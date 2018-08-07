/*
MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "mediaplayer.h"
#include "ui_mediaplayer.h"

#define THEME_CONFIG_FILE "/config/theme.sst"
#define SLIDER_STEP 10

MediaPlayer::MediaPlayer(QRect screen_size, QWidget *parent) : QMainWindow(parent),
    m_global_height(screen_size.height()), m_global_width(screen_size.width()),
    ui(new Ui::MediaPlayer), m_videoWidget(0), m_theme_config_path(PRO_FILE_PWD)
{
    ui->setupUi(this);

    m_playerControls = new PlayerControls();
    m_mediaFile = new MediafileController(this);
    m_search = new SearchDialog(this);
    m_aboutPlayer = new AboutPigmend(this);
    m_sliderInFullScreen = new QSlider(Qt::Horizontal);
    m_titleInFullScreen = new QLabel;
    m_progressTimeInFullScreen = new QLabel;
    m_durationInFullScreen = new QLabel;

    m_progressTimeInFullScreen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    m_durationInFullScreen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    // shortcuts
    m_playSC = new QShortcut(Qt::Key_MediaPlay, ui->playButton, SLOT(click()));
    m_nextSC = new QShortcut(Qt::Key_MediaNext, ui->nextButton, SLOT(click()));
    m_prevSC = new QShortcut(Qt::Key_MediaPrevious, ui->prevButton, SLOT(click()));
    m_stopSC = new QShortcut(Qt::Key_MediaStop, ui->stopButton, SLOT(click()));
    m_theme_config_path.append(THEME_CONFIG_FILE);

    // initialize menu and load stylr
    initMenu();
    adjustVideoWidget();
    loadTheme();

    //
    m_isPlaylistLoaded = false;
    m_shuffleMode = false;
    ui->volumeSlider->setRange(0, 100);

    m_sliderInFullScreen->setObjectName("sliderInFullScreen");
	m_globalVideoWidget->setObjectName("globalVideoWidget");
    m_videoWidget->setObjectName("videoWidget");
    ui->progressSlider->installEventFilter(this);
    m_sliderInFullScreen->installEventFilter(this);
    m_globalVideoWidget->installEventFilter(this);
    m_videoWidget->installEventFilter(this);

    // set QWidget for video output
    connect(this, SIGNAL(videoWidgetDefined(VideoWidget*)), m_playerControls, SLOT(setVideoWidget(VideoWidget*)));
    emit videoWidgetDefined(m_videoWidget);

    // index animation and notification
    QString pathLoad(PRO_FILE_PWD);
    pathLoad.append("/img/custom/loader.gif");
    m_movieLoading = new QMovie(pathLoad);
    QString pathDone(PRO_FILE_PWD);
    pathDone.append("/img/custom/okload.gif");
    m_movieDone = new QMovie(pathDone);
    ui->loadingLabel->setMovie(m_movieLoading);
    m_movieLoading->start();
    ui->indexInfoLabel->setText("Indexing...");

    // menu actions
    connect(m_addFileAction, SIGNAL(triggered(bool)), m_mediaFile, SLOT(openFile()));
    connect(m_addFolderAction, SIGNAL(triggered(bool)), m_mediaFile, SLOT(openFolder()));
    connect(m_orangeAction, SIGNAL(triggered(bool)), this, SLOT(setOrangeMendTheme()));
    connect(m_blueAction, SIGNAL(triggered(bool)), this, SLOT(setBlueMendTheme()));
    connect(m_greyAction, SIGNAL(triggered(bool)), this, SLOT(setGreyMendTheme()));
    connect(m_darkGreyAction, SIGNAL(triggered(bool)), this, SLOT(setDarkGreyMendTheme()));
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

    // ui operations
    connect(ui->addFileButton, SIGNAL(clicked(bool)), m_mediaFile, SLOT(openFile()));
    connect(ui->addFolderButton, SIGNAL(clicked(bool)), m_mediaFile, SLOT(openFolder()));
    connect(ui->playButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(play()));
    connect(ui->pauseButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(pause()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(stop()));
    connect(ui->nextButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(nextForced()));
    connect(ui->prevButton, SIGNAL(clicked(bool)), m_playerControls, SLOT(prev()));
    connect(ui->fullScreenButton, SIGNAL(clicked(bool)), m_globalVideoWidget, SLOT(manageFullScreen()));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearPlaylist()));
    connect(ui->playlistWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), m_playerControls, SLOT(setMediaFile(QListWidgetItem*)));
    connect(ui->progressSlider, SIGNAL(sliderMoved(int)), m_playerControls, SLOT(seek(int)));
    connect(this, SIGNAL(progressSliderValueChanged(int)), m_playerControls, SLOT(seek(int)));
    connect(m_sliderInFullScreen, SIGNAL(sliderMoved(int)), m_playerControls, SLOT(seek(int)));
    connect(this, SIGNAL(progressSliderValueChanged(int)), m_playerControls, SLOT(seek(int)));
    connect(ui->fast2Button, SIGNAL(clicked(bool)), m_playerControls, SLOT(fastForward()));
    connect(ui->fast4Button, SIGNAL(clicked(bool)), m_playerControls, SLOT(fastForward()));
    connect(ui->repeatBox, SIGNAL(toggled(bool)), m_playerControls, SLOT(setRepeatMode(bool)));
    connect(ui->shuffleBox, SIGNAL(toggled(bool)), m_playerControls, SLOT(setShuffleMode(bool)));
    connect(ui->shuffleBox, SIGNAL(toggled(bool)), this, SLOT(checkShuffleMode(bool)));
    connect(ui->searchButton, SIGNAL(clicked(bool)), m_search, SLOT(show()));
    connect(ui->searchButton, SIGNAL(clicked(bool)), m_search, SLOT(setStartTips()));
    connect(ui->volumeUpButton, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonUpChanged()));
    connect(ui->volumeDownButton, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonDownChanged()));
    connect(ui->muteButton, SIGNAL(clicked(bool)), this, SLOT(onVolumeMute()));
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeSliderValueChanged()));
    // full screen
    connect(m_playInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(play()));
    connect(m_pauseInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(pause()));
    connect(m_stopInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(stop()));
    connect(m_nextInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(nextForced()));
    connect(m_prevInFullScreen, SIGNAL(clicked(bool)), m_playerControls, SLOT(prev()));
    connect(m_disableFullScreen, SIGNAL(clicked(bool)), m_globalVideoWidget, SLOT(manageFullScreen()));
    connect(m_volumeUpInFullScreen, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonUpChanged()));
    connect(m_volumeDownInFullScreen, SIGNAL(clicked(bool)), this, SLOT(onVolumeButtonDownChanged()));
    connect(m_volumeMuteInFullScreen, SIGNAL(clicked(bool)), this, SLOT(onVolumeMute()));
    connect(m_globalVideoWidget, SIGNAL(fullScreenChanged(bool)), this, SLOT(hideControlPanelInNormalMode(bool)));

    // internal operations
    connect(m_playerControls, SIGNAL(currentMediaItem(QString)), this, SLOT(focusItem(QString)));
    connect(m_playerControls, SIGNAL(titleChanged( QStringList*)), this, SLOT(updateTitle( QStringList*)));
    connect(m_playerControls, SIGNAL(durationChanged(int)), this, SLOT(updateDuration(int)));
    connect(m_mediaFile, SIGNAL(filesChosen()), this, SLOT(updatePlaylist()));
    connect(m_playerControls, SIGNAL(timeProgressChanged(int)), this, SLOT(updateTimeProgress(int)));
    connect(m_search, SIGNAL(matchesFound(QListWidgetItem*)), m_playerControls, SLOT(setMediaFile(QListWidgetItem*)));
    connect(m_mediaFile, SIGNAL(filesFound(int,int, bool)), this, SLOT(updateIndexedData(int,int, bool)));
    connect(this, SIGNAL(changeVolume(int)), m_playerControls, SIGNAL(setVolumeToPlayer(int)));
    connect(m_playerControls, SIGNAL(changeVolumeValue(float)), this, SLOT(updateVolumeValue(float)));
    connect(m_playerControls, SIGNAL(mousePositionChanged(QPoint*)), this, SLOT(updateCursorPosition(QPoint*)));
}

MediaPlayer::~MediaPlayer()
{
    delete m_videoButtonsLayout;
    delete m_durationInFullScreen;
    delete m_progressTimeInFullScreen;
    delete m_globalVideoWidget;
    delete m_videoTitleLayout;
    delete m_videoControlGridLayout;
    delete m_videoScreenLayout;
    delete m_videoGridLayout;
    delete m_sliderInFullScreen;
    delete m_titleInFullScreen;
    delete ui;
    delete m_playerControls;
    delete m_videoWidget;
    delete m_mediaFile;
    delete m_search;
    delete m_aboutPlayer;
    delete m_movieLoading;
    delete m_movieDone;
    delete m_menuBar;
    delete m_playSC;
    delete m_nextSC;
    delete m_prevSC;
    delete m_stopSC;
}

bool MediaPlayer::eventFilter(QObject* watched, QEvent* event)
{
    switch (event->type())
    {
        case QEvent::KeyPress:
        {
            QKeyEvent *keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Right)
            {
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
            }
            else if (keyEvent->key() == Qt::Key_Left)
            {
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
            }

            break;
        }
        case QEvent::MouseButtonPress:
        {
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            if (mouseEvent->button() == Qt::LeftButton && watched->objectName() != "globalVideoWidget" &&
                watched->objectName() != "videoWidget")
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

    // view
    m_viewmenu = m_menuBar->addMenu("View");
    m_thememenu = m_viewmenu->addMenu(QIcon(":/buttons/img/buttons/paint-brush-16.ico"), "Theme");
    m_orangeAction = m_thememenu->addAction(QIcon(":/custom/img/custom/orangemend.ico"), "Orange Mend");
    m_blueAction = m_thememenu->addAction(QIcon(":/custom/img/custom/bluemend.ico"), "Blue Mend");
    m_greyAction = m_thememenu->addAction(QIcon(":/custom/img/custom/greymend.ico"), "Grey Mend");
    m_darkGreyAction = m_thememenu->addAction(QIcon(":/custom/img/custom/darkgreymend.ico"), "Dark Grey Mend");
    m_fullScreenAction = m_viewmenu->addAction(QIcon(":/buttons/img/buttons/fullscreen-enter-16.ico"), "Full Screen");
    m_fullScreenAction->setShortcut(QKeySequence(Qt::Key_F5));
    m_viewmenu->addSeparator();
    // window size
    m_windowMenu = m_viewmenu->addMenu(QIcon(":/buttons/img/buttons/window-5-16.ico"), "Window size");
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
    m_spaceInFullScreenButtons = new QSpacerItem(0, 0);

    // buttons size and style policy
    m_playInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_pauseInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_stopInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_nextInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_prevInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_disableFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_volumeUpInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_volumeDownInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_volumeMuteInFullScreen->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

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
    m_volumeUpInFullScreen->setIcon(QIcon(":/buttons/img/buttons/volume-up-4-16.ico"));
    m_volumeDownInFullScreen->setIcon(QIcon(":/buttons/img/buttons/volume-down-5-16.ico"));
    m_volumeMuteInFullScreen->setIcon(QIcon(":/buttons/img/buttons/mute-2-16.ico"));

    ui->videoLayout->addWidget(m_globalVideoWidget);

    m_videoGridLayout->addLayout(m_videoTitleLayout, 0, 0);
    m_videoGridLayout->addLayout(m_videoScreenLayout, 1, 0);
    m_videoGridLayout->addLayout(m_videoControlGridLayout, 2, 0);

    m_videoScreenLayout->addWidget(m_videoWidget);

    m_videoControlGridLayout->addLayout(m_videoProgressLayout, 0, 0);
    m_videoControlGridLayout->addLayout(m_videoButtonsLayout, 1, 0);

    m_videoProgressLayout->addWidget(m_progressTimeInFullScreen);
    m_videoProgressLayout->addWidget(m_sliderInFullScreen);
    m_videoProgressLayout->addWidget(m_durationInFullScreen);

    m_videoButtonsLayout->addSpacerItem(m_spaceInFullScreenButtons);
    m_videoButtonsLayout->addWidget(m_prevInFullScreen);
    m_videoButtonsLayout->addWidget(m_stopInFullScreen);
    m_videoButtonsLayout->addWidget(m_playInFullScreen);
    m_videoButtonsLayout->addWidget(m_pauseInFullScreen);
    m_videoButtonsLayout->addWidget(m_nextInFullScreen);
    m_videoButtonsLayout->addSpacerItem(m_spaceInFullScreenButtons);
    //m_videoButtonsLayout->addWidget(m_disableFullScreen);
    m_videoButtonsLayout->addWidget(m_disableFullScreen, 0, Qt::AlignRight);
    //m_videoButtonsLayout->addWidget(m_volumeUpInFullScreen);
    //m_videoButtonsLayout->addWidget(m_volumeDownInFullScreen);
    //m_videoButtonsLayout->addWidget(m_volumeMuteInFullScreen);
    m_videoTitleLayout->addWidget(m_titleInFullScreen);

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
}

void MediaPlayer::updatePlaylist()
{
    ui->playlistWidget->clear();    // delete all playlist widget items

    static size_t row = 0;          // row count

    // insert filenames from QMap as items to playlist widget
    for (auto it = m_playlist.m_plData.begin(); it != m_playlist.m_plData.end(); ++it)
    {
        QString item = it.key();
        ui->playlistWidget->insertItem(row, item);
        ++row;
    }

    ui->allItemsLabel->setFrameStyle(QFrame::StyledPanel);
    ui->allItemsLabel->setText("<font color=\"white\">Amount: </font>" + QString::number(ui->playlistWidget->count()));   // set count of tracks

    // if added new files - shuffle it all
    if (m_shuffleMode)
        m_playerControls->setShuffleMode(true);

    // prepare first media file
    // while loaded playlist first time - prepare first file for playing
    // and don't prepare first file after adding files to existing playlist
    // because then current media file stops playing and sets first file as media file
    if (!m_isPlaylistLoaded)
    {
        QListWidgetItem* item = new QListWidgetItem(m_playlist.m_plData.value(m_playlist.m_plData.firstKey()));
        m_playerControls->setFirstFile(item);
        m_isPlaylistLoaded = true;
    }
}

void MediaPlayer::updateTitle(QStringList* title)
{
    // set metadata: artist, title, genre and release date
    QString title_line, delimiter(" ⸪ ");
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
    for (auto it = m_playlist.m_plData.begin(); it != m_playlist.m_plData.end(); ++it)
    {
#ifdef WIN32
        QString canonical_path = "file:///" + it.value();
#elif unix
        QString canonical_path = "file://" + it.value();
#endif

        if (path == canonical_path)
        {
          ui->playlistWidget->item(row)->setSelected(true);
          ui->playlistWidget->scrollToItem(ui->playlistWidget->item(row));
          ui->currentItemLabel->setText(QString::number(row + 1));              // set number of current track
        }
        ++row;
    }
}

void MediaPlayer::clearPlaylist()
{
    // clear palylist
    if (ui->playlistWidget->count() == 0)
        return;

    ui->playlistWidget->clear();
    if (m_playlist.clearPlaylistData() != 0)
        qCritical() << "Can't clear playlist data" << endl;

    updatePlaylist();
    // set false
    // when new data will be added to empty playlist then enable ability to prepare first file
    m_isPlaylistLoaded = false;
}

void MediaPlayer::checkShuffleMode(bool check)
{
    m_shuffleMode = check;
}

void MediaPlayer::setOrangeMendTheme()
{
    updateTheme("orange mend");
}

void MediaPlayer::setBlueMendTheme()
{
    updateTheme("blue mend");
}

void MediaPlayer::setGreyMendTheme()
{
    updateTheme("grey mend");
}

void MediaPlayer::setDarkGreyMendTheme()
{
    updateTheme("dark grey mend");
}

/* XXX Add enum instead of QString theme */
void MediaPlayer::updateTheme(QString theme)
{
    QString backcolor;
    QString color;
    QString transbackcolor;
    QString menucolor;

    if (theme == "blue mend")
    {
        backcolor = "background-color: rgb(0, 170, 127); color: rgb(0, 170, 127);";
        color = "color: rgb(0, 170, 127)";
        transbackcolor = "background-color: rgb(0, 170, 127, 127); color: rgb(255, 255, 255);";
        menucolor = "selection-background-color: rgb(0, 170, 127); background-color: rgb(0, 170, 127, 125); color: rgb(255, 255, 255);";
    }
    else if (theme == "orange mend")
    {
        backcolor = "background-color: rgb(255, 85, 0); color: rgb(255, 85, 0);";
        color = "color: rgb(255, 85, 0)";
        transbackcolor = "background-color: rgb(255, 85, 0, 127); color: rgb(255, 255, 255);";
        menucolor = "selection-background-color: rgb(255, 85, 0); background-color: rgb(255, 85, 0, 125); color: rgb(255, 255, 255);";
    }
    else if (theme == "grey mend")
    {
        backcolor = "background-color: rgb(105, 105, 105); color: rgb(105, 105, 105);";
        color = "color: rgb(105, 105, 105)";
        transbackcolor = "background-color: rgb(105, 105, 105, 127); color: rgb(255, 255, 255);";
        menucolor = "selection-background-color: rgb(105, 105, 105); background-color: rgb(105, 105, 105, 125); color: rgb(255, 255, 255);";
    }
    else if (theme == "dark grey mend")
    {
        backcolor = "background-color: rgb(47, 79, 79); color: rgb(47, 79, 79);";
        color = "color: rgb(47, 79, 79)";
        transbackcolor = "background-color: rgb(47, 79, 79, 127); color: rgb(255, 255, 255);";
        menucolor = "selection-background-color: rgb(47, 79, 79); background-color: rgb(47, 79, 79, 125); color: rgb(255, 255, 255);";
    }
    else
    {
        qDebug() << "Undefined theme data";
        return;
    }

    rememberTheme(theme);
    m_search->updateTheme(theme);

    ui->addFileButton->setStyleSheet(backcolor);
    ui->addFolderButton->setStyleSheet(backcolor);
    ui->allItemsLabel->setStyleSheet(color);
    ui->clearButton->setStyleSheet(backcolor);
    ui->currentItemLabel->setStyleSheet(color);
    ui->fast2Button->setStyleSheet(backcolor);
    ui->fast4Button->setStyleSheet(backcolor);
    ui->fullScreenButton->setStyleSheet(backcolor);
    ui->nextButton->setStyleSheet(backcolor);
    ui->pauseButton->setStyleSheet(backcolor);
    ui->playButton->setStyleSheet(backcolor);
    ui->playlistWidget->setStyleSheet(transbackcolor);
    ui->prevButton->setStyleSheet(backcolor);
    ui->progressSlider->setStyleSheet(transbackcolor);
    ui->volumeSlider->setStyleSheet(transbackcolor);
    ui->searchButton->setStyleSheet(backcolor);
    ui->stopButton->setStyleSheet(backcolor);
    ui->stopButton->setStyleSheet(backcolor);
    ui->volumeUpButton->setStyleSheet(backcolor);
    ui->volumeDownButton->setStyleSheet(backcolor);
    ui->muteButton->setStyleSheet(backcolor);
    ui->label->setStyleSheet(color);
    ui->titleLabel->setStyleSheet(color);
    ui->indexInfoLabel->setStyleSheet(color);
    m_menuBar->setStyleSheet(menucolor);

    // full screen mode
    m_sliderInFullScreen->setStyleSheet(transbackcolor);
    m_titleInFullScreen->setStyleSheet(color);
    m_durationInFullScreen->setStyleSheet(color);
    m_progressTimeInFullScreen->setStyleSheet(color);
    m_playInFullScreen->setStyleSheet(backcolor);
    m_pauseInFullScreen->setStyleSheet(backcolor);
    m_stopInFullScreen->setStyleSheet(backcolor);
    m_nextInFullScreen->setStyleSheet(backcolor);
    m_prevInFullScreen->setStyleSheet(backcolor);
    m_disableFullScreen->setStyleSheet(backcolor);
    m_volumeUpInFullScreen->setStyleSheet(backcolor);
    m_volumeDownInFullScreen->setStyleSheet(backcolor);
    m_volumeMuteInFullScreen->setStyleSheet(backcolor);
}

