/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

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
	PlayerControls(QWidget *parent = nullptr);
    ~PlayerControls();

    bool m_stopMouseThread;

    bool isRepeatMode();                        // sets current media file again
    bool nextInShuffle();                       // sets next media file in accordance with shuffled data
    bool prevInShuffle();                       // sets previous media file in accordance with shuffled data
    QString getCurrentMediaItem();
    QString getCurrentMediaItemValue();

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
    void setMediaFile(QString item);            // sets media file for playing
    void setVideoWidget(VideoWidget *vw);       // sets QWidget for video output
    void setTimeProgress(qint64 timeProgress);  // set time position
    void seek(int progressValue);               // sets progress if value at progress slider is changed
    void fastForward();                         // sets fast forward (2x, 4x)
    void setRepeatMode(bool checkRepeat);       // sets m_repeatMode true or false
    void setShuffleMode(bool checkShuffle);     // sets m_shuffleMode calling m_playlist.makeShuffle() which shuffles data
    void setFirstFile(QListWidgetItem *item);   // sets playing first file after pressing `play` at once after playlist filling
    void setVolume(int volume);
	void setVolumeMuted();
    void interrupt();

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
	void volumeMutedChanged(bool isMuted);
	void isMusicContent(bool);
	void paused(bool);

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
    std::thread m_thread;
};

#endif // PLAYER_H
