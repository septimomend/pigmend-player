/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

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
	parent = nullptr;
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
    if (!m_plData.isEmpty())
    {
        m_plData.clear();
        m_shuffledData.clear();
    }
	return size_t(m_plData.size());
}

size_t PlaylistSingleton::makeShuffle(bool shuffleMode)
{
    // if the suffle mode is enabled - copy filepath of playlist data to the vector
    // and shuffle this vector by random_shuffle() algorithm
	srand(static_cast<unsigned int>(time(nullptr)));
    m_shuffledData.clear();

	if (shuffleMode)
    {
		for (auto it = m_plData.begin(); it != m_plData.end(); ++it)
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
	for (auto it = m_plData.begin(); it != m_plData.end(); ++it)
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
