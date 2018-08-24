/*

MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
