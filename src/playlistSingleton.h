/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef PLAYLISTSINGLETON_H
#define PLAYLISTSINGLETON_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <algorithm>

QT_BEGIN_NAMESPACE
class QMediaPlaylist;
QT_END_NAMESPACE

class PlaylistSingleton : public QObject
{
    Q_OBJECT

private:
	PlaylistSingleton(QObject *parent = nullptr);
    ~PlaylistSingleton();
    PlaylistSingleton(const PlaylistSingleton &) = delete;
    PlaylistSingleton& operator=(const PlaylistSingleton &) = delete;

public:
    static PlaylistSingleton &getInstance();
    size_t clearPlaylistData();                 // clears m_plData and returns its size
    size_t makeShuffle(bool shuffleMode);

public:
    QMap<QString, QString> m_plData;    // container for pairs of filename and filepath
    QVector<QString> m_shuffledData;
};

#endif // PLAYLISTSINGLETON_H