void MediaPlayer::rememberTheme(QString &style_id)
{

    QFile fs(m_theme_config_path);

    if (!fs.open(QFile::WriteOnly | QFile::Text))
    {
        qCritical() << "could not open file for write";
        return;
    }

    QTextStream in(&fs);
    in << style_id;

    fs.close();
}

void MediaPlayer::loadTheme()
{
    QFile fs(m_theme_config_path);

    if (!fs.open(QFile::ReadWrite | QFile::Text))
    {
        qCritical() << "could not open file for read";
        return;
    }

    QTextStream out(&fs);
    QString theme_name = out.readAll();

    updateTheme(theme_name);

    fs.close();
}

void MediaPlayer::showInfo()
{
    QDesktopServices::openUrl(QUrl("https://github.com/septimomend/playermend"));
}

void MediaPlayer::updateIndexedData(int audio_count, int video_count, bool status)
{
    if (status)
    {
        ui->indexInfoLabel->setText("PC Media:");
        m_movieLoading->stop();
        ui->loadingLabel->setMovie(m_movieDone);
        m_movieDone->start();
    }

    if (audio_count == 0)
        ui->indexAudioLabel->setText("no audio on this PC");
    if (video_count == 0)
        ui->indexVideoLabel->setText("no video on this PC");
    else
    {
        ui->indexAudioLabel->setText("Audio: " + QString::number(audio_count));
        ui->indexVideoLabel->setText("Video: " + QString::number(video_count));
    }
}

