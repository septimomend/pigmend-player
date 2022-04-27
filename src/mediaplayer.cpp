/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "mediaplayer.h"
#include "ui_mediaplayer.h"
#include "config-dp/config.h"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace rapidxml;
using namespace  tinyxml2;

#define PLAYLIST_NUM_COLUMN 0
#define PLAYLIST_NAME_COLUMN 1
#define PLAYLIST_TIME_COLUMN 2
#define SLIDER_STEP 10
#define PLAYLIST_COLUMN_COUNT 3
#define TIME_TO_HIDE_VIDEO_CTRL_MS 1000

MediaPlayer::MediaPlayer(QRect screen_size, conf_data_t *conf_data, QWidget *parent) : QMainWindow(parent),
	m_global_height(screen_size.height()), m_global_width(screen_size.width()),
	ui(new Ui::MediaPlayer), m_videoWidget(nullptr), m_conf_data(conf_data)
{
    ui->setupUi(this);

    initPlaylist();
    QSettingsWidgetDialogEngine::registerGlobalWidgetType<QSettingsDialogWidget<PluginDialog>>(777777);

	m_playerControls = new PlayerControls();
	m_mediaFile = new MediafileController(this);
	m_search = new SearchDialog(this);
    m_preferences = new PreferencesDialog();
	m_aboutPlayer = new AboutPigmend(conf_data, this);
    m_renameDialog = new renameDialog(this);
	m_timer = new QTimer(this);
    m_videoControlTimer = new QTimer(this);
    m_keyPressNumber = 0;
    m_style = NULL;

	// shortcuts
	m_playSC = new QShortcut(Qt::Key_MediaPlay, ui->playButton, SLOT(click()));
	m_nextSC = new QShortcut(Qt::Key_MediaNext, ui->nextButton, SLOT(click()));
	m_prevSC = new QShortcut(Qt::Key_MediaPrevious, ui->prevButton, SLOT(click()));
	m_stopSC = new QShortcut(Qt::Key_MediaStop, ui->stopButton, SLOT(click()));

    ui->trademarkInfoLabel->setText(m_aboutPlayer->getInfoAbout()->software_name + " by "
        + m_aboutPlayer->getInfoAbout()->author_name + " © " + m_aboutPlayer->getInfoAbout()->year);

    // initialize modules
	initAnimations();
	initMenu();
	adjustVideoWidget();
	updateTheme();

	//
    m_isUpdateOnRemove = false;
	m_isPlaylistLoaded = false;
    m_isPaused = true;
	m_shuffleMode = false;
	ui->volumeSlider->setRange(0, 100);

	m_sliderInFullScreen->setObjectName("sliderInFullScreen");
	m_globalVideoWidget->setObjectName("globalVideoWidget");
	m_videoWidget->setObjectName("videoWidget");
	ui->progressSlider->installEventFilter(this);
	m_sliderInFullScreen->installEventFilter(this);
	m_globalVideoWidget->installEventFilter(this);
	m_videoWidget->installEventFilter(this);
	ui->playButton->installEventFilter(this);
	ui->pauseButton->installEventFilter(this);
	ui->volumeSlider->installEventFilter(this);
	m_volumeSliderInFullScreen->installEventFilter(this);
	this->installEventFilter(this);

    unfocusButtons();

	// set QWidget for video output
    m_playerControls->setVideoWidget(m_videoWidget);

	// menu actions
	connect(m_addFileAction, SIGNAL(triggered(bool)), m_mediaFile, SLOT(openFile()));
	connect(m_addFolderAction, SIGNAL(triggered(bool)), m_mediaFile, SLOT(openFolder()));
	connect(m_orangeAction, SIGNAL(triggered(bool)), this, SLOT(updateTheme()));
	connect(m_blueAction, SIGNAL(triggered(bool)), this, SLOT(updateTheme()));
	connect(m_greyAction, SIGNAL(triggered(bool)), this, SLOT(updateTheme()));
	connect(m_darkGreyAction, SIGNAL(triggered(bool)), this, SLOT(updateTheme()));
	connect(m_noneAnimationAction, SIGNAL(triggered(bool)), this, SLOT(updateAnimation()));
	connect(m_defaultAnimationAction, SIGNAL(triggered(bool)), this, SLOT(updateAnimation()));
	connect(m_equalizerAnimationAction, SIGNAL(triggered(bool)), this, SLOT(updateAnimation()));
	connect(m_radioAnimationAction, SIGNAL(triggered(bool)), this, SLOT(updateAnimation()));
    connect(m_astralAnimationAction, SIGNAL(triggered(bool)), this, SLOT(updateAnimation()));
	connect(m_fullScreenAction, SIGNAL(triggered(bool)), m_globalVideoWidget, SLOT(manageFullScreen()));
	connect(m_clearAction, SIGNAL(triggered(bool)), this, SLOT(clearPlaylist()));
	connect(m_infoAction, SIGNAL(triggered(bool)), this, SLOT(showInfo()));
	connect(m_aboutPigmendAction, SIGNAL(triggered(bool)), m_aboutPlayer, SLOT(show()));
	connect(m_exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
	connect(m_smallWindowAction, SIGNAL(triggered(bool)), this, SLOT(setWindowSize()));
	connect(m_middleWindowAction, SIGNAL(triggered(bool)), this, SLOT(setWindowSize()));
	connect(m_normalWindowAction, SIGNAL(triggered(bool)), this, SLOT(setWindowSize()));
	connect(m_wideWindowAction, SIGNAL(triggered(bool)), this, SLOT(setWindowSize()));
	connect(m_maximizeAction, SIGNAL(triggered(bool)), this, SLOT(setWindowSize()));
    connect(m_preferencesAction, SIGNAL(triggered(bool)), m_preferences, SLOT(showPreferences()));

	// ui operations
	connect(ui->addFileButton, SIGNAL(clicked(bool)), m_mediaFile, SLOT(openFile()));
	connect(ui->addFolderButton, SIGNAL(clicked(bool)), m_mediaFile, SLOT(openFolder()));
	connect(ui->playButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(play()));
	connect(ui->pauseButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(pause()));
	connect(ui->stopButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(stop()));
	connect(ui->nextButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(nextForced()));
	connect(ui->prevButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(prev()));
    connect(ui->fullScreenButton, SIGNAL(clicked(bool)), this, SLOT(toggleVideoWidgetFullscreen()));
	connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearPlaylist()));
    connect(ui->deleteItemButton, SIGNAL(clicked(bool)), this, SLOT(removeItemFromPlaylist()));
    connect(&m_playlist, SIGNAL(activatePlaylist(int,int)), this, SLOT(onPlaylistDoubleClicked(int,int)));
	connect(ui->progressSlider, SIGNAL(sliderMoved(int)), m_playerControls, SLOT(seek(int)));
	connect(m_sliderInFullScreen, SIGNAL(sliderMoved(int)), m_playerControls, SLOT(seek(int)));
	connect(this, SIGNAL(progressSliderValueChanged(int)), m_playerControls, SLOT(seek(int)));
	connect(ui->fast2Button, SIGNAL(clicked(bool)), m_playerControls, SLOT(fastForward()));
	connect(ui->fast4Button, SIGNAL(clicked(bool)), m_playerControls, SLOT(fastForward()));
	connect(ui->repeatButton, SIGNAL(toggled(bool)), this, SLOT(onRepeatButton()));
	connect(ui->shuffleButton, SIGNAL(clicked(bool)), this, SLOT(onShuffleButton()));
	connect(ui->searchButton, SIGNAL(clicked(bool)), m_search, SLOT(show()));
	connect(ui->searchButton, SIGNAL(clicked(bool)), m_search, SLOT(setStartTips()));
	connect(ui->volumeUpButton, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonUpChanged()));
	connect(ui->volumeDownButton, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonDownChanged()));
	connect(ui->muteButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(setVolumeMuted()));
	connect(ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeSliderValueChanged()));
	connect(m_volumeSliderInFullScreen, SIGNAL(valueChanged(int)), this, SLOT(onVolumeSliderValueChanged()));
	connect(ui->showHidePlaylistButton, SIGNAL(clicked(bool)), this, SLOT(showHidePlaylist()));
    connect(&m_playlist, SIGNAL(removeActionTriggered()), this, SLOT(removeItemFromPlaylist()));
    connect(ui->playlistTabWidget, SIGNAL(currentChanged(int)), this, SLOT(playlistTabChanged(int)));
    connect(ui->playlistTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closePlaylistTab(int)));
    connect(ui->playlistTabWidget, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(renamePlaylistTab(int)));

    // full screen
	connect(m_playInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(play()));
	connect(m_pauseInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(pause()));
	connect(m_stopInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(stop()));
	connect(m_nextInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(nextForced()));
	connect(m_prevInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(prev()));
	connect(m_disableFullScreen, SIGNAL(clicked(bool)), this, SLOT(toggleVideoWidgetFullscreen()));
	connect(m_volumeUpInFullScreen, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonUpChanged()));
	connect(m_volumeDownInFullScreen, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonDownChanged()));
	connect(m_volumeMuteInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(setVolumeMuted()));
	connect(m_globalVideoWidget, SIGNAL(fullScreenChanged(bool)), this, SLOT(hideControlPanelInNormalMode(bool)));
    connect(m_videoWidget, SIGNAL(videoWidgetToggleRequest()), this, SLOT(toggleVideoWidgetFullscreen()));
    connect(m_globalVideoWidget, SIGNAL(videoWidgetToggleRequest()), this, SLOT(toggleVideoWidgetFullscreen()));
    connect(this, SIGNAL(videoFullscreenToggled()), m_videoWidget, SLOT(onFullscreenToggled()));
    connect(m_videoControlTimer, SIGNAL(timeout()), this, SLOT(hideVideoControlPanel()));

	// internal operations
	connect(m_playerControls, SIGNAL(currentMediaItem(QString)), this, SLOT(focusItem(QString)));
    connect(m_playerControls, SIGNAL(titleChanged(QStringList*)), this, SLOT(updateTitle(QStringList*)));
	connect(m_playerControls, SIGNAL(durationChanged(int)), this, SLOT(updateDuration(int)));
	connect(m_mediaFile, SIGNAL(filesChosen()), this, SLOT(updatePlaylist()));
	connect(m_playerControls, SIGNAL(timeProgressChanged(int)), this, SLOT(updateTimeProgress(int)));
    connect(m_search, SIGNAL(matchesFound(QString)), m_playerControls, SLOT(setMediaFile(QString)));
    connect(m_mediaFile, SIGNAL(filesFound(int,int,bool)), this, SLOT(updateIndexedData(int,int,bool)));
	connect(this, SIGNAL(changeVolume(int)), m_playerControls, SIGNAL(setVolumeToPlayer(int)));
	connect(m_playerControls, SIGNAL(changeVolumeValue(float)), this, SLOT(updateVolumeValue(float)));
	connect(m_playerControls, SIGNAL(mousePositionChanged(QPoint*)), this, SLOT(updateCursorPosition(QPoint*)));
	connect(m_playerControls, SIGNAL(volumeMutedChanged(bool)), this, SLOT(onVolumeMute(bool)));
	connect(m_timer, SIGNAL(timeout()), this, SLOT(onPlaylistUpdate()));
	connect(m_playerControls, SIGNAL(isMusicContent(bool)), this, SLOT(onContentTypeChange(bool)));
	connect(m_playerControls, SIGNAL(paused(bool)), this, SLOT(stopAnimation(bool)));
    connect(this, SIGNAL(closeMainWindow()), m_playerControls, SLOT(interrupt()));
    connect(m_renameDialog, SIGNAL(renamed(QString,int)), this, SLOT(playlistTabRenamed(QString,int)));

	setGeometry(screen_size.x(), screen_size.y(), m_global_width / 2, m_global_height / 2);
}

