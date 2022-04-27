/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "playlistSingleton.h"

#include <QtDebug>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>
#include <iostream>
#include <iomanip>
#include <QDebug>
#include <QDateTime>

using namespace std;

PlaylistSingleton::PlaylistSingleton(QObject *parent)
{
    (void)parent;
    m_style = nullptr;
    m_playilstCounter = 1;

    m_actInsert = new QAction("Add item", this);
    m_actDelete = new QAction("Delete", this);

    m_actInsert->setIcon(QIcon(":/buttons/img/buttons/add-file-16.ico"));
    m_actDelete->setIcon(QIcon(":/buttons/img/buttons/x-mark-16.ico"));

    connect(m_actInsert, &QAction::triggered, [=]() { emit addActionTriggered(); });
    connect(m_actDelete, &QAction::triggered, [=]() { emit removeActionTriggered(); });
}

PlaylistSingleton::~PlaylistSingleton()
{

}

PlaylistSingleton& PlaylistSingleton::getInstance()
{
    static PlaylistSingleton instance;
    return instance;
}

size_t PlaylistSingleton::clearPlaylistData()
{
    if (!m_plData->isEmpty())
    {
        m_plData->clear();
        m_shuffledData.clear();
    }
    return size_t(m_plData->size());
}

void PlaylistSingleton::deletePlaylistItem(QTableWidgetItem *item)
{
    m_plData->remove(item->text());
}

size_t PlaylistSingleton::makeShuffle(bool shuffleMode)
{
    // if the suffle mode is enabled - copy filepath of playlist data to the vector
    // and shuffle this vector by random_shuffle() algorithm
	srand(static_cast<unsigned int>(time(nullptr)));
    m_shuffledData.clear();

	if (shuffleMode)
    {
        for (auto it = m_plData->begin(); it != m_plData->end(); ++it)
            m_shuffledData.push_back(it.value());
        std::random_shuffle(m_shuffledData.begin(), m_shuffledData.end());
    }
    else
        m_shuffledData.clear();

    return size_t(m_shuffledData.size());
}

QString PlaylistSingleton::convertIntToTimeStr(int hours, int min, int sec)
{
	QString h_str = QString::number(hours);
	QString m_str = QString::number(min);
	QString s_str = QString::number(sec);

	if (h_str.size() < 2)
		h_str = QString(2 - h_str.size(), '0') + h_str;

	if (m_str.size() < 2)
		m_str = QString(2 - m_str.size(), '0') + m_str;

	if (s_str.size() < 2)
		s_str = QString(2 - s_str.size(), '0') + s_str;

	return (h_str + ":" + m_str + ":" + s_str);
}

QString PlaylistSingleton::getAudioTotalTime()
{
	int total = 0, seconds, hours, minutes;
    for (auto it = m_plData->begin(); it != m_plData->end(); ++it)
	{
		TagLib::FileRef f(it.value().toStdString().c_str());

		if(!f.isNull() && f.tag())
			TagLib::PropertyMap tags = f.file()->properties();

		if (!f.isNull() && f.audioProperties())
		{
			TagLib::AudioProperties *properties = f.audioProperties();
			total += properties->lengthInSeconds();
		}
	}

	hours = total / 3600;
	minutes = (total % 3600) / 60;
	seconds = (total % 3600) % 60;

	return convertIntToTimeStr(hours, minutes, seconds);
}

QString PlaylistSingleton::getAudioTime(QString &audio_file)
{
	int time = 0, seconds, hours, minutes;
	TagLib::FileRef f(audio_file.toStdString().c_str());

	if(!f.isNull() && f.tag())
		TagLib::PropertyMap tags = f.file()->properties();

	if (!f.isNull() && f.audioProperties())
	{
		TagLib::AudioProperties *properties = f.audioProperties();
		time += properties->lengthInSeconds();
	}

	hours = time / 3600;
	minutes = (time % 3600) / 60;
	seconds = (time % 3600) % 60;

	return convertIntToTimeStr(hours, minutes, seconds);
}