void MediaPlayer::setWindowSize()
{
    QAction *actionSender = qobject_cast<QAction*>(sender()); // retrieve which action was clicked
    QString actionText = actionSender->text();
    QRect currentGeometry = geometry();
    if (actionText == m_smallWindowAction->text())
    {
        showNormal();
        setGeometry(currentGeometry.x(), currentGeometry.y(), 400, 200);
    }
    else if (actionText == m_middleWindowAction->text())
    {
        showNormal();
        setGeometry(currentGeometry.x(), currentGeometry.y(), 900, 400);
    }
    else if (actionText == m_normalWindowAction->text())
    {
        showNormal();
        setGeometry(currentGeometry.x(), currentGeometry.y(), 1100, 600);
    }
    else if (actionText == m_wideWindowAction->text())
    {
        showNormal();
        setGeometry(currentGeometry.x(), currentGeometry.y(), 1300, 500);
    }
    else if (actionText == m_maximizeAction->text())
        showMaximized();
}

int MediaPlayer::volume() const
{
    qreal linearVolume =  QAudio::convertVolume(ui->volumeSlider->value() / qreal(100),
        QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);

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
}

void MediaPlayer::onVolumeButtonDownChanged()
{
    int sliderValue = ui->volumeSlider->value();
    sliderValue -= 10;
    ui->volumeSlider->setValue(sliderValue);
}