MediaPlayer::~MediaPlayer()
{
	deleteObjectsInFullScreen();

	delete ui;
	delete m_playerControls;
	delete m_mediaFile;
	delete m_search;
    delete m_renameDialog;
	delete m_aboutPlayer;
	delete m_movieLoading;
	delete m_movieDone;
	delete m_menuBar;
	delete m_playSC;
	delete m_nextSC;
	delete m_prevSC;
	delete m_stopSC;
    delete m_videoControlTimer;
	delete m_timer;
	delete m_movieMusic;
    delete addPlaylistButton;
}

void MediaPlayer::deleteObjectsInFullScreen()
{
	delete m_musicLabel;
	delete m_globalVideoWidget;
	delete m_videoWidget;
	delete m_videoGridLayout;
	delete m_videoControlGridLayout;
	delete m_videoProgressLayout;
	delete m_videoTitleLayout;
	delete m_videoScreenLayout;
	delete m_videoButtonsLayout;
	delete m_controlVLayout;
	delete m_playInFullScreen;
	delete m_pauseInFullScreen;
	delete m_stopInFullScreen;
	delete m_nextInFullScreen;
	delete m_prevInFullScreen;
	delete m_disableFullScreen;
	delete m_volumeUpInFullScreen;
	delete m_volumeDownInFullScreen;
	delete m_volumeMuteInFullScreen;
	delete m_spaceInFullScreenButtonsLeft;
	delete m_spaceInFullScreenButtonsRight;
	delete m_sliderInFullScreen;
	delete m_volumeSliderInFullScreen;
	delete m_titleInFullScreen;
	delete m_progressTimeInFullScreen;
	delete m_durationInFullScreen;
}

void MediaPlayer::unfocusButtons()
{
    ui->addFileButton->setFocusPolicy(Qt::NoFocus);
    ui->addFolderButton->setFocusPolicy(Qt::NoFocus);
    ui->clearButton->setFocusPolicy(Qt::NoFocus);
    ui->deleteItemButton->setFocusPolicy(Qt::NoFocus);
    ui->fast2Button->setFocusPolicy(Qt::NoFocus);
    ui->fast4Button->setFocusPolicy(Qt::NoFocus);
    ui->fullScreenButton->setFocusPolicy(Qt::NoFocus);
    ui->muteButton->setFocusPolicy(Qt::NoFocus);
    ui->nextButton->setFocusPolicy(Qt::NoFocus);
    ui->pauseButton->setFocusPolicy(Qt::NoFocus);
    ui->playButton->setFocusPolicy(Qt::NoFocus);
    ui->prevButton->setFocusPolicy(Qt::NoFocus);
    ui->repeatButton->setFocusPolicy(Qt::NoFocus);
    ui->searchButton->setFocusPolicy(Qt::NoFocus);
    ui->stopButton->setFocusPolicy(Qt::NoFocus);
    ui->volumeDownButton->setFocusPolicy(Qt::NoFocus);
    ui->volumeUpButton->setFocusPolicy(Qt::NoFocus);
    ui->shuffleButton->setFocusPolicy(Qt::NoFocus);
    ui->showHidePlaylistButton->setFocusPolicy(Qt::NoFocus);
    ui->progressSlider->setFocusPolicy(Qt::NoFocus);
    ui->volumeSlider->setFocusPolicy(Qt::NoFocus);
    addPlaylistButton->setFocusPolicy(Qt::NoFocus);
}

