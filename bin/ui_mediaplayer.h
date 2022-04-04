/********************************************************************************
** Form generated from reading UI file 'mediaplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIAPLAYER_H
#define UI_MEDIAPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaPlayer
{
public:
    QAction *actionerw;
    QAction *actionrwe;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *menuLayout;
    QGridLayout *gridLayout;
    QPushButton *addFolderButton;
    QPushButton *addFileButton;
    QPushButton *clearButton;
    QPushButton *searchButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *indexInfoLabel;
    QLabel *durationLabel;
    QLabel *progressTimeLabel;
    QSlider *progressSlider;
    QLabel *titleLabel;
    QLabel *loadingLabel;
    QPushButton *showHidePlaylistButton;
    QLabel *playlistLabel;
    QPushButton *shuffleButton;
    QLabel *indexAudioLabel;
    QGridLayout *videoLayout;
    QLabel *label;
    QHBoxLayout *playlistHorizontalLayout;
    QLabel *underPlaylistLabel;
    QPushButton *repeatButton;
    QLabel *indexVideoLabel;
    QLabel *allItemsLabel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_1;
    QHBoxLayout *controlLayout;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QLabel *delimiterLabel;
    QVBoxLayout *fastRewindControlLayout;
    QPushButton *fast2Button;
    QPushButton *fast4Button;
    QSpacerItem *horizontalSpacer_5;
    QLabel *delimiterLabel3;
    QPushButton *muteButton;
    QLabel *delimiterLabel2;
    QPushButton *volumeDownButton;
    QSlider *volumeSlider;
    QPushButton *volumeUpButton;
    QLabel *delimiterLabel4;
    QPushButton *fullScreenButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *currentItemLabel;
    QLabel *totalTimeLabel;
    QTableWidget *playlistWidget;

    void setupUi(QMainWindow *MediaPlayer)
    {
        if (MediaPlayer->objectName().isEmpty())
            MediaPlayer->setObjectName(QString::fromUtf8("MediaPlayer"));
        MediaPlayer->resize(821, 397);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(15);
        sizePolicy.setVerticalStretch(50);
        sizePolicy.setHeightForWidth(MediaPlayer->sizePolicy().hasHeightForWidth());
        MediaPlayer->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/pigmend.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MediaPlayer->setWindowIcon(icon);
        MediaPlayer->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 53, 53);"));
        MediaPlayer->setIconSize(QSize(30, 30));
        MediaPlayer->setDocumentMode(false);
        MediaPlayer->setTabShape(QTabWidget::Rounded);
        MediaPlayer->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        MediaPlayer->setUnifiedTitleAndToolBarOnMac(false);
        actionerw = new QAction(MediaPlayer);
        actionerw->setObjectName(QString::fromUtf8("actionerw"));
        actionrwe = new QAction(MediaPlayer);
        actionrwe->setObjectName(QString::fromUtf8("actionrwe"));
        centralWidget = new QWidget(MediaPlayer);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        menuLayout = new QHBoxLayout();
        menuLayout->setSpacing(6);
        menuLayout->setObjectName(QString::fromUtf8("menuLayout"));

        gridLayout_2->addLayout(menuLayout, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        addFolderButton = new QPushButton(centralWidget);
        addFolderButton->setObjectName(QString::fromUtf8("addFolderButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addFolderButton->sizePolicy().hasHeightForWidth());
        addFolderButton->setSizePolicy(sizePolicy1);
        addFolderButton->setCursor(QCursor(Qt::PointingHandCursor));
        addFolderButton->setMouseTracking(false);
        addFolderButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/buttons/img/buttons/add-folder-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        addFolderButton->setIcon(icon1);
        addFolderButton->setFlat(true);

        gridLayout->addWidget(addFolderButton, 5, 9, 1, 1);

        addFileButton = new QPushButton(centralWidget);
        addFileButton->setObjectName(QString::fromUtf8("addFileButton"));
        sizePolicy1.setHeightForWidth(addFileButton->sizePolicy().hasHeightForWidth());
        addFileButton->setSizePolicy(sizePolicy1);
        addFileButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/buttons/img/buttons/add-file-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        addFileButton->setIcon(icon2);
        addFileButton->setFlat(true);

        gridLayout->addWidget(addFileButton, 5, 8, 1, 1);

        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        sizePolicy1.setHeightForWidth(clearButton->sizePolicy().hasHeightForWidth());
        clearButton->setSizePolicy(sizePolicy1);
        clearButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/buttons/img/buttons/delete-column-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        clearButton->setIcon(icon3);
        clearButton->setFlat(true);

        gridLayout->addWidget(clearButton, 5, 10, 1, 1);

        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        sizePolicy1.setHeightForWidth(searchButton->sizePolicy().hasHeightForWidth());
        searchButton->setSizePolicy(sizePolicy1);
        searchButton->setCursor(QCursor(Qt::PointingHandCursor));
        searchButton->setLayoutDirection(Qt::LeftToRight);
        searchButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/buttons/img/buttons/search-3-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        searchButton->setIcon(icon4);
        searchButton->setFlat(true);

        gridLayout->addWidget(searchButton, 5, 12, 1, 2, Qt::AlignRight);

        horizontalSpacer_3 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 6, 1, 1, 1);

        indexInfoLabel = new QLabel(centralWidget);
        indexInfoLabel->setObjectName(QString::fromUtf8("indexInfoLabel"));
        indexInfoLabel->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(indexInfoLabel->sizePolicy().hasHeightForWidth());
        indexInfoLabel->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(8);
        indexInfoLabel->setFont(font);
        indexInfoLabel->setStyleSheet(QString::fromUtf8(""));
        indexInfoLabel->setFrameShape(QFrame::NoFrame);
        indexInfoLabel->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(indexInfoLabel, 7, 9, 1, 2);

        durationLabel = new QLabel(centralWidget);
        durationLabel->setObjectName(QString::fromUtf8("durationLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(durationLabel->sizePolicy().hasHeightForWidth());
        durationLabel->setSizePolicy(sizePolicy3);
        durationLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(durationLabel, 4, 6, 1, 2);

        progressTimeLabel = new QLabel(centralWidget);
        progressTimeLabel->setObjectName(QString::fromUtf8("progressTimeLabel"));
        sizePolicy3.setHeightForWidth(progressTimeLabel->sizePolicy().hasHeightForWidth());
        progressTimeLabel->setSizePolicy(sizePolicy3);
        progressTimeLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(progressTimeLabel, 4, 0, 1, 1);

        progressSlider = new QSlider(centralWidget);
        progressSlider->setObjectName(QString::fromUtf8("progressSlider"));
        progressSlider->setFont(font);
        progressSlider->setCursor(QCursor(Qt::PointingHandCursor));
        progressSlider->setStyleSheet(QString::fromUtf8(""));
        progressSlider->setOrientation(Qt::Horizontal);
        progressSlider->setTickPosition(QSlider::NoTicks);

        gridLayout->addWidget(progressSlider, 4, 1, 1, 5);

        titleLabel = new QLabel(centralWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy4);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        titleLabel->setFont(font1);
        titleLabel->setLayoutDirection(Qt::LeftToRight);
        titleLabel->setStyleSheet(QString::fromUtf8(""));
        titleLabel->setTextFormat(Qt::AutoText);
        titleLabel->setScaledContents(false);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setWordWrap(false);

        gridLayout->addWidget(titleLabel, 0, 0, 1, 7);

        loadingLabel = new QLabel(centralWidget);
        loadingLabel->setObjectName(QString::fromUtf8("loadingLabel"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(loadingLabel->sizePolicy().hasHeightForWidth());
        loadingLabel->setSizePolicy(sizePolicy5);
        loadingLabel->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(loadingLabel, 7, 8, 1, 1);

        showHidePlaylistButton = new QPushButton(centralWidget);
        showHidePlaylistButton->setObjectName(QString::fromUtf8("showHidePlaylistButton"));
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(showHidePlaylistButton->sizePolicy().hasHeightForWidth());
        showHidePlaylistButton->setSizePolicy(sizePolicy6);
        showHidePlaylistButton->setMaximumSize(QSize(48, 16777215));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/buttons/img/buttons/hide-arrow-48.ico"), QSize(), QIcon::Normal, QIcon::Off);
        showHidePlaylistButton->setIcon(icon5);
        showHidePlaylistButton->setFlat(true);

        gridLayout->addWidget(showHidePlaylistButton, 0, 7, 1, 1);

        playlistLabel = new QLabel(centralWidget);
        playlistLabel->setObjectName(QString::fromUtf8("playlistLabel"));
        playlistLabel->setEnabled(false);
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(playlistLabel->sizePolicy().hasHeightForWidth());
        playlistLabel->setSizePolicy(sizePolicy7);
        playlistLabel->setFont(font1);
        playlistLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        playlistLabel->setFrameShape(QFrame::NoFrame);
        playlistLabel->setTextFormat(Qt::AutoText);
        playlistLabel->setScaledContents(false);

        gridLayout->addWidget(playlistLabel, 0, 8, 1, 3, Qt::AlignBottom);

        shuffleButton = new QPushButton(centralWidget);
        shuffleButton->setObjectName(QString::fromUtf8("shuffleButton"));
        sizePolicy1.setHeightForWidth(shuffleButton->sizePolicy().hasHeightForWidth());
        shuffleButton->setSizePolicy(sizePolicy1);
        shuffleButton->setMaximumSize(QSize(20, 20));
        shuffleButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/buttons/img/buttons/shuffle-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        shuffleButton->setIcon(icon6);
        shuffleButton->setCheckable(true);
        shuffleButton->setFlat(true);

        gridLayout->addWidget(shuffleButton, 1, 9, 1, 1, Qt::AlignLeft);

        indexAudioLabel = new QLabel(centralWidget);
        indexAudioLabel->setObjectName(QString::fromUtf8("indexAudioLabel"));
        indexAudioLabel->setEnabled(false);
        sizePolicy3.setHeightForWidth(indexAudioLabel->sizePolicy().hasHeightForWidth());
        indexAudioLabel->setSizePolicy(sizePolicy3);
        indexAudioLabel->setFont(font);
        indexAudioLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        indexAudioLabel->setFrameShape(QFrame::Box);
        indexAudioLabel->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(indexAudioLabel, 7, 11, 1, 1, Qt::AlignRight);

        videoLayout = new QGridLayout();
        videoLayout->setSpacing(6);
        videoLayout->setObjectName(QString::fromUtf8("videoLayout"));
        videoLayout->setHorizontalSpacing(6);

        gridLayout->addLayout(videoLayout, 1, 0, 3, 8);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy8);
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 7, 0, 1, 6);

        playlistHorizontalLayout = new QHBoxLayout();
        playlistHorizontalLayout->setSpacing(0);
        playlistHorizontalLayout->setObjectName(QString::fromUtf8("playlistHorizontalLayout"));
        underPlaylistLabel = new QLabel(centralWidget);
        underPlaylistLabel->setObjectName(QString::fromUtf8("underPlaylistLabel"));
        underPlaylistLabel->setMaximumSize(QSize(16777215, 20));
        QFont font3;
        font3.setPointSize(12);
        underPlaylistLabel->setFont(font3);
        underPlaylistLabel->setFrameShadow(QFrame::Sunken);
        underPlaylistLabel->setTextFormat(Qt::AutoText);

        playlistHorizontalLayout->addWidget(underPlaylistLabel);

        repeatButton = new QPushButton(centralWidget);
        repeatButton->setObjectName(QString::fromUtf8("repeatButton"));
        sizePolicy1.setHeightForWidth(repeatButton->sizePolicy().hasHeightForWidth());
        repeatButton->setSizePolicy(sizePolicy1);
        repeatButton->setMaximumSize(QSize(20, 20));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(53, 53, 53, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        repeatButton->setPalette(palette);
        repeatButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/buttons/img/buttons/repeat-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        repeatButton->setIcon(icon7);
        repeatButton->setCheckable(true);
        repeatButton->setFlat(true);

        playlistHorizontalLayout->addWidget(repeatButton);


        gridLayout->addLayout(playlistHorizontalLayout, 1, 8, 1, 1);

        indexVideoLabel = new QLabel(centralWidget);
        indexVideoLabel->setObjectName(QString::fromUtf8("indexVideoLabel"));
        indexVideoLabel->setEnabled(false);
        sizePolicy3.setHeightForWidth(indexVideoLabel->sizePolicy().hasHeightForWidth());
        indexVideoLabel->setSizePolicy(sizePolicy3);
        indexVideoLabel->setFont(font);
        indexVideoLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        indexVideoLabel->setFrameShape(QFrame::Box);
        indexVideoLabel->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(indexVideoLabel, 7, 12, 1, 2, Qt::AlignRight);

        allItemsLabel = new QLabel(centralWidget);
        allItemsLabel->setObjectName(QString::fromUtf8("allItemsLabel"));
        allItemsLabel->setEnabled(false);
        QSizePolicy sizePolicy9(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(allItemsLabel->sizePolicy().hasHeightForWidth());
        allItemsLabel->setSizePolicy(sizePolicy9);
        allItemsLabel->setFont(font1);
        allItemsLabel->setLayoutDirection(Qt::LeftToRight);
        allItemsLabel->setStyleSheet(QString::fromUtf8(""));
        allItemsLabel->setFrameShape(QFrame::NoFrame);
        allItemsLabel->setFrameShadow(QFrame::Plain);
        allItemsLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(allItemsLabel, 0, 12, 1, 2, Qt::AlignRight|Qt::AlignBottom);

        horizontalSpacer_4 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 6, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 6, 4, 1, 1);

        horizontalSpacer_1 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_1, 6, 5, 1, 1);

        controlLayout = new QHBoxLayout();
        controlLayout->setSpacing(6);
        controlLayout->setObjectName(QString::fromUtf8("controlLayout"));
        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        QSizePolicy sizePolicy10(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy10);
        playButton->setMinimumSize(QSize(40, 0));
        playButton->setCursor(QCursor(Qt::PointingHandCursor));
        playButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/buttons/img/buttons/play-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon8);
        playButton->setFlat(false);

        controlLayout->addWidget(playButton);

        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        sizePolicy10.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy10);
        pauseButton->setMinimumSize(QSize(40, 0));
        pauseButton->setCursor(QCursor(Qt::PointingHandCursor));
        pauseButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/buttons/img/buttons/media-pause-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon9);
        pauseButton->setFlat(true);

        controlLayout->addWidget(pauseButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        sizePolicy10.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy10);
        stopButton->setMinimumSize(QSize(40, 0));
        stopButton->setCursor(QCursor(Qt::PointingHandCursor));
        stopButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/buttons/img/buttons/stop-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon10);
        stopButton->setFlat(true);

        controlLayout->addWidget(stopButton);

        prevButton = new QPushButton(centralWidget);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        sizePolicy10.setHeightForWidth(prevButton->sizePolicy().hasHeightForWidth());
        prevButton->setSizePolicy(sizePolicy10);
        prevButton->setMinimumSize(QSize(40, 0));
        prevButton->setCursor(QCursor(Qt::PointingHandCursor));
        prevButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/buttons/img/buttons/media-skip-backward-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        prevButton->setIcon(icon11);
        prevButton->setFlat(true);

        controlLayout->addWidget(prevButton);

        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        sizePolicy10.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy10);
        nextButton->setMinimumSize(QSize(40, 0));
        nextButton->setCursor(QCursor(Qt::PointingHandCursor));
        nextButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/buttons/img/buttons/media-skip-forward-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon12);
        nextButton->setFlat(true);

        controlLayout->addWidget(nextButton);

        delimiterLabel = new QLabel(centralWidget);
        delimiterLabel->setObjectName(QString::fromUtf8("delimiterLabel"));
        delimiterLabel->setFrameShape(QFrame::VLine);
        delimiterLabel->setFrameShadow(QFrame::Sunken);

        controlLayout->addWidget(delimiterLabel);

        fastRewindControlLayout = new QVBoxLayout();
        fastRewindControlLayout->setSpacing(6);
        fastRewindControlLayout->setObjectName(QString::fromUtf8("fastRewindControlLayout"));
        fast2Button = new QPushButton(centralWidget);
        fast2Button->setObjectName(QString::fromUtf8("fast2Button"));
        sizePolicy1.setHeightForWidth(fast2Button->sizePolicy().hasHeightForWidth());
        fast2Button->setSizePolicy(sizePolicy1);
        fast2Button->setMaximumSize(QSize(30, 15));
        QFont font4;
        font4.setPointSize(9);
        fast2Button->setFont(font4);
        fast2Button->setStyleSheet(QString::fromUtf8(""));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/buttons/img/buttons/arrow-playback-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        fast2Button->setIcon(icon13);
        fast2Button->setFlat(true);

        fastRewindControlLayout->addWidget(fast2Button);

        fast4Button = new QPushButton(centralWidget);
        fast4Button->setObjectName(QString::fromUtf8("fast4Button"));
        sizePolicy1.setHeightForWidth(fast4Button->sizePolicy().hasHeightForWidth());
        fast4Button->setSizePolicy(sizePolicy1);
        fast4Button->setMaximumSize(QSize(30, 15));
        fast4Button->setFont(font4);
        fast4Button->setStyleSheet(QString::fromUtf8(""));
        fast4Button->setIcon(icon13);
        fast4Button->setFlat(true);

        fastRewindControlLayout->addWidget(fast4Button);


        controlLayout->addLayout(fastRewindControlLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        controlLayout->addItem(horizontalSpacer_5);

        delimiterLabel3 = new QLabel(centralWidget);
        delimiterLabel3->setObjectName(QString::fromUtf8("delimiterLabel3"));
        delimiterLabel3->setFrameShape(QFrame::VLine);
        delimiterLabel3->setFrameShadow(QFrame::Sunken);

        controlLayout->addWidget(delimiterLabel3);

        muteButton = new QPushButton(centralWidget);
        muteButton->setObjectName(QString::fromUtf8("muteButton"));
        sizePolicy1.setHeightForWidth(muteButton->sizePolicy().hasHeightForWidth());
        muteButton->setSizePolicy(sizePolicy1);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/buttons/img/buttons/mute-2-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        muteButton->setIcon(icon14);
        muteButton->setCheckable(true);
        muteButton->setFlat(true);

        controlLayout->addWidget(muteButton);

        delimiterLabel2 = new QLabel(centralWidget);
        delimiterLabel2->setObjectName(QString::fromUtf8("delimiterLabel2"));
        delimiterLabel2->setFrameShape(QFrame::VLine);
        delimiterLabel2->setFrameShadow(QFrame::Sunken);

        controlLayout->addWidget(delimiterLabel2);

        volumeDownButton = new QPushButton(centralWidget);
        volumeDownButton->setObjectName(QString::fromUtf8("volumeDownButton"));
        sizePolicy1.setHeightForWidth(volumeDownButton->sizePolicy().hasHeightForWidth());
        volumeDownButton->setSizePolicy(sizePolicy1);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/buttons/img/buttons/volume-down-5-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        volumeDownButton->setIcon(icon15);
        volumeDownButton->setFlat(true);

        controlLayout->addWidget(volumeDownButton, 0, Qt::AlignRight);

        volumeSlider = new QSlider(centralWidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        sizePolicy1.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy1);
        volumeSlider->setOrientation(Qt::Horizontal);

        controlLayout->addWidget(volumeSlider);

        volumeUpButton = new QPushButton(centralWidget);
        volumeUpButton->setObjectName(QString::fromUtf8("volumeUpButton"));
        sizePolicy1.setHeightForWidth(volumeUpButton->sizePolicy().hasHeightForWidth());
        volumeUpButton->setSizePolicy(sizePolicy1);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/buttons/img/buttons/volume-up-4-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        volumeUpButton->setIcon(icon16);
        volumeUpButton->setFlat(true);

        controlLayout->addWidget(volumeUpButton, 0, Qt::AlignLeft);

        delimiterLabel4 = new QLabel(centralWidget);
        delimiterLabel4->setObjectName(QString::fromUtf8("delimiterLabel4"));
        delimiterLabel4->setFrameShape(QFrame::VLine);
        delimiterLabel4->setFrameShadow(QFrame::Sunken);

        controlLayout->addWidget(delimiterLabel4);

        fullScreenButton = new QPushButton(centralWidget);
        fullScreenButton->setObjectName(QString::fromUtf8("fullScreenButton"));
        sizePolicy1.setHeightForWidth(fullScreenButton->sizePolicy().hasHeightForWidth());
        fullScreenButton->setSizePolicy(sizePolicy1);
        fullScreenButton->setCursor(QCursor(Qt::PointingHandCursor));
        fullScreenButton->setMouseTracking(false);
        fullScreenButton->setAcceptDrops(true);
        fullScreenButton->setToolTipDuration(-1);
        fullScreenButton->setAutoFillBackground(false);
        fullScreenButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/buttons/img/buttons/fullscreen-enter-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        fullScreenButton->setIcon(icon17);
        fullScreenButton->setFlat(true);

        controlLayout->addWidget(fullScreenButton, 0, Qt::AlignRight);


        gridLayout->addLayout(controlLayout, 5, 0, 1, 8);

        horizontalSpacer_2 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 6, 2, 1, 1);

        currentItemLabel = new QLabel(centralWidget);
        currentItemLabel->setObjectName(QString::fromUtf8("currentItemLabel"));
        currentItemLabel->setEnabled(false);
        sizePolicy9.setHeightForWidth(currentItemLabel->sizePolicy().hasHeightForWidth());
        currentItemLabel->setSizePolicy(sizePolicy9);
        currentItemLabel->setFont(font1);
        currentItemLabel->setStyleSheet(QString::fromUtf8(""));
        currentItemLabel->setFrameShape(QFrame::NoFrame);
        currentItemLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentItemLabel, 0, 11, 1, 1, Qt::AlignBottom);

        totalTimeLabel = new QLabel(centralWidget);
        totalTimeLabel->setObjectName(QString::fromUtf8("totalTimeLabel"));
        totalTimeLabel->setFont(font);

        gridLayout->addWidget(totalTimeLabel, 1, 12, 1, 2, Qt::AlignRight|Qt::AlignBottom);

        playlistWidget = new QTableWidget(centralWidget);
        playlistWidget->setObjectName(QString::fromUtf8("playlistWidget"));
        QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(playlistWidget->sizePolicy().hasHeightForWidth());
        playlistWidget->setSizePolicy(sizePolicy11);
        playlistWidget->setMaximumSize(QSize(16777215, 16777215));
        playlistWidget->setFont(font);
        playlistWidget->setFocusPolicy(Qt::NoFocus);
        playlistWidget->setContextMenuPolicy(Qt::NoContextMenu);
        playlistWidget->setToolTipDuration(2);
        playlistWidget->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {border: none;background-color: #282828;width: 10px;margin: 25px 0 0px 0;}\\\n"
"QScrollBar::handle:vertical{border-radius: 4px;border-color: rgba(216, 216, 216, 75%);border-width: 1px; border-style: solid; background-color: rgba(216, 216, 216, 75%); min-height: 25px;}\\\n"
"QScrollBar::add-line:vertical{width: 0px; height: 0px;}\\\n"
"QScrollBar::sub-line:vertical{width: 0px; height: 0px;}\\\n"
"QScrollBar::add-page:vertical{background-color: transparent;}\\\n"
"QScrollBar::sub-page:vertical{background-color: transparent;}\\"));
        playlistWidget->setFrameShape(QFrame::Box);
        playlistWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        playlistWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        playlistWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        playlistWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        playlistWidget->setDragEnabled(false);
        playlistWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        playlistWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        playlistWidget->setShowGrid(false);
        playlistWidget->setGridStyle(Qt::NoPen);
        playlistWidget->horizontalHeader()->setVisible(false);
        playlistWidget->horizontalHeader()->setCascadingSectionResizes(true);
        playlistWidget->horizontalHeader()->setDefaultSectionSize(0);
        playlistWidget->horizontalHeader()->setHighlightSections(true);
        playlistWidget->horizontalHeader()->setMinimumSectionSize(0);
        playlistWidget->horizontalHeader()->setStretchLastSection(false);
        playlistWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(playlistWidget, 2, 8, 3, 6);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        MediaPlayer->setCentralWidget(centralWidget);

        retranslateUi(MediaPlayer);

        QMetaObject::connectSlotsByName(MediaPlayer);
    } // setupUi

    void retranslateUi(QMainWindow *MediaPlayer)
    {
        MediaPlayer->setWindowTitle(QApplication::translate("MediaPlayer", "Pigmend Player", nullptr));
        actionerw->setText(QApplication::translate("MediaPlayer", "erw", nullptr));
        actionrwe->setText(QApplication::translate("MediaPlayer", "rwe", nullptr));
#ifndef QT_NO_TOOLTIP
        addFolderButton->setToolTip(QApplication::translate("MediaPlayer", "Add folder", nullptr));
#endif // QT_NO_TOOLTIP
        addFolderButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        addFileButton->setToolTip(QApplication::translate("MediaPlayer", "Add files", nullptr));
#endif // QT_NO_TOOLTIP
        addFileButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        clearButton->setToolTip(QApplication::translate("MediaPlayer", "Clear playlist", nullptr));
#endif // QT_NO_TOOLTIP
        clearButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        searchButton->setToolTip(QApplication::translate("MediaPlayer", "Search", nullptr));
#endif // QT_NO_TOOLTIP
        searchButton->setText(QString());
        indexInfoLabel->setText(QString());
        durationLabel->setText(QApplication::translate("MediaPlayer", "00:00:00", nullptr));
        progressTimeLabel->setText(QApplication::translate("MediaPlayer", "00:00:00", nullptr));
        titleLabel->setText(QString());
        loadingLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        showHidePlaylistButton->setToolTip(QApplication::translate("MediaPlayer", "Hide playlist", nullptr));
#endif // QT_NO_TOOLTIP
        showHidePlaylistButton->setText(QString());
        playlistLabel->setText(QApplication::translate("MediaPlayer", "Playlist:", nullptr));
#ifndef QT_NO_TOOLTIP
        shuffleButton->setToolTip(QApplication::translate("MediaPlayer", "Shuffle", nullptr));
#endif // QT_NO_TOOLTIP
        shuffleButton->setText(QString());
        indexAudioLabel->setText(QString());
        label->setText(QApplication::translate("MediaPlayer", "Pigmend Player by Ivan Chapkailo \302\251 2018", nullptr));
        underPlaylistLabel->setText(QApplication::translate("MediaPlayer", "|", nullptr));
#ifndef QT_NO_TOOLTIP
        repeatButton->setToolTip(QApplication::translate("MediaPlayer", "Repeat item", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        repeatButton->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        repeatButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        repeatButton->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        indexVideoLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        allItemsLabel->setToolTip(QApplication::translate("MediaPlayer", "Count of playlist items", nullptr));
#endif // QT_NO_TOOLTIP
        allItemsLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        playButton->setToolTip(QApplication::translate("MediaPlayer", "Play", nullptr));
#endif // QT_NO_TOOLTIP
        playButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        playButton->setShortcut(QApplication::translate("MediaPlayer", "Space", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        pauseButton->setToolTip(QApplication::translate("MediaPlayer", "Pause", nullptr));
#endif // QT_NO_TOOLTIP
        pauseButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        pauseButton->setShortcut(QApplication::translate("MediaPlayer", "Space", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        stopButton->setToolTip(QApplication::translate("MediaPlayer", "Stop", nullptr));
#endif // QT_NO_TOOLTIP
        stopButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        prevButton->setToolTip(QApplication::translate("MediaPlayer", "Previous", nullptr));
#endif // QT_NO_TOOLTIP
        prevButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        nextButton->setToolTip(QApplication::translate("MediaPlayer", "Next", nullptr));
#endif // QT_NO_TOOLTIP
        nextButton->setText(QString());
        delimiterLabel->setText(QString());
        fast2Button->setText(QApplication::translate("MediaPlayer", "2x", nullptr));
        fast4Button->setText(QApplication::translate("MediaPlayer", "4x", nullptr));
        delimiterLabel3->setText(QString());
#ifndef QT_NO_TOOLTIP
        muteButton->setToolTip(QApplication::translate("MediaPlayer", "Mute", nullptr));
#endif // QT_NO_TOOLTIP
        muteButton->setText(QString());
        delimiterLabel2->setText(QString());
        volumeDownButton->setText(QString());
        volumeUpButton->setText(QString());
        delimiterLabel4->setText(QString());
#ifndef QT_NO_TOOLTIP
        fullScreenButton->setToolTip(QApplication::translate("MediaPlayer", "Full Screen", nullptr));
#endif // QT_NO_TOOLTIP
        fullScreenButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        currentItemLabel->setToolTip(QApplication::translate("MediaPlayer", "Number of current track", nullptr));
#endif // QT_NO_TOOLTIP
        currentItemLabel->setText(QString());
        totalTimeLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MediaPlayer: public Ui_MediaPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIAPLAYER_H
