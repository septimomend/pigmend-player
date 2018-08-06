/*

MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMainWindow>
#include <QWidget>
#include <QMediaService>
#include <QListWidgetItem>
#include <QTime>
#include <QMenuBar>
#include <QDesktopServices>
#include <QMovie>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QLabel>

#include "playlistSingleton.h"
#include "videoWidget.h"
#include "playerControls.h"
#include "mediafileController.h"
#include "search.h"
#include "aboutpigmend.h"

namespace Ui
{
class MediaPlayer;
}

class MediaPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MediaPlayer(QRect screen_size, QWidget *parent = 0);
    ~MediaPlayer();

private:
    void initMenu();
    void rememberTheme(QString &style_id);
    void loadTheme();
    void updateTheme(QString theme);
    int volume() const;
    void clearLayout(QLayout *layout);
    void adjustVideoWidget();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

signals:
    void fullScreenChanged(bool fullScreen);
    void videoWidgetDefined(VideoWidget *vw);
    void changeVolume(int volume);
    void progressSliderValueChanged(int);   // use this signal while silder value changes instead of QSlider::valueChanged(int) - it is slow and bugged

private slots:
    void updatePlaylist();                  // read playlist QMap to playlist widget
    void updateTitle(QStringList *title);   // sets metadata at header
    void updateDuration(int duration);      // sets duration of mediafile to QLabel widget
    void focusItem(QString path);           // focuses first item in playlist widget
    void updateTimeProgress(int playTime);  // updates progress time
    void clearPlaylist();                   // clears playlist widget and data
    void checkShuffleMode(bool check);      // shuffled new data if playlist updated
    void setBlueMendTheme();                // sets blue theme
    void setOrangeMendTheme();              // sets orange theme
    void setGreyMendTheme();                // sets grey theme
    void setDarkGreyMendTheme();            // sets grey theme
    void showInfo();                        // info about author
    void updateIndexedData(int mp3count, int mp4count, bool status);// sets count of media files which are gotten from thread
    void setWindowSize();
    void updateVolumeValue(float volume);
    void onVolumeSliderValueChanged();
    void onVolumeButtonUpChanged();
    void onVolumeButtonDownChanged();
    void onVolumeMute();
    void updateCursorPosition(QPoint *);
    void hideControlPanelInNormalMode(bool forcedHide);

private:
    int m_global_height;
    int m_global_width;
    Ui::MediaPlayer *ui;
    bool m_shuffleMode;
    bool m_isPlaylistLoaded;
    VideoWidget *m_videoWidget;
    VideoWidget *m_globalVideoWidget;
    PlayerControls *m_playerControls;
    MediafileController *m_mediaFile;
    PlaylistSingleton &m_playlist = PlaylistSingleton::getInstance();   // singleton instance
    SearchDialog *m_search;
    AboutPigmend *m_aboutPlayer;
    QMovie *m_movieLoading, *m_movieDone;
    QString m_theme_config_path;
    QSlider *m_sliderInFullScreen;
    QLabel *m_titleInFullScreen;
    QLabel *m_durationInFullScreen;
    QLabel *m_progressTimeInFullScreen;

    // shortcuts
    QShortcut *m_playSC;
    QShortcut *m_nextSC;
    QShortcut *m_prevSC;
    QShortcut *m_stopSC;

    // menu
    QMenuBar *m_menuBar;
    QMenu *m_filemenu;
    QMenu *m_viewmenu;
    QMenu *m_thememenu;
    QMenu *m_helpmenu;
    QMenu *m_windowMenu;
    QAction *m_addFileAction;
    QAction *m_addFolderAction;
    QAction *m_orangeAction;
    QAction *m_blueAction;
    QAction *m_greyAction;
    QAction *m_darkGreyAction;
    QAction *m_fullScreenAction;
    QAction *m_clearAction;
    QAction *m_infoAction;
    QAction *m_aboutPigmendAction;
    QAction *m_exitAction;
    QAction *m_normalWindowAction;
    QAction *m_maximizeAction;
    QAction *m_smallWindowAction;
    QAction *m_middleWindowAction;
    QAction *m_wideWindowAction;

    // Full screen controls
    QSpacerItem *m_spaceInFullScreenButtons;
    QHBoxLayout *m_videoProgressLayout;
    QHBoxLayout *m_videoTitleLayout;
    QHBoxLayout *m_videoScreenLayout;
    QHBoxLayout *m_videoButtonsLayout;
    QVBoxLayout *m_controlVLayout;
    QGridLayout *m_videoGridLayout;
    QGridLayout *m_videoControlGridLayout;
    QPushButton *m_playInFullScreen;
    QPushButton *m_pauseInFullScreen;
    QPushButton *m_stopInFullScreen;
    QPushButton *m_nextInFullScreen;
    QPushButton *m_prevInFullScreen;
    QPushButton *m_disableFullScreen;
    QPushButton *m_volumeUpInFullScreen;
    QPushButton *m_volumeDownInFullScreen;
    QPushButton *m_volumeMuteInFullScreen;
};

#endif // MEDIAPLAYER_H