bool MediaPlayer::eventFilter(QObject* watched, QEvent* event)
{
	switch (event->type())
	{
		case QEvent::KeyPress:
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			switch (keyEvent->key())
			{
				case Qt::Key_Right:
					if (m_globalVideoWidget->isFullScreen())
					{
						m_sliderInFullScreen->setValue(m_sliderInFullScreen->value() + SLIDER_STEP);
						ui->progressSlider->setValue(m_sliderInFullScreen->value());
					}
					else
					{
						ui->progressSlider->setValue(ui->progressSlider->value() + SLIDER_STEP);
						m_sliderInFullScreen->setValue(ui->progressSlider->value());
					}

					emit progressSliderValueChanged(ui->progressSlider->value());
					break;
				case Qt::Key_Left:
					if (m_globalVideoWidget->isFullScreen())
					{
						m_sliderInFullScreen->setValue(m_sliderInFullScreen->value() - SLIDER_STEP);
						ui->progressSlider->setValue(m_sliderInFullScreen->value());
					}
					else
					{
						ui->progressSlider->setValue(ui->progressSlider->value() - SLIDER_STEP);
						m_sliderInFullScreen->setValue(ui->progressSlider->value());
					}

					emit progressSliderValueChanged(ui->progressSlider->value());
					break;
				case Qt::Key_Up:
					if (m_globalVideoWidget->isFullScreen())
					{
						m_volumeSliderInFullScreen->setValue(m_volumeSliderInFullScreen->value() + SLIDER_STEP);
						ui->volumeSlider->setValue(m_volumeSliderInFullScreen->value());
					}
					else
					{
						ui->volumeSlider->setValue(ui->volumeSlider->value() + SLIDER_STEP);
						m_volumeSliderInFullScreen->setValue(ui->volumeSlider->value());
					}
					break;
				case Qt::Key_Down:
					if (m_globalVideoWidget->isFullScreen())
					{
						m_volumeSliderInFullScreen->setValue(m_volumeSliderInFullScreen->value() - SLIDER_STEP);
						ui->volumeSlider->setValue(m_volumeSliderInFullScreen->value());
					}
					else
					{
						ui->volumeSlider->setValue(ui->volumeSlider->value() - SLIDER_STEP);
						m_volumeSliderInFullScreen->setValue(ui->volumeSlider->value());
					}
					break;
                case Qt::Key_Space:
                    m_keyPressNumber++;

                    if (m_keyPressNumber == 1)
                    {
                        if (m_isPaused)
                            m_playerControls->play();
                        else
                            m_playerControls->pause();

                        QTimer::singleShot(500, this, SLOT(onKeyPressed()));
                    }
                    break;
                case Qt::Key_Delete:
                    m_keyPressNumber++;

                    if (m_keyPressNumber == 1)
                    {
                        removeItemFromPlaylist();
                        QTimer::singleShot(500, this, SLOT(onKeyPressed()));
                    }
                    break;
				case Qt::Key_1:
                    emit m_smallWindowAction->triggered(true);
					break;
				case Qt::Key_2:
                    emit m_middleWindowAction->triggered(true);
					break;
				case Qt::Key_3:
                    emit m_normalWindowAction->triggered(true);
					break;
				case Qt::Key_4:
                    emit m_wideWindowAction->triggered(true);
					break;
				case Qt::Key_5:
                    emit m_maximizeAction->triggered(true);
					break;
				default:
					break;
			}

            if ((keyEvent->key() == Qt::Key_Return && keyEvent->modifiers() == Qt::AltModifier) || keyEvent->key() == Qt::Key_F5)
            {
                m_keyPressNumber++;

                if (m_keyPressNumber == 1)
                {
                    this->toggleVideoWidgetFullscreen();
                    QTimer::singleShot(500, this, SLOT(onKeyPressed()));
                }
            }
            else if (keyEvent->key() == Qt::Key_O && keyEvent->modifiers() == Qt::CTRL)
            {
                m_keyPressNumber++;

                if (m_keyPressNumber == 1)
                {
                    m_mediaFile->openFile();
                    QTimer::singleShot(500, this, SLOT(onKeyPressed()));
                }
            }
            else if (keyEvent->key() == Qt::Key_P && keyEvent->modifiers() == Qt::CTRL)
            {
                m_keyPressNumber++;

                if (m_keyPressNumber == 1)
                {
                    m_mediaFile->openFolder();
                    QTimer::singleShot(500, this, SLOT(onKeyPressed()));
                }
            }
            else if (keyEvent->key() == Qt::Key_Q && keyEvent->modifiers() == Qt::CTRL)
            {
                m_keyPressNumber++;

                if (m_keyPressNumber == 1)
                {
                    this->close();
                    QTimer::singleShot(500, this, SLOT(onKeyPressed()));
                }
            }
            else if (keyEvent->key() == Qt::Key_M && keyEvent->modifiers() == Qt::CTRL)
            {
                m_keyPressNumber++;

                if (m_keyPressNumber == 1)
                {
                    m_playerControls->setVolumeMuted();
                    QTimer::singleShot(500, this, SLOT(onKeyPressed()));
                }
            }

			break;
		}
		case QEvent::MouseButtonPress:
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
			if (mouseEvent->button() == Qt::LeftButton && (watched->objectName() == "sliderInFullScreen" ||
				watched->objectName() == "progressSlider"))
			{
				if (m_globalVideoWidget->isFullScreen())
				{
					m_sliderInFullScreen->setValue(m_sliderInFullScreen->minimum() +
						((m_sliderInFullScreen->maximum() - m_sliderInFullScreen->minimum()) * mouseEvent->x()) /
						m_sliderInFullScreen->width());

					ui->progressSlider->setValue(m_sliderInFullScreen->value());
				}
				else
				{
					ui->progressSlider->setValue(ui->progressSlider->minimum() +
						((ui->progressSlider->maximum() - ui->progressSlider->minimum()) * mouseEvent->x()) /
						ui->progressSlider->width());

					m_sliderInFullScreen->setValue(ui->progressSlider->value());
				}

				emit progressSliderValueChanged(ui->progressSlider->value());
			}
			break;
		}
		default:
			break;
	}

	event->accept();

	return QMainWindow::eventFilter(watched, event);
}

void MediaPlayer::initPlaylist()
{
    addPlaylistButton = new QPushButton();
    addPlaylistButton->setIcon(QIcon(":/buttons/img/buttons/plus-16.png"));
    addPlaylistButton->setFlat(true);
    connect(addPlaylistButton, SIGNAL(clicked(bool)), this, SLOT(openNewPlaylistTab()));
    ui->playlistTabWidget->setCornerWidget(addPlaylistButton, Qt::TopRightCorner);

    // add initial tab playlist
    ui->playlistTabWidget->clear();
    playlists_str newPlaylist = m_playlist.createNewPlaylist();
    ui->playlistTabWidget->addTab(newPlaylist.playlistWidget, newPlaylist.tabName);
    ui->playlistTabWidget->currentWidget()->setObjectName(newPlaylist.tabId);
    ui->playlistTabWidget->setTabsClosable(false);
    m_playlist.setActivePlaylist(ui->playlistTabWidget->currentWidget()->objectName());
    m_playlist.makeShuffle(m_shuffleMode);
}

void MediaPlayer::openNewPlaylistTab()
{
    playlists_str newPlaylist = m_playlist.createNewPlaylist();
    int id = ui->playlistTabWidget->addTab(newPlaylist.playlistWidget, newPlaylist.tabName);
    ui->playlistTabWidget->setCurrentIndex(id);
    ui->playlistTabWidget->currentWidget()->setObjectName(newPlaylist.tabId);
    ui->playlistTabWidget->setTabsClosable(true);
    m_playlist.setActivePlaylist(ui->playlistTabWidget->currentWidget()->objectName());
    m_playlist.makeShuffle(m_shuffleMode);
}

void MediaPlayer::onKeyPressed()
{
    m_keyPressNumber = 0;
}

void MediaPlayer::resizeMovieLabel()
{
    QRect fullScreenSize = QGuiApplication::primaryScreen()->geometry();
    QRect thisScreenSize = this->geometry();

    float fullXPercent = fullScreenSize.width() / 100;
    float fullYPercent = fullScreenSize.height() / 100;
    float windowX = thisScreenSize.width();
    float windowY = thisScreenSize.height();
    float percentX = windowX / fullXPercent / 100;
    float percentY = windowY / fullYPercent / 100;
    float diffPercent = percentX > percentY ? percentY : percentX;

    m_movieMusic->setScaledSize(QSize(m_movieImageSize.width() * diffPercent, m_movieImageSize.height() * diffPercent));
}