void MediaPlayer::onVolumeMute()
{
    ui->volumeSlider->setValue(0);
}

void MediaPlayer::updateVolumeValue(float volume)
{
    ui->volumeSlider->setValue(volume);
}

void MediaPlayer::updateCursorPosition(QPoint *position)
{
    if (m_globalVideoWidget->isFullScreen() && ((position->y() <= m_global_height &&
        position->y() >= (m_global_height - (m_global_height * 0.06))) ||
        (position->y() >= 0 && position->y() <= m_global_height * 0.035)))
    {
        m_spaceInFullScreenButtons->changeSize(m_global_width * 0.4, 0);
        m_sliderInFullScreen->show();
        m_titleInFullScreen->show();
        m_durationInFullScreen->show();
        m_progressTimeInFullScreen->show();
        m_playInFullScreen->show();
        m_pauseInFullScreen->show();
        m_stopInFullScreen->show();
        m_nextInFullScreen->show();
        m_prevInFullScreen->show();
        m_disableFullScreen->show();
        //m_volumeUpInFullScreen->show();
        //m_volumeDownInFullScreen->show();
        //m_volumeMuteInFullScreen->show();
    }
    else
        hideControlPanelInNormalMode(true);
}

void MediaPlayer::hideControlPanelInNormalMode(bool forcedHide)
{
    if (m_globalVideoWidget->isFullScreen() && !forcedHide)
        return;

    m_spaceInFullScreenButtons->changeSize(0, 0);
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