playlists_str PlaylistSingleton::createNewPlaylist()
{
    playlists_str newPlaylist = {};
    newPlaylist.tabName = "Playlist #" + QString::number(m_playilstCounter++);
    newPlaylist.tabId = "pltab" + QString::number(QDateTime::currentSecsSinceEpoch());
    newPlaylist.playlistWidget = new QTableWidget();
    newPlaylist.playlistWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    newPlaylist.playlistWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    newPlaylist.playlistWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    newPlaylist.playlistWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    newPlaylist.playlistWidget->setFont(QFont("Ubuntu", 8));
    newPlaylist.playlistWidget->setFocusPolicy(Qt::NoFocus);
    newPlaylist.playlistWidget->setWordWrap(false);
    newPlaylist.playlistWidget->setShowGrid(false);
    newPlaylist.playlistWidget->setAutoScroll(true);
    newPlaylist.playlistWidget->horizontalHeader()->setCascadingSectionResizes(true);
    newPlaylist.playlistWidget->horizontalHeader()->setMinimumSectionSize(0);
    newPlaylist.playlistWidget->horizontalHeader()->hide();
    newPlaylist.playlistWidget->verticalHeader()->hide();
    newPlaylist.plData.empty();
    m_playlists.insert(newPlaylist.tabId, newPlaylist);

    for (auto it = m_playlists.begin(); it != m_playlists.end(); ++it)
    {
        if (it.key() == newPlaylist.tabId)
        {
            m_plData = &it.value().plData;
            m_playing_widget = it.value().playlistWidget;
            connect(it.value().playlistWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onPlaylistDoubleClicked(int,int)));
            break;
        }
    }

    updateStylesheet();
    initContextMenu();

    return newPlaylist;
}

bool PlaylistSingleton::setActivePlaylist(QString id)
{
    for (auto it = m_playlists.begin(); it != m_playlists.end(); ++it)
    {
        if (it.key() == id)
        {
            m_current_playlist = &it.value();
            return true;
        }
    }

    return false;
}

void PlaylistSingleton::updateTheme(styles_data_t *style)
{
    m_style = style;
    updateStylesheet();
}

void PlaylistSingleton::updateStylesheet()
{
    if (!m_style)
        return;

    for (auto it = m_playlists.begin(); it != m_playlists.end(); ++it)
    {
        it.value().playlistWidget->setStyleSheet(m_style->playlistTheme);
        it.value().playlistWidget->verticalScrollBar()->setStyleSheet(m_style->playlistScrollBar);
    }
}

QTableWidget *PlaylistSingleton::getCurrentPlaylistWidget(bool isCurrentlyPlaying)
{
    return isCurrentlyPlaying ? m_playing_widget : m_current_playlist->playlistWidget;
}

void PlaylistSingleton::initContextMenu()
{
    for (auto it = m_playlists.begin(); it != m_playlists.end(); ++it)
    {
        QTableWidget *widget = it.value().playlistWidget;
        if (!widget->actions().isEmpty())
            continue;

        widget->setContextMenuPolicy(Qt::ActionsContextMenu);
        widget->addActions({ m_actInsert, m_actDelete });
    }
}

void PlaylistSingleton::onPlaylistDoubleClicked(int row, int column)
{
    m_plData = &m_current_playlist->plData;
    m_playing_widget = m_current_playlist->playlistWidget;

    emit activatePlaylist(row, column);
}

QMap<QString, QString> *PlaylistSingleton::getCurrentPlaylistContainer()
{
    return &m_current_playlist->plData;
}

bool PlaylistSingleton::removePlaylist(QString id)
{
    m_playlists.remove(id);

    if (m_current_playlist->tabId == id)
    {
        m_plData = &m_playlists.begin().value().plData;
        m_playing_widget = m_playlists.begin().value().playlistWidget;
    }

    for (auto it = m_playlists.begin(); it != m_playlists.end(); ++it)
    {
        qDebug() << it.key() << it->tabId;
    }
    return true;
}

QString PlaylistSingleton::getCurrentTabId()
{
    return m_current_playlist->tabId;
}