void MediaPlayer::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    QRect fullScreenSize = QGuiApplication::primaryScreen()->geometry();

    float fullXPercent = fullScreenSize.width() / 100;
    float fullYPercent = fullScreenSize.height() / 100;
    float windowX = event->size().width();
    float windowY = event->size().height();
    float percentX = windowX / fullXPercent / 100;
    float percentY = windowY / fullYPercent / 100;
    float diffPercent = percentX > percentY ? percentY : percentX;

#if DEBUG
    qDebug() << "Resizing - " << event->size().width() << " x " << event->size().height();
#endif

    m_movieMusic->setScaledSize(QSize(m_movieImageSize.width() * diffPercent, m_movieImageSize.height() * diffPercent));

    if (!ui->playlistLabel->isHidden())
        m_menuBar->setFixedWidth(ui->playlistTabWidget->geometry().width());
}

void MediaPlayer::initMenu()
{
	m_menuBar = new QMenuBar;

	m_menuBar->setStyleSheet("selection-background-color: rgb(0, 170, 127); background-color: rgb(0, 170, 127, 125); color: #ffffff");
	m_menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

	// file
	m_filemenu = m_menuBar->addMenu("File");
	m_addFileAction = m_filemenu->addAction(QIcon(":/buttons/img/buttons/add-file-16.ico"), "Add file");
	m_addFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
	m_addFolderAction = m_filemenu->addAction(QIcon(":/buttons/img/buttons/add-folder-16.ico"), "Add folder");
	m_addFolderAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
	m_filemenu->addSeparator();
	m_clearAction = m_filemenu->addAction(QIcon(":/buttons/img/buttons/delete-column-16.ico"), "Clear playlist");
	m_filemenu->addSeparator();
	m_exitAction = m_filemenu->addAction("Exit");
	m_exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    // edit
    m_editmenu = m_menuBar->addMenu("Edit");
    m_preferencesAction = m_editmenu->addAction(QIcon(PREFERENCES_ICON_PATH);

	// view
	m_viewmenu = m_menuBar->addMenu("View");
	m_thememenu = m_viewmenu->addMenu(QIcon(":/buttons/img/buttons/paint-brush-16.ico"), "Theme");
	m_windowMenu = m_viewmenu->addMenu(QIcon(":/buttons/img/buttons/window-5-16.ico"), "Window size");
	m_animation_menu = m_viewmenu->addMenu(QIcon(":/buttons/img/buttons/audio-spectrum-16.ico"), "Animation");

    // view theme
	m_orangeAction = m_thememenu->addAction(QIcon(":/custom/img/custom/orangemend.ico"), "Orange Mend");
	m_blueAction = m_thememenu->addAction(QIcon(":/custom/img/custom/bluemend.ico"), "Blue Mend");
	m_greyAction = m_thememenu->addAction(QIcon(":/custom/img/custom/greymend.ico"), "Grey Mend");
	m_darkGreyAction = m_thememenu->addAction(QIcon(":/custom/img/custom/darkgreymend.ico"), "Dark Grey Mend");
	m_orangeAction->setObjectName("orange mend");
	m_blueAction->setObjectName("blue mend");
	m_greyAction->setObjectName("grey mend");
	m_darkGreyAction->setObjectName("dark grey mend");
	m_fullScreenAction = m_viewmenu->addAction(QIcon(":/buttons/img/buttons/fullscreen-enter-16.ico"), "Full Screen");
	m_fullScreenAction->setShortcut(QKeySequence(Qt::Key_F5));
	m_viewmenu->addSeparator();

    // view window size
	m_smallWindowAction = m_windowMenu->addAction("Small");
	m_smallWindowAction->setShortcut(QKeySequence(Qt::Key_1));
	m_middleWindowAction = m_windowMenu->addAction("Middle");
	m_middleWindowAction->setShortcut(QKeySequence(Qt::Key_2));
	m_normalWindowAction = m_windowMenu->addAction("Normal");
	m_normalWindowAction->setShortcut(QKeySequence(Qt::Key_3));
	m_wideWindowAction = m_windowMenu->addAction("Wide");
	m_wideWindowAction->setShortcut(QKeySequence(Qt::Key_4));
	m_maximizeAction = m_windowMenu->addAction("Maximum");
	m_maximizeAction->setShortcut(QKeySequence(Qt::Key_5));

    // view animation
	m_noneAnimationAction = m_animation_menu->addAction("None");
	m_defaultAnimationAction = m_animation_menu->addAction("Default");
	m_equalizerAnimationAction = m_animation_menu->addAction("Equalizer");
    m_radioAnimationAction = m_animation_menu->addAction("Equalizer Bricks");
    m_astralAnimationAction = m_animation_menu->addAction("Astral");
	m_noneAnimationAction->setObjectName("noneAnimation");
	m_defaultAnimationAction->setObjectName("defaultAnimation");
	m_equalizerAnimationAction->setObjectName("equalizerAnimation");
    m_radioAnimationAction->setObjectName("equalizerBricksAnimations");
    m_astralAnimationAction->setObjectName("astralAnimations");

	// about
	m_helpmenu = m_menuBar->addMenu("Help");
	m_infoAction = m_helpmenu->addAction(QIcon(":/buttons/img/buttons/author.ico"), "Author");
	m_aboutPigmendAction = m_helpmenu->addAction(QIcon(":/buttons/img/buttons/info-2-16.ico"), "About Pigmend");

	ui->menuLayout->addWidget(m_menuBar);
	ui->menuLayout->setAlignment(m_menuBar, Qt::AlignRight);
}

void MediaPlayer::adjustVideoWidget()
{
	// adjust video widget
	m_globalVideoWidget = new VideoWidget(false, this);
	m_videoWidget = new VideoWidget(true, m_globalVideoWidget);
	m_videoGridLayout = new QGridLayout(m_globalVideoWidget);
	m_videoControlGridLayout = new QGridLayout;
	m_videoProgressLayout = new QHBoxLayout;
	m_videoTitleLayout = new QHBoxLayout;
	m_videoScreenLayout = new QHBoxLayout;
	m_videoButtonsLayout = new QHBoxLayout;
	m_controlVLayout = new QVBoxLayout;
	m_playInFullScreen = new QPushButton;
	m_pauseInFullScreen = new QPushButton;
	m_stopInFullScreen = new QPushButton;
	m_nextInFullScreen = new QPushButton;
	m_prevInFullScreen = new QPushButton;
	m_disableFullScreen = new QPushButton;
	m_volumeUpInFullScreen = new QPushButton;
	m_volumeDownInFullScreen = new QPushButton;
	m_volumeMuteInFullScreen = new QPushButton;
	m_spaceInFullScreenButtonsLeft = new QSpacerItem(0, 0);
	m_spaceInFullScreenButtonsRight = new QSpacerItem(0, 0);
	m_sliderInFullScreen = new QSlider(Qt::Horizontal);
	m_volumeSliderInFullScreen = new QSlider(Qt::Horizontal);
	m_titleInFullScreen = new QLabel;
	m_progressTimeInFullScreen = new QLabel;
	m_durationInFullScreen = new QLabel;
	m_musicLabel = new QLabel;

    m_musicLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_musicLabel->setAlignment(Qt::AlignCenter);
	m_musicLabel->setMovie(m_movieMusic);
	m_movieMusic->start();
	m_musicLabel->hide();
    QImageReader movieImg(m_movieMusic->fileName());
    m_movieImageSize = movieImg.size();
    resizeMovieLabel();

	m_volumeSliderInFullScreen->setBaseSize(int(m_global_width * 0.2), 0);

	m_progressTimeInFullScreen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	m_durationInFullScreen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    // buttons size and m_style policy
	m_playInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	m_pauseInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	m_stopInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	m_nextInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	m_prevInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	m_disableFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

	m_playInFullScreen->setFlat(true);
	m_pauseInFullScreen->setFlat(true);
	m_stopInFullScreen->setFlat(true);
	m_nextInFullScreen->setFlat(true);
	m_prevInFullScreen->setFlat(true);
	m_disableFullScreen->setFlat(true);
	m_volumeUpInFullScreen->setFlat(true);
	m_volumeDownInFullScreen->setFlat(true);
	m_volumeMuteInFullScreen->setFlat(true);

	m_playInFullScreen->setIcon(QIcon(":/buttons/img/buttons/play-16.ico"));
	m_pauseInFullScreen->setIcon(QIcon(":/buttons/img/buttons/media-pause-16.ico"));
	m_stopInFullScreen->setIcon(QIcon(":/buttons/img/buttons/stop-16.ico"));
	m_nextInFullScreen->setIcon(QIcon(":/buttons/img/buttons/media-skip-forward-16.ico"));
	m_prevInFullScreen->setIcon(QIcon(":/buttons/img/buttons/media-skip-backward-16.ico"));
	m_disableFullScreen->setIcon(QIcon(":/buttons/img/buttons/fullscreen-exit-16.ico"));
	m_volumeUpInFullScreen->setIcon(QIcon(":/buttons/img/buttons/volume-up-4-16.png"));
	m_volumeDownInFullScreen->setIcon(QIcon(":/buttons/img/buttons/volume-down-5-16.png"));
	m_volumeMuteInFullScreen->setIcon(QIcon(":/buttons/img/buttons/mute-2-16.ico"));

	m_volumeMuteInFullScreen->setCheckable(true);

	ui->videoLayout->addWidget(m_globalVideoWidget);

	m_videoGridLayout->setMargin(0);
	m_videoGridLayout->addLayout(m_videoTitleLayout, 0, 0);
	m_videoGridLayout->addLayout(m_videoScreenLayout, 1, 0);
	m_videoGridLayout->addLayout(m_videoControlGridLayout, 2, 0);

	m_videoScreenLayout->addWidget(m_videoWidget);
	m_videoScreenLayout->addWidget(m_musicLabel);

	m_videoControlGridLayout->addLayout(m_videoProgressLayout, 0, 0);
	m_videoControlGridLayout->addLayout(m_videoButtonsLayout, 1, 0);

	m_videoProgressLayout->addWidget(m_progressTimeInFullScreen);
	m_videoProgressLayout->addWidget(m_sliderInFullScreen);
	m_videoProgressLayout->addWidget(m_durationInFullScreen);

	m_videoButtonsLayout->addWidget(m_volumeMuteInFullScreen, 0, Qt::AlignLeft);
	m_videoButtonsLayout->addWidget(m_volumeDownInFullScreen, 0, Qt::AlignLeft);
	m_videoButtonsLayout->addWidget(m_volumeSliderInFullScreen);
	m_videoButtonsLayout->addWidget(m_volumeUpInFullScreen, 0, Qt::AlignLeft);
	m_videoButtonsLayout->addSpacerItem(m_spaceInFullScreenButtonsLeft);
	m_videoButtonsLayout->addWidget(m_stopInFullScreen);
	m_videoButtonsLayout->addWidget(m_prevInFullScreen);
	m_videoButtonsLayout->addWidget(m_playInFullScreen);
	m_videoButtonsLayout->addWidget(m_pauseInFullScreen);
	m_videoButtonsLayout->addWidget(m_nextInFullScreen);
	m_videoButtonsLayout->addSpacerItem(m_spaceInFullScreenButtonsRight);
	m_videoButtonsLayout->addWidget(m_disableFullScreen, 0, Qt::AlignRight);
	m_videoTitleLayout->addWidget(m_titleInFullScreen, 0, Qt::AlignCenter);

	hideControlPanelInNormalMode(true);
}

void MediaPlayer::initAnimations()
{
	m_movieLoading = new QMovie(":/custom/img/custom/loader.gif");
	m_movieDone = new QMovie(":/custom/img/custom/okload.gif");

	ui->loadingLabel->setMovie(m_movieLoading);
	m_movieLoading->start();

    ui->indexInfoLabel->setText("Indexing media on this device...");

	QString pathMusicAnimation = m_xmldp.getAudioAnimation(static_cast<char*>(config_get_data(ANIMATIONS_CONFIG, m_conf_data)));

	if (pathMusicAnimation.isEmpty())
		qWarning() << __FUNCTION__ << ": No music animation";

	m_movieMusic = new QMovie(pathMusicAnimation);
}

void MediaPlayer::onPlaylistUpdate()
{
	int row = 0;

	m_timer->stop();
    m_playlist.getCurrentPlaylistWidget()->setRowCount(row);
    m_playlist.getCurrentPlaylistWidget()->setColumnCount(PLAYLIST_COLUMN_COUNT);

	QStringList playlistHeader;
	playlistHeader << "#" << "Name" << "Time";
    m_playlist.getCurrentPlaylistWidget()->setHorizontalHeaderLabels(playlistHeader);
    m_playlist.getCurrentPlaylistWidget()->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_playlist.getCurrentPlaylistWidget()->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_playlist.getCurrentPlaylistWidget()->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    m_playlist.getCurrentPlaylistWidget()->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	// insert filenames from QMap as items to playlist widget
    for (auto it = m_playlist.getCurrentPlaylistContainer()->begin(); it != m_playlist.getCurrentPlaylistContainer()->end(); ++it)
	{
		QString item = it.key();
        m_playlist.getCurrentPlaylistWidget()->insertRow(row);
        m_playlist.getCurrentPlaylistWidget()->setItem(row, PLAYLIST_NUM_COLUMN, new QTableWidgetItem(QString::number(row + 1) + "."));
        m_playlist.getCurrentPlaylistWidget()->setItem(row, PLAYLIST_NAME_COLUMN, new QTableWidgetItem(item));
        m_playlist.getCurrentPlaylistWidget()->setItem(row, PLAYLIST_TIME_COLUMN, new QTableWidgetItem(m_playlist.getAudioTime(it.value())));
		++row;
	}

    ui->allItemsLabel->setFrameStyle(QFrame::StyledPanel);
    ui->allItemsLabel->setText("<font color=\"white\">Amount: </font>" + QString::number(m_playlist.getCurrentPlaylistWidget()->rowCount()));   // set count of tracks

	// if added new files - shuffle it all
	if (m_shuffleMode)
    {
		m_playerControls->setShuffleMode(true);

        if (m_isUpdateOnRemove)
            m_playerControls->nextForced();
    }

	// prepare first media file
	// while loaded playlist first time - prepare first file for playing
	// and don't prepare first file after adding files to existing playlist
	// because then current media file stops playing and sets first file as media file
    if (!m_isPlaylistLoaded && !m_playlist.m_plData->isEmpty())
	{
        QListWidgetItem* item = new QListWidgetItem(m_playlist.m_plData->value(m_playlist.m_plData->firstKey()));
		m_playerControls->setFirstFile(item);
		m_isPlaylistLoaded = true;
	}

	ui->totalTimeLabel->setText("<font color=\"white\">Total time: </font>" + m_playlist.getAudioTotalTime());

    if (!m_playlist.getCurrentPlaylistWidget()->isHidden())
        m_menuBar->setFixedWidth(ui->playlistTabWidget->geometry().width());

    focusItem(m_playerControls->getCurrentMediaItem());
    m_isUpdateOnRemove = false;
}

void MediaPlayer::updatePlaylist()
{
	ui->totalTimeLabel->setText("Loading... Please, wait");
	// need to simulate pause (0 - because the time to send signal timeout() is enough for pause)
	// to set text "Loading..." to the label before starting update
	m_timer->start(0);
}

void MediaPlayer::onPlaylistDoubleClicked(int row, int column)
{
	column = PLAYLIST_NAME_COLUMN;
	ui->progressSlider->setValue(0);
	m_sliderInFullScreen->setValue(0);
    QString item = m_playlist.getCurrentPlaylistWidget(true)->item(row, column)->text();
	m_playerControls->setMediaFile(item);
}

void MediaPlayer::updateTitle(QStringList* title)
{
	// set metadata: artist, title, genre and release date
    QString title_line, delimiter(" ⋄ ");
	int index = 0;
	int counter = title->count();

	if (title->isEmpty())
		title_line = "no metadata";
	else
	{
		while (counter)
		{
			QString title_item = title->at(index);
			if (!title_item.isEmpty() && !index)
				title_line = title->at(index);
			else if (title_item.isEmpty() && !index)
				title_line = "unknown";
			if (!title_item.isEmpty() && index)
				title_line += delimiter + title->at(index);

			index++;
			counter--;
		}
	}

	ui->titleLabel->setText(title_line);
	m_titleInFullScreen->setText(title_line);
}

void MediaPlayer::updateDuration(int duration)
{
	int seconds = (duration/1000) % 60;
	int minutes = (duration/60000) % 60;
	int hours = (duration/3600000) % 24;

	QTime time(hours, minutes,seconds);
	ui->durationLabel->setText(time.toString());
	m_durationInFullScreen->setText(time.toString());
	ui->progressSlider->setMaximum(duration / 1000);   // set maximum value of slider progress
	m_sliderInFullScreen->setMaximum(duration / 1000);
}

void MediaPlayer::updateTimeProgress(int playTime)
{
	int seconds = (playTime/1000) % 60;
	int minutes = (playTime/60000) % 60;
	int hours = (playTime/3600000) % 24;

	QTime time(hours, minutes,seconds);
	ui->progressTimeLabel->setText(time.toString());
	m_progressTimeInFullScreen->setText(time.toString());
	ui->progressSlider->setValue(playTime / 1000);     // set current progress value
	m_sliderInFullScreen->setValue(playTime / 1000);
}

void MediaPlayer::focusItem(QString path)
{
	int row = 0;
    for (auto it = m_playlist.m_plData->begin(); it != m_playlist.m_plData->end(); ++it)
	{
#ifdef WIN32
		QString canonical_path = "file:///" + it.value();
#elif unix
		QString canonical_path = "file://" + it.value();
#endif

		if (path == canonical_path)
		{
          m_playlist.getCurrentPlaylistWidget(true)->selectRow(row);
          m_playlist.getCurrentPlaylistWidget(true)->scrollToItem(m_playlist.getCurrentPlaylistWidget(true)->selectedItems().at(0));
		  ui->currentItemLabel->setText(QString::number(row + 1));              // set number of current track
		}
		++row;
	}
}

void MediaPlayer::clearPlaylist()
{
	// clear palylist
    if (m_playlist.getCurrentPlaylistWidget()->rowCount() == 0)
		return;

    m_playlist.getCurrentPlaylistWidget()->clear();
	if (m_playlist.clearPlaylistData() != 0)
		qCritical() << "Can't clear playlist data" << endl;

    updatePlaylist();
	// set false
	// when new data will be added to empty playlist then enable ability to prepare first file
	m_isPlaylistLoaded = false;
}

void MediaPlayer::onShuffleButton()
{
	m_shuffleMode = ui->shuffleButton->isChecked();
    ui->shuffleButton->setStyleSheet(m_shuffleMode ? m_style->buttonCheckedTheme : m_style->backcolor);
	m_playerControls->setShuffleMode(m_shuffleMode);
}

void MediaPlayer::onRepeatButton()
{
    ui->repeatButton->setStyleSheet(ui->repeatButton->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
	m_playerControls->setRepeatMode(ui->repeatButton->isChecked());
}

void MediaPlayer::updateTheme()
{
	QString theme_name = this->sender() ? this->sender()->objectName() : "";
    QString theme_file(getDBXML());

	theme_file.append(static_cast<char*>(config_get_data(THEME_CONFIG, m_conf_data)));

    m_style = m_xmldp.getStylesXML(theme_file, theme_name);

    if (!m_style)
	{
		qWarning() << __FUNCTION__ << ": nullptr detected" << endl;
		return;
	}

	if (!theme_name.isEmpty() && m_xmldp.setStylesXML(theme_file, theme_name))
	{
		qWarning() << __FUNCTION__ << ": can't save " << theme_name << " theme to xml" << endl;
		return;
	}

    m_search->updateTheme(m_style);
    m_aboutPlayer->updateTheme(m_style);
    m_renameDialog->updateTheme(m_style);
    m_playlist.updateTheme(m_style);
    PluginDialog::updateTheme(m_style);

    ui->addFileButton->setStyleSheet(m_style->backcolor);
    ui->addFolderButton->setStyleSheet(m_style->backcolor);
    ui->allItemsLabel->setStyleSheet(m_style->color);
    ui->clearButton->setStyleSheet(m_style->backcolor);
    ui->deleteItemButton->setStyleSheet(m_style->backcolor);
    ui->currentItemLabel->setStyleSheet(m_style->color);
    ui->fast2Button->setStyleSheet(m_style->backcolor);
    ui->fast4Button->setStyleSheet(m_style->backcolor);
    ui->fullScreenButton->setStyleSheet(m_style->backcolor);
    ui->nextButton->setStyleSheet(m_style->backcolor);
    ui->pauseButton->setStyleSheet(ui->pauseButton->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    ui->playButton->setStyleSheet(ui->playButton->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    ui->playlistTabWidget->setStyleSheet(m_style->playlistTabsTheme);
    ui->playlistTabWidget->tabBar()->setStyleSheet(m_style->playlistTabsTheme);
    ui->playlistTabWidget->cornerWidget()->setStyleSheet(m_style->playlistTabsTheme);
    ui->prevButton->setStyleSheet(m_style->backcolor);
    ui->progressSlider->setStyleSheet(m_style->progressSliderTheme);
    ui->volumeSlider->setStyleSheet(m_style->volumeSliderTheme);
    ui->searchButton->setStyleSheet(m_style->backcolor);
    ui->stopButton->setStyleSheet(m_style->backcolor);
    ui->volumeUpButton->setStyleSheet(m_style->backcolor);
    ui->volumeDownButton->setStyleSheet(m_style->backcolor);
    ui->muteButton->setStyleSheet(ui->muteButton->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    ui->trademarkInfoLabel->setStyleSheet(m_style->color);
    ui->titleLabel->setStyleSheet(m_style->color);
    ui->indexInfoLabel->setStyleSheet(m_style->color);
    ui->showHidePlaylistButton->setStyleSheet(m_style->backcolor);
    ui->shuffleButton->setStyleSheet(ui->shuffleButton->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    ui->repeatButton->setStyleSheet(ui->repeatButton->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    ui->underPlaylistLabel->setStyleSheet(m_style->color);
    ui->totalTimeLabel->setStyleSheet(m_style->color);
    m_menuBar->setStyleSheet(m_style->menucolor);

	// full screen mode
    m_sliderInFullScreen->setStyleSheet(m_style->progressSliderTheme);
    m_volumeSliderInFullScreen->setStyleSheet(m_style->volumeSliderTheme);
    m_titleInFullScreen->setStyleSheet(m_style->color);
    m_durationInFullScreen->setStyleSheet(m_style->color);
    m_progressTimeInFullScreen->setStyleSheet(m_style->color);
    m_playInFullScreen->setStyleSheet(m_playInFullScreen->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    m_pauseInFullScreen->setStyleSheet(m_pauseInFullScreen->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    m_stopInFullScreen->setStyleSheet(m_style->backcolor);
    m_nextInFullScreen->setStyleSheet(m_style->backcolor);
    m_prevInFullScreen->setStyleSheet(m_style->backcolor);
    m_disableFullScreen->setStyleSheet(m_style->backcolor);
    m_volumeUpInFullScreen->setStyleSheet(m_style->backcolor);
    m_volumeDownInFullScreen->setStyleSheet(m_style->backcolor);
    m_volumeMuteInFullScreen->setStyleSheet(m_volumeMuteInFullScreen->isChecked() ? m_style->buttonCheckedTheme : m_style->backcolor);
    m_preferences->updateTheme(m_style->preferencesTheme);
}

void MediaPlayer::updateAnimation()
{
	m_movieMusic->stop();
	m_musicLabel->clear();
	m_musicLabel->setStyleSheet("");

	if (!this->sender() || this->sender()->objectName().isNull() || this->sender()->objectName().isEmpty() ||
		this->sender()->objectName() == constants::NONE_ANIMATION)
	{
		m_musicLabel->setStyleSheet("image: url(:/custom/img/custom/pigmendback.png)");
	}
	else
	{
        m_movieMusic->setFileName(m_xmldp.getAudioAnimation(static_cast<char*>(config_get_data(ANIMATIONS_CONFIG, m_conf_data)),
            this->sender()->objectName()));
        QImageReader movieImg(m_movieMusic->fileName());
        m_movieImageSize = movieImg.size();
        resizeMovieLabel();

		m_musicLabel->setMovie(m_movieMusic);

        if (!m_isPaused)
            m_movieMusic->start();
        else
        {
            m_movieMusic->start();
            m_movieMusic->stop();
        }
	}
}

void MediaPlayer::showInfo()
{
    QDesktopServices::openUrl(QUrl(m_aboutPlayer->getInfoAbout()->author_url));
}

void MediaPlayer::updateIndexedData(int audio_count, int video_count, bool status)
{
	if (status)
	{
        ui->indexInfoLabel->setText("Media available on this device:");
		m_movieLoading->stop();
		ui->loadingLabel->setMovie(m_movieDone);
		m_movieDone->start();
	}

	if (audio_count == 0)
        ui->indexAudioLabel->setText(tr("<img src=\":/custom/img/custom/headphones-48.png\" width=\"16\" height=\"16\"/> 0"));
	if (video_count == 0)
        ui->indexVideoLabel->setText(tr("<img src=\":/custom/img/custom/video-camera-100.png\" width=\"16\" height=\"16\"/> 0"));
	else
	{
        QString audio = "<img src=\":/custom/img/custom/headphones-48.png\" width=\"16\" height=\"16\"/> " + QString::number(audio_count);
        QString video = "<img src=\":/custom/img/custom/video-camera-100.png\" width=\"16\" height=\"16\" /> " + QString::number(video_count);
        ui->indexAudioLabel->setText(tr(audio.toStdString().c_str()));
        ui->indexVideoLabel->setText(tr(video.toStdString().c_str()));
	}

    if (!ui->playlistLabel->isHidden())
        m_menuBar->setFixedWidth(ui->playlistTabWidget->geometry().width());
}

void MediaPlayer::setWindowSize()
{
	QAction *actionSender = qobject_cast<QAction*>(sender()); // retrieve which action was clicked
	QString actionText = actionSender->text();
	QRect currentGeometry = geometry();

	showNormal();

	if (actionText == m_smallWindowAction->text())
		setGeometry(currentGeometry.x(), currentGeometry.y(), 400, 200);
	else if (actionText == m_middleWindowAction->text())
		setGeometry(currentGeometry.x(), currentGeometry.y(), 900, 400);
	else if (actionText == m_normalWindowAction->text())
		setGeometry(currentGeometry.x(), currentGeometry.y(), 1100, 600);
	else if (actionText == m_wideWindowAction->text())
		setGeometry(currentGeometry.x(), currentGeometry.y(), 1300, 500);
	else if (actionText == m_maximizeAction->text())
		showMaximized();
}

int MediaPlayer::volume() const
{
	qreal linearVolume;

	if (m_globalVideoWidget->isFullScreen())
	{
		linearVolume = QAudio::convertVolume(m_volumeSliderInFullScreen->value() / qreal(100),
			QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);
	}
	else
	{
		linearVolume = QAudio::convertVolume(ui->volumeSlider->value() / qreal(100),
		QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);
	}

	return qRound(linearVolume * 100);
}

void MediaPlayer::onVolumeSliderValueChanged()
{
	emit changeVolume(volume());
}

void MediaPlayer::onVolumeButtonUpChanged()
{
	int sliderValue = ui->volumeSlider->value();
	sliderValue += 10;
	ui->volumeSlider->setValue(sliderValue);
	m_volumeSliderInFullScreen->setValue(ui->volumeSlider->value());
}

void MediaPlayer::onVolumeButtonDownChanged()
{
	int sliderValue = ui->volumeSlider->value();
	sliderValue -= 10;
	ui->volumeSlider->setValue(sliderValue);
	m_volumeSliderInFullScreen->setValue(ui->volumeSlider->value());
}

void MediaPlayer::onVolumeMute(bool isMuted)
{
	if (isMuted)
	{
        m_volumeMuteInFullScreen->setChecked(true);
        ui->muteButton->setChecked(true);
        ui->muteButton->setStyleSheet(m_style->buttonCheckedTheme);
        m_volumeMuteInFullScreen->setStyleSheet(m_style->buttonCheckedTheme);
	}
	else
	{
        m_volumeMuteInFullScreen->setChecked(false);
        ui->muteButton->setChecked(false);
        ui->muteButton->setStyleSheet(m_style->backcolor);
        m_volumeMuteInFullScreen->setStyleSheet(m_style->backcolor);
	}
}

void MediaPlayer::updateVolumeValue(float volume)
{
	ui->volumeSlider->setValue(int(volume));
	m_volumeSliderInFullScreen->setValue(int(volume));
}

void MediaPlayer::updateCursorPosition(QPoint *position)
{
	if (m_globalVideoWidget->isFullScreen() && ((position->y() <= m_global_height &&
		position->y() >= (m_global_height - (m_global_height * 0.07))) ||
		(position->y() >= 0 && position->y() <= m_global_height * 0.04)))
	{
        m_videoControlTimer->stop();
		m_videoTitleLayout->setMargin(10);
		m_videoControlGridLayout->setMargin(10);
		m_spaceInFullScreenButtonsLeft->changeSize(int(m_global_width * 0.26), 0, QSizePolicy::Expanding);
		m_spaceInFullScreenButtonsRight->changeSize(int(m_global_width * 0.35), 0, QSizePolicy::Expanding);
		m_sliderInFullScreen->show();
		m_volumeSliderInFullScreen->show();
		m_titleInFullScreen->show();
		m_durationInFullScreen->show();
		m_progressTimeInFullScreen->show();
		m_playInFullScreen->show();
		m_pauseInFullScreen->show();
		m_stopInFullScreen->show();
		m_nextInFullScreen->show();
		m_prevInFullScreen->show();
		m_disableFullScreen->show();
		m_volumeUpInFullScreen->show();
		m_volumeDownInFullScreen->show();
		m_volumeMuteInFullScreen->show();
        m_globalVideoWidget->showCursorOnFullScreen();
        m_videoWidget->showCursorOnFullScreen();
	}
    else if (m_globalVideoWidget->isFullScreen() && !m_videoControlTimer->isActive() && !m_titleInFullScreen->isHidden())
        m_videoControlTimer->start(TIME_TO_HIDE_VIDEO_CTRL_MS);
}

void MediaPlayer::hideVideoControlPanel()
{
    hideControlPanelInNormalMode(true);
}

void MediaPlayer::hideControlPanelInNormalMode(bool forcedHide)
{
    if (m_globalVideoWidget->isFullScreen() && !forcedHide)
		return;

    m_videoControlTimer->stop();
	m_videoTitleLayout->setMargin(0);
	m_videoControlGridLayout->setMargin(0);
	m_spaceInFullScreenButtonsLeft->changeSize(0, 0);
	m_spaceInFullScreenButtonsRight->changeSize(0, 0);
	m_sliderInFullScreen->hide();
	m_titleInFullScreen->hide();
	m_durationInFullScreen->hide();
	m_progressTimeInFullScreen->hide();
	m_playInFullScreen->hide();
	m_pauseInFullScreen->hide();
	m_stopInFullScreen->hide();
	m_nextInFullScreen->hide();
	m_prevInFullScreen->hide();
	m_disableFullScreen->hide();
	m_volumeUpInFullScreen->hide();
	m_volumeDownInFullScreen->hide();
	m_volumeMuteInFullScreen->hide();
	m_volumeSliderInFullScreen->hide();
}

void MediaPlayer::clearLayout(QLayout *layout)
{
	QLayoutItem *item;
	while((item = layout->takeAt(0)))
	{
		if (item->layout())
		{
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget())
			delete item->widget();

		delete item;
	}
}

void MediaPlayer::showHidePlaylist()
{
	ui->playlistLabel->setHidden(!ui->playlistLabel->isHidden());
    ui->playlistTabWidget->setHidden(!ui->playlistTabWidget->isHidden());
	ui->indexAudioLabel->setHidden(!ui->indexAudioLabel->isHidden());
	ui->indexVideoLabel->setHidden(!ui->indexVideoLabel->isHidden());
	ui->indexInfoLabel->setHidden(!ui->indexInfoLabel->isHidden());
	ui->allItemsLabel->setHidden(!ui->allItemsLabel->isHidden());
	ui->addFileButton->setHidden(!ui->addFileButton->isHidden());
	ui->addFolderButton->setHidden(!ui->addFolderButton->isHidden());
	ui->clearButton->setHidden(!ui->clearButton->isHidden());
    ui->deleteItemButton->setHidden(!ui->deleteItemButton->isHidden());
	ui->searchButton->setHidden(!ui->searchButton->isHidden());
	ui->repeatButton->setHidden(!ui->repeatButton->isHidden());
	ui->shuffleButton->setHidden(!ui->shuffleButton->isHidden());
	ui->currentItemLabel->setHidden(!ui->currentItemLabel->isHidden());
	ui->loadingLabel->setHidden(!ui->loadingLabel->isHidden());
	ui->underPlaylistLabel->setHidden(!ui->underPlaylistLabel->isHidden());
	ui->totalTimeLabel->setHidden(!ui->totalTimeLabel->isHidden());

    if (ui->playlistTabWidget->isHidden())
	{
        m_menuBar->setFixedWidth(13);
		ui->showHidePlaylistButton->setIcon(QIcon(":/buttons/img/buttons/show-arrow-48.ico"));
		ui->showHidePlaylistButton->setToolTip("Show playlist");
	}
	else
	{
        m_menuBar->setFixedWidth(ui->playlistTabWidget->geometry().width());
		ui->showHidePlaylistButton->setIcon(QIcon(":/buttons/img/buttons/hide-arrow-48.ico"));
		ui->showHidePlaylistButton->setToolTip("Hide playlist");
	}
}

void MediaPlayer::onContentTypeChange(bool isAudio)
{
	if (isAudio)
	{
		m_videoWidget->hide();
		m_musicLabel->show();
	}
	else
	{
		m_musicLabel->hide();
		m_videoWidget->show();
	}
}

void MediaPlayer::stopAnimation(bool isPaused)
{
    m_isPaused = isPaused;

	if (isPaused)
    {
        ui->pauseButton->setChecked(true);
        m_pauseInFullScreen->setChecked(true);
        ui->playButton->setChecked(false);
        m_playInFullScreen->setChecked(false);
        ui->pauseButton->setStyleSheet(m_style->buttonCheckedTheme);
        m_pauseInFullScreen->setStyleSheet(m_style->buttonCheckedTheme);
        ui->playButton->setStyleSheet(m_style->backcolor);
        m_playInFullScreen->setStyleSheet(m_style->backcolor);

		m_movieMusic->stop();
    }
	else
    {
        ui->playButton->setChecked(true);
        m_playInFullScreen->setChecked(true);
        ui->pauseButton->setChecked(false);
        m_pauseInFullScreen->setChecked(false);
        ui->playButton->setStyleSheet(m_style->buttonCheckedTheme);
        m_playInFullScreen->setStyleSheet(m_style->buttonCheckedTheme);
        ui->pauseButton->setStyleSheet(m_style->backcolor);
        m_pauseInFullScreen->setStyleSheet(m_style->backcolor);

		m_movieMusic->start();
    }
}

void MediaPlayer::postInit()
{
    m_menuBar->setFixedWidth(ui->playlistTabWidget->geometry().width());
}

void MediaPlayer::closeEvent(QCloseEvent *event)
{
    emit closeMainWindow();
    event->accept();
}

void MediaPlayer::toggleVideoWidgetFullscreen()
{
    if (m_globalVideoWidget->windowState() == Qt::WindowFullScreen)
    {
        m_globalVideoWidget->setParent(this);
        m_globalVideoWidget->setWindowState(Qt::WindowNoState);
        ui->videoLayout->addWidget(m_globalVideoWidget);
    }
    else
    {
        ui->videoLayout->removeWidget(m_globalVideoWidget);
        m_globalVideoWidget->setParent(this, Qt::Tool | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        m_globalVideoWidget->showFullScreen();
    }

    emit videoFullscreenToggled();
}

void MediaPlayer::removeItemFromPlaylist()
{
    if (!m_playlist.getCurrentPlaylistWidget()->item(m_playlist.getCurrentPlaylistWidget()->currentRow(), 1))
        return;

    QList<QTableWidgetItem*> selectedRows = m_playlist.getCurrentPlaylistWidget()->selectedItems();

    foreach(QTableWidgetItem *obj, selectedRows)
    {
        if (obj->column() != 1)
            continue;

        if (m_playerControls->getCurrentMediaItemValue() == obj->text())
        {
            if (!m_shuffleMode)
                m_playerControls->nextForced();

            m_playlist.deletePlaylistItem(obj);
        }
        else
            m_playlist.deletePlaylistItem(obj);

    }

    m_isUpdateOnRemove = true;
    updatePlaylist();
}

void MediaPlayer::playlistTabChanged(int id)
{
    if (id < 0)
        return;

    // always keep one tab opened
    if (id == 0 && ui->playlistTabWidget->count() == 1)
        ui->playlistTabWidget->setTabsClosable(false);

#if DEBUG
    qDebug() << "Switch to ID" << id << ":" << ui->playlistTabWidget->currentWidget()->objectName();
#endif

    m_playlist.setActivePlaylist(ui->playlistTabWidget->currentWidget()->objectName());
    m_playlist.makeShuffle(m_shuffleMode);
}

void MediaPlayer::closePlaylistTab(int id)
{
    if (id < 0)
        return;

#if DEBUG
    qDebug() << "Close playlist ID" << id + 1 << "of" << ui->playlistTabWidget->count() << ":" << ui->playlistTabWidget->widget(id)->objectName();
#endif

    m_playlist.removePlaylist(ui->playlistTabWidget->widget(id)->objectName());
    QWidget *tab = ui->playlistTabWidget->widget(id);
    ui->playlistTabWidget->removeTab(id);
    delete tab;
    tab = NULL;

    if (ui->playlistTabWidget->count() == 1)
    {
        ui->playlistTabWidget->setTabsClosable(false);
        return;
    }
}
void MediaPlayer::renamePlaylistTab(int id)
{
    m_renameDialog->setPlaceholer(ui->playlistTabWidget->tabText(id), id);
    m_renameDialog->show();
}

void MediaPlayer::playlistTabRenamed(QString text, int id)
{
    ui->playlistTabWidget->setTabText(id, text);
}
