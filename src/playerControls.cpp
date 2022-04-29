/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "playerControls.h"

int PlayerControls::m_mediaOrder = -1;

PlayerControls::PlayerControls(QWidget *parent) : m_vw(static_cast<VideoWidget*>(parent))
{
    m_player = new QMediaPlayer();
    m_musicPlayer = new QMediaPlayer();

    // if metadata will be changed, ie new media file assigned then sends metaDataChanged() signal and
    // setMetaData() is fixing this data
    connect(m_player, SIGNAL(metaDataChanged()), this, SLOT(setMetaData()));        // relable to metadata changing
    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(changeDuration(qint64)));
    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(setMetaData()));  // duration
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(setTimeProgress(qint64)));
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(processState(QMediaPlayer::State)));
    connect(m_player, SIGNAL(volumeChanged(int)), this, SLOT(setVolume(int)));
    connect(this, SIGNAL(setVolumeToPlayer(int)), m_player, SLOT(setVolume(int)));

    m_isMusic = false;
    m_isKeyClicked = false;
    m_repeatMode = false;
    m_shuffleMode = false;
    m_handleSelected = false;
    m_position = 0;
    m_stopMouseThread = false;

    m_thread = std::thread(&captureMousePosition, this);
    m_thread.detach();
}

PlayerControls::~PlayerControls()
{
    delete m_player;
    delete m_musicPlayer;
}

void PlayerControls::setVideoContent()
{
    // if this mp3 file - show music gif
    // else show video
	if (m_player->currentMedia().canonicalUrl().toString().contains(QString(".mp3")) ||
		m_player->currentMedia().canonicalUrl().toString().contains(QString(".wav")) ||
		m_player->currentMedia().canonicalUrl().toString().contains(QString(".flac")))
    {
        if (!m_isMusic)
            m_isMusic = true;
    }
    else
    {
        m_player->setVideoOutput(m_vw);
        m_isMusic = false;
    }

	emit isMusicContent(m_isMusic);
}

void PlayerControls::play()
{
    if (m_player->currentMedia().isNull())
        return;

    if (!m_player->media().isNull() && m_player->playbackRate() != 1.0)
	{
		m_player->setPlaybackRate(1.0); // set normal playback rate if press `play` after some fast forward button
		return;
	}

    emit currentMediaItem(QString(m_player->currentMedia().canonicalUrl().toString()));  // send signal with path of current media file
    m_player->setMedia(m_player->currentMedia().canonicalUrl());

#if DEBUG
    qDebug() << "Play " << QString(m_player->currentMedia().canonicalUrl().toString());
#endif

    if (m_vw == nullptr)
    {
        qCritical() << "Error: Video widget is not defined" << endl;
        return;
    }

    setVideoContent();

    m_player->setPosition(m_position);
    m_player->play();
    setVolume(m_player->volume());
    m_position = 0;

    m_isKeyClicked = false;
    m_handleSelected = false;

	emit paused(false);
}

void PlayerControls::pause()
{
    m_isKeyClicked = true;
	m_position = int(m_player->position());
    m_player->pause();      // pause play track
    //m_musicPlayer->pause(); // and pause gif
    m_isMusic = false;      // false to be sure gif will be continue after pressing play button
	emit paused(true);
}

void PlayerControls::stop()
{
    m_isKeyClicked = true;
    m_player->stop();       // stop play
    //m_musicPlayer->stop();  // and stop gif
    m_isMusic = false;      // false to be sure gif will be continue after pressing play button
	emit paused(true);
}

void PlayerControls::nextForced()
{
    // this function ignores repeat mode
    // it was made for turning tracks by `next` button when repeat mode is enabled
    // but if the shuffle mode is enabled too the next track will set randomly
    m_isKeyClicked = true;

    if (nextInShuffle())
        return;

    // get current media file path
    QString path = m_player->currentMedia().canonicalUrl().toString();

    // pass QMap with playlist data
    for (auto it = m_playlist.m_plData->begin(); it != m_playlist.m_plData->end(); ++it)
    {
#ifdef WIN32
        QString canonical_path = "file:///" + it.value();
#elif unix
        QString canonical_path = "file://" + it.value();
#endif

        if (path == canonical_path)
        {
            // and this is not last item so set next item to media playing
            if (it != m_playlist.m_plData->end() - 1)
            {
                ++it;
                m_player->setMedia(QUrl::fromLocalFile(it.value()));

                // artificial generation of signal
                // when current media is not available track duration is 0
                // and if after this track is unavailable again signal durationChanged() will not work
                // because there no changes
                emit m_player->durationChanged(0);

                play();
                break;
            }
            else
                qDebug() << "Last song. No next";
        }
    }
}

void PlayerControls::next()
{
    // if repeat mode is true - play current song again
    if (isRepeatMode())
        return;

    nextForced();
}

void PlayerControls::prev()
{
    m_isKeyClicked = true;

    if (prevInShuffle())
        return;

    // get current media file path
    QString path = m_player->currentMedia().canonicalUrl().toString();

    // pass QMap with playlist data
    for (auto it = m_playlist.m_plData->begin(); it != m_playlist.m_plData->end(); ++it)
    {
        // if here is accordance with current path
#ifdef WIN32
        QString canonical_path = "file:///" + it.value();
#elif unix
        QString canonical_path = "file://" + it.value();
#endif
        if (path == canonical_path)
        {
            // and this is not first item so set previous item to media playing
            if (it != m_playlist.m_plData->begin())
            {
                --it;
                m_player->setMedia(QUrl::fromLocalFile(it.value()));
                play();
                break;
            }
            else
                qDebug() << "First song. No previous";
        }
    }
}

