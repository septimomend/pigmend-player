/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

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
#include <QTimer>

#include "playlistSingleton.h"
#include "videoWidget.h"
#include "playerControls.h"
#include "mediafileController.h"
#include "search.h"
#include "aboutpigmend.h"
#include "preferencesdialog.h"
#include "renamedialog.h"

namespace Ui
{
class MediaPlayer;
}

class MediaPlayer : public QMainWindow
{
    Q_OBJECT

public:
	explicit MediaPlayer(QRect screen_size, conf_data_t *conf_data, QWidget *parent = nullptr);
	~MediaPlayer() override;
    void postInit();

private:
    void initMenu();
    int volume() const;
    void clearLayout(QLayout *layout);
    void adjustVideoWidget();
    void deleteObjectsInFullScreen();
	void initAnimations();
    void resizeMovieLabel();
    void unfocusButtons();
    void initPlaylist();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent *event) override;

signals:
    void fullScreenChanged(bool fullScreen);
    void changeVolume(int volume);
    void progressSliderValueChanged(int);   // use this signal while silder value changes instead of QSlider::valueChanged(int) - it is slow and bugged
    void closeMainWindow();
    void videoFullscreenToggled();

private slots:
    void updatePlaylist();                  // read playlist QMap to playlist widget
    void updateTitle(QStringList *title);   // sets metadata at header
    void updateDuration(int duration);      // sets duration of mediafile to QLabel widget
    void focusItem(QString path);           // focuses first item in playlist widget
    void updateTimeProgress(int playTime);  // updates progress time
    void clearPlaylist();                   // clears playlist widget and data
    void showInfo();                        // info about author
    void updateIndexedData(int mp3count, int mp4count, bool status);// sets count of media files which are gotten from thread
    void setWindowSize();
    void updateVolumeValue(float volume);
    void onVolumeSliderValueChanged();
    void onVolumeButtonUpChanged();
    void onVolumeButtonDownChanged();
	void onVolumeMute(bool isMuted);
    void updateCursorPosition(QPoint *);
    void hideControlPanelInNormalMode(bool forcedHide);
    void hideVideoControlPanel();
	void updateTheme();
	void updateAnimation();
	void stopAnimation(bool isPaused);
	void showHidePlaylist();
	void onShuffleButton();
	void onRepeatButton();
	void onPlaylistDoubleClicked(int row, int column);
	void onPlaylistUpdate();
	void onContentTypeChange(bool isAudio);
    void onKeyPressed();
    void toggleVideoWidgetFullscreen();
    void removeItemFromPlaylist();
    void openNewPlaylistTab();
    void playlistTabChanged(int id);
    void closePlaylistTab(int id);
    void renamePlaylistTab(int id);
    void playlistTabRenamed(QString text, int id);
    void onMenuResize();

private:
    int m_global_height;
    int m_global_width;
    int m_keyPressNumber;
    Ui::MediaPlayer *ui;
    bool m_shuffleMode;
    bool m_isPlaylistLoaded;
    bool m_isPaused;
    bool m_isUpdateOnRemove;
    VideoWidget *m_videoWidget;
    VideoWidget *m_globalVideoWidget;
    PlayerControls *m_playerControls;
    MediafileController *m_mediaFile;
    PlaylistSingleton &m_playlist = PlaylistSingleton::getInstance();
    SearchDialog *m_search;
    PreferencesDialog *m_preferences;
    AboutPigmend *m_aboutPlayer;
    renameDialog *m_renameDialog;
    QMovie *m_movieLoading, *m_movieDone;
	QMovie *m_movieMusic;
    QSize m_movieImageSize;
    QString m_theme_config_path;
	QTimer *m_timer;
    QTimer *m_videoControlTimer;
    QTimer *m_menuWidthTimer;
    QPushButton *addPlaylistButton;

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
	QMenu *m_animation_menu;
    QMenu *m_helpmenu;
    QMenu *m_windowMenu;
    QMenu *m_editmenu;
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
	QAction *m_noneAnimationAction;
	QAction *m_defaultAnimationAction;
	QAction *m_equalizerAnimationAction;
	QAction *m_radioAnimationAction;
    QAction *m_astralAnimationAction;
    QAction *m_preferencesAction;

    // Full screen controls
    QSpacerItem *m_spaceInFullScreenButtonsLeft;
    QSpacerItem *m_spaceInFullScreenButtonsRight;
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
    QSlider *m_sliderInFullScreen;
    QSlider *m_volumeSliderInFullScreen;
    QLabel *m_titleInFullScreen;
    QLabel *m_durationInFullScreen;
    QLabel *m_progressTimeInFullScreen;
	QLabel *m_musicLabel;

	//config
	conf_data_t *m_conf_data;

	//xml
	XMLDP m_xmldp;
    styles_data_t *m_style;
};

#endif // MEDIAPLAYER_H
