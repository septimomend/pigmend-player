/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef PLAYLISTSINGLETON_H
#define PLAYLISTSINGLETON_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <algorithm>
#include <QTableWidgetItem>
#include "constants.h"

QT_BEGIN_NAMESPACE
class QMediaPlaylist;
QT_END_NAMESPACE

struct playlists_str
{
    QString tabId;
    QString tabName;
    QMap<QString, QString> plData;
    QTableWidget *playlistWidget;
};

class PlaylistSingleton : public QObject
{
    Q_OBJECT

private slots:
    void onPlaylistDoubleClicked(int row, int column);

private:
	PlaylistSingleton(QObject *parent = nullptr);
    ~PlaylistSingleton();
    PlaylistSingleton(const PlaylistSingleton &) = delete;
    PlaylistSingleton& operator=(const PlaylistSingleton &) = delete;

	QString convertIntToTimeStr(int hours, int min, int sec);
    void updateStylesheet();
    void initContextMenu();

public:
    static PlaylistSingleton &getInstance();
    size_t clearPlaylistData();                 // clears m_plData and returns its size
    size_t makeShuffle(bool shuffleMode);
	QString getAudioTotalTime();
	QString getAudioTime(QString &audio_file);
    void deletePlaylistItem(QTableWidgetItem *item);
    playlists_str createNewPlaylist();
    playlists_str *getActivePlaylist(int id);
    bool setActivePlaylist(QString id);
    bool removePlaylist(QString id);
    void updateTheme(styles_data_t *style);
    QTableWidget *getCurrentPlaylistWidget(bool isCurrentlyPlaying = false);
    QMap<QString, QString> *getCurrentPlaylistContainer();
    QString getCurrentTabId();

signals:
    void removeActionTriggered();
    void addActionTriggered();
    void activatePlaylist(int row, int column);

public:
    QMap<QString, QString> *m_plData;    // container for pairs of filename and filepath
    QVector<QString> m_shuffledData;

private:
    QMap<QString, playlists_str> m_playlists;
    styles_data_t *m_style;
    playlists_str *m_current_playlist;
    QTableWidget *m_playing_widget;
    int m_playilstCounter;
    QAction *m_actInsert;
    QAction *m_actDelete;
};

#endif // PLAYLISTSINGLETON_H