void PlayerControls::setFirstFile(QListWidgetItem* item)
{
    // prepare first item after filling playlist at first time
    m_player->setMedia(QUrl::fromLocalFile(item->text()));
}

void PlayerControls::setMediaFile(QString item)
{
    m_handleSelected = true;
    m_isKeyClicked = true;

    // set media file. When make double click on playlist widget item, then send this item to here
    // and check if this item text (ie filename) is in QMap container
    // then set its path to media playing
    auto iter = m_playlist.m_plData->find(item);
    if (iter != m_playlist.m_plData->end() && iter.key() == item)
    {
       m_player->setMedia(QUrl::fromLocalFile(iter.value()));
       play();
    }
}

void PlayerControls::setVolume(int volume)
{
    qreal logVolume = QAudio::convertVolume(volume / qreal(100), QAudio::LinearVolumeScale, QAudio::LogarithmicVolumeScale);
    emit changeVolumeValue(qRound(logVolume * 100));
}

void PlayerControls::changeDuration(qint64 duration)
{
	emit durationChanged(int(duration));
}

void PlayerControls::setMetaData()
{
    // read metadata and write it to string list
    QStringList title;
    title << m_player->metaData(QMediaMetaData::ContributingArtist).toString() <<
             m_player->metaData(QMediaMetaData::Title).toString() <<
             m_player->metaData(QMediaMetaData::Genre).toString() <<
             m_player->metaData(QMediaMetaData::Year).toString();

    // DEPRECATED use changeDuration instead
    //qint64 duration = m_player->metaData(QMediaMetaData::Duration).toInt();
    //emit durationChanged(duration); // send duration

    emit titleChanged(&title);      // send metadata
}

void PlayerControls::setVideoWidget(VideoWidget *vw)
{
    m_vw = vw;
}

void PlayerControls::setTimeProgress(qint64 timeProgress)
{
	emit timeProgressChanged(int(timeProgress));
}

void PlayerControls::processState(QMediaPlayer::State state)
{
    // if file is in stopped state and some player button isn't clicked
    // it means track is completed or its can't be decoded so turn to next
    if(state == QMediaPlayer::StoppedState && !m_isKeyClicked)
        next();
}

void PlayerControls::seek(int progressValue)
{
    m_player->setPosition(progressValue * 1000);
}

void PlayerControls::fastForward()
{
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve which button was clicked
    QString buttonText = buttonSender->text();

    // if this 2x button - set double playback rate
    // if 4x - by 4 times faster
    if (buttonText == "2x")
        m_player->setPlaybackRate(2.0);
    else if (buttonText == "4x")
        m_player->setPlaybackRate(4.0);
}

void PlayerControls::setRepeatMode(bool checkRepeat)
{
    m_repeatMode = checkRepeat;
}

void PlayerControls::setShuffleMode(bool checkShuffle)
{
    // makeShuffle() copies playlist data to vector and shuffles it
    // then it returns size of shuffled container
    // if returned value is 0 - no data to be shuffled
    m_shuffleMode = m_playlist.makeShuffle(checkShuffle);
}

bool PlayerControls::isRepeatMode()
{
    // if repeat mode enabled - set current track again and again
    if (m_repeatMode)
    {
        m_player->setMedia(m_player->currentMedia());
        play();
        return true;
    }
    else
        return false;
}

bool PlayerControls::nextInShuffle()
{
    // read shuffled container
    // this function calls every time with next()
    // in first calling the variable `i` is 0, so will be chose 0-indexed data from shuffled vector
    // in second - 1-indexed data and so on
    if (m_shuffleMode && !m_handleSelected)
    {
        if(m_mediaOrder != (m_playlist.m_shuffledData.size() - 1))
        {
            ++m_mediaOrder;
            m_player->setMedia(QUrl::fromLocalFile(m_playlist.m_shuffledData[m_mediaOrder]));
            play();
            return true;
        }
        else
            qDebug() << "Last song. No next";
    }

    return false;
}

bool PlayerControls::prevInShuffle()
{
    // read shuffled container
    // this function calls every time with next()
    // in first calling the variable `i` is 0, so will be chose 0-indexed data from shuffled vector
    // in second - 1-indexed data and so on
    if (m_shuffleMode && !m_handleSelected)
    {
        if (m_mediaOrder > 0)
        {
            --m_mediaOrder;
            m_player->setMedia(QUrl::fromLocalFile(m_playlist.m_shuffledData[m_mediaOrder]));
            play();
            return true;
        }
        else
            qDebug() << "Last song. No next";
    }

    return false;
}

void PlayerControls::captureMousePosition(PlayerControls *pc)
{
    std::lock_guard<std::mutex> locker(pc->m_mtx);

    while (!pc->m_stopMouseThread)
    {
        QPoint cursor_position = pc->mapFromGlobal(QCursor::pos());
        emit pc->mousePositionChanged(&cursor_position);
    }
}

void PlayerControls::setVolumeMuted()
{
	m_player->setMuted(!m_player->isMuted());
	emit volumeMutedChanged(m_player->isMuted());
}

void PlayerControls::interrupt()
{
    m_stopMouseThread = true;
}

QString PlayerControls::getCurrentMediaItemValue()
{
    QStringList sl = m_player->currentMedia().canonicalUrl().toString().split("/");
    return sl.at(sl.count() - 1);
}

QString PlayerControls::getCurrentMediaItem()
{
    return m_player->currentMedia().canonicalUrl().toString();
}
