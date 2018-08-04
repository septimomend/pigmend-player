/*

MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QListWidgetItem>
#include <QMediaMetaData>
#include <QPushButton>
#include <mutex>
#include <thread>

#include "playlistSingleton.h"
#include "videoWidget.h"

class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    PlayerControls(QWidget *parent = 0);
    ~PlayerControls();

    bool isRepeatMode();                        // sets current media file again
    bool nextInShuffle();                       // sets next media file in accordance with shuffled data
    bool prevInShuffle();                       // sets previous media file in accordance with shuffled data

    static void captureMousePosition(PlayerControls *pc);

private:
    void setVideoContent();                     // sets video content in accordance what media kind is chosen (music or video)

public slots:
    void play();
    void pause();
    void stop();
    void next();
    void nextForced();
    void prev();
    void setMediaFile(QListWidgetItem *item);   // sets media file for playing
    void setVideoWidget(VideoWidget *vw);       // sets QWidget for video output
    void setTimeProgress(qint64 timeProgress);  // set time position
    void seek(int progressValue);               // sets progress if value at progress slider is changed
    void fastForward();                         // sets fast forward (2x, 4x)
    void setRepeatMode(bool checkRepeat);       // sets m_repeatMode true or false
    void setShuffleMode(bool checkShuffle);     // sets m_shuffleMode calling m_playlist.makeShuffle() which shuffles data
    void setFirstFile(QListWidgetItem *item);   // sets playing first file after pressing `play` at once after playlist filling
    void setVolume(int volume);

private slots:
    void setMetaData();                         // reads and sets metadata of file
    void processState(QMediaPlayer::State state); // process state of current track - if it is completed or broken then play next track
    void changeDuration(qint64 duration);

signals:
    void currentMediaItem(QString);             // gets current media item that
    void titleChanged(QStringList*);            // informs about setting of metadata and sends this one
    void durationChanged(int);                  // sends duration of mediafile
    void timeProgressChanged(int);              // sends current time of media playing
    void changeVolumeValue(float);
    void setVolumeToPlayer(int);
    void mousePositionChanged(QPoint *);

private:
    QMediaPlayer *m_player, *m_musicPlayer;
    VideoWidget *m_vw;
    bool m_isMusic, m_isKeyClicked;
    bool m_repeatMode, m_shuffleMode;
    bool m_handleSelected;
    int m_position;
    PlaylistSingleton &m_playlist = PlaylistSingleton::getInstance();
    static int m_mediaOrder;
    std::mutex m_mtx;
};

#endif // PLAYER_H
