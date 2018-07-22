/********************************************************************************
** Form generated from reading UI file 'mediaplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIAPLAYER_H
#define UI_MEDIAPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QGridLayout *gridLayout;
    QLabel *titleLabel;
    QLabel *indexInfoLabel;
    QPushButton *prevButton;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *clearButton;
    QListWidget *playlistWidget;
    QLabel *durationLabel;
    QLabel *playlistLabel;
    QPushButton *stopButton;
    QLabel *currentItemLabel;
    QSlider *progressSlider;
    QLabel *indexVideoLabel;
    QFormLayout *formLayout;
    QSlider *volumeSlider;
    QLabel *progressTimeLabel;
    QPushButton *fullScreenButton;
    QVBoxLayout *videoLayout;
    QPushButton *addFileButton;
    QLabel *indexAudioLabel;
    QPushButton *nextButton;
    QPushButton *searchButton;
    QPushButton *addFolderButton;
    QLabel *allItemsLabel;
    QLabel *loadingLabel;
    QCheckBox *shuffleBox;
    QCheckBox *repeatBox;
    QGridLayout *fastForwardLayout;
    QPushButton *fast4Button;
    QPushButton *fast2Button;
    QLabel *label;
    QFormLayout *formLayout_3;
    QPushButton *muteButton;
    QPushButton *volumeDownButton;
    QPushButton *volumeUpButton;
    QHBoxLayout *menuLayout;

    void setupUi(QMainWindow *MediaPlayer)
    {
        if (MediaPlayer->objectName().isEmpty())
            MediaPlayer->setObjectName(QStringLiteral("MediaPlayer"));
        MediaPlayer->resize(821, 397);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(15);
        sizePolicy.setVerticalStretch(50);
        sizePolicy.setHeightForWidth(MediaPlayer->sizePolicy().hasHeightForWidth());
        MediaPlayer->setSizePolicy(sizePolicy);
        MediaPlayer->setStyleSheet(QStringLiteral("background-color: rgb(53, 53, 53);"));
        MediaPlayer->setIconSize(QSize(30, 30));
        MediaPlayer->setDocumentMode(false);
        MediaPlayer->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        MediaPlayer->setUnifiedTitleAndToolBarOnMac(false);
        actionerw = new QAction(MediaPlayer);
        actionerw->setObjectName(QStringLiteral("actionerw"));
        actionrwe = new QAction(MediaPlayer);
        actionrwe->setObjectName(QStringLiteral("actionrwe"));
        centralWidget = new QWidget(MediaPlayer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        titleLabel = new QLabel(centralWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setLayoutDirection(Qt::LeftToRight);
        titleLabel->setStyleSheet(QStringLiteral(""));
        titleLabel->setTextFormat(Qt::AutoText);
        titleLabel->setScaledContents(false);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setWordWrap(false);

        gridLayout->addWidget(titleLabel, 0, 0, 1, 7);

        indexInfoLabel = new QLabel(centralWidget);
        indexInfoLabel->setObjectName(QStringLiteral("indexInfoLabel"));
        indexInfoLabel->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(indexInfoLabel->sizePolicy().hasHeightForWidth());
        indexInfoLabel->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(8);
        indexInfoLabel->setFont(font1);
        indexInfoLabel->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(indexInfoLabel, 6, 8, 1, 1);

        prevButton = new QPushButton(centralWidget);
        prevButton->setObjectName(QStringLiteral("prevButton"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(prevButton->sizePolicy().hasHeightForWidth());
        prevButton->setSizePolicy(sizePolicy3);
        prevButton->setCursor(QCursor(Qt::PointingHandCursor));
        prevButton->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/img/buttons/media-skip-backward-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        prevButton->setIcon(icon);
        prevButton->setFlat(true);

        gridLayout->addWidget(prevButton, 3, 2, 1, 1);

        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        sizePolicy3.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy3);
        playButton->setCursor(QCursor(Qt::PointingHandCursor));
        playButton->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/img/buttons/play-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon1);
        playButton->setFlat(true);

        gridLayout->addWidget(playButton, 3, 3, 1, 1);

        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        sizePolicy3.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy3);
        pauseButton->setCursor(QCursor(Qt::PointingHandCursor));
        pauseButton->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/img/buttons/media-pause-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon2);
        pauseButton->setFlat(true);

        gridLayout->addWidget(pauseButton, 3, 4, 1, 1);

        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(clearButton->sizePolicy().hasHeightForWidth());
        clearButton->setSizePolicy(sizePolicy4);
        clearButton->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/buttons/img/buttons/delete-column-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        clearButton->setIcon(icon3);
        clearButton->setFlat(true);

        gridLayout->addWidget(clearButton, 3, 9, 1, 1);

        playlistWidget = new QListWidget(centralWidget);
        playlistWidget->setObjectName(QStringLiteral("playlistWidget"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(playlistWidget->sizePolicy().hasHeightForWidth());
        playlistWidget->setSizePolicy(sizePolicy5);
        playlistWidget->setMaximumSize(QSize(16777215, 16777215));
        playlistWidget->setFont(font1);
        playlistWidget->setFocusPolicy(Qt::NoFocus);
        playlistWidget->setContextMenuPolicy(Qt::NoContextMenu);
        playlistWidget->setToolTipDuration(2);
        playlistWidget->setStyleSheet(QStringLiteral(""));
        playlistWidget->setFrameShape(QFrame::Box);
        playlistWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        playlistWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        playlistWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        playlistWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        playlistWidget->setMovement(QListView::Static);
        playlistWidget->setResizeMode(QListView::Adjust);
        playlistWidget->setViewMode(QListView::ListMode);
        playlistWidget->setModelColumn(0);
        playlistWidget->setUniformItemSizes(true);
        playlistWidget->setWordWrap(true);
        playlistWidget->setSelectionRectVisible(false);

        gridLayout->addWidget(playlistWidget, 1, 7, 2, 4);

        durationLabel = new QLabel(centralWidget);
        durationLabel->setObjectName(QStringLiteral("durationLabel"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(durationLabel->sizePolicy().hasHeightForWidth());
        durationLabel->setSizePolicy(sizePolicy6);
        durationLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(durationLabel, 2, 6, 1, 1);

        playlistLabel = new QLabel(centralWidget);
        playlistLabel->setObjectName(QStringLiteral("playlistLabel"));
        playlistLabel->setEnabled(false);
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(playlistLabel->sizePolicy().hasHeightForWidth());
        playlistLabel->setSizePolicy(sizePolicy7);
        playlistLabel->setFont(font);
        playlistLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        playlistLabel->setFrameShape(QFrame::NoFrame);
        playlistLabel->setTextFormat(Qt::AutoText);
        playlistLabel->setScaledContents(false);

        gridLayout->addWidget(playlistLabel, 0, 7, 1, 2);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        sizePolicy3.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy3);
        stopButton->setCursor(QCursor(Qt::PointingHandCursor));
        stopButton->setStyleSheet(QStringLiteral(""));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/buttons/img/buttons/stop-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon4);
        stopButton->setFlat(true);

        gridLayout->addWidget(stopButton, 3, 1, 1, 1);

        currentItemLabel = new QLabel(centralWidget);
        currentItemLabel->setObjectName(QStringLiteral("currentItemLabel"));
        currentItemLabel->setEnabled(false);
        QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(currentItemLabel->sizePolicy().hasHeightForWidth());
        currentItemLabel->setSizePolicy(sizePolicy8);
        currentItemLabel->setFont(font);
        currentItemLabel->setStyleSheet(QStringLiteral(""));
        currentItemLabel->setFrameShape(QFrame::NoFrame);
        currentItemLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(currentItemLabel, 0, 9, 1, 1);

        progressSlider = new QSlider(centralWidget);
        progressSlider->setObjectName(QStringLiteral("progressSlider"));
        progressSlider->setFont(font1);
        progressSlider->setCursor(QCursor(Qt::PointingHandCursor));
        progressSlider->setStyleSheet(QStringLiteral(""));
        progressSlider->setOrientation(Qt::Horizontal);
        progressSlider->setTickPosition(QSlider::NoTicks);

        gridLayout->addWidget(progressSlider, 2, 1, 1, 5);

        indexVideoLabel = new QLabel(centralWidget);
        indexVideoLabel->setObjectName(QStringLiteral("indexVideoLabel"));
        indexVideoLabel->setEnabled(false);
        sizePolicy6.setHeightForWidth(indexVideoLabel->sizePolicy().hasHeightForWidth());
        indexVideoLabel->setSizePolicy(sizePolicy6);
        indexVideoLabel->setFont(font1);
        indexVideoLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        indexVideoLabel->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(indexVideoLabel, 6, 10, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));

        gridLayout->addLayout(formLayout, 5, 1, 1, 1);

        volumeSlider = new QSlider(centralWidget);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(volumeSlider, 4, 1, 1, 1);

        progressTimeLabel = new QLabel(centralWidget);
        progressTimeLabel->setObjectName(QStringLiteral("progressTimeLabel"));
        sizePolicy6.setHeightForWidth(progressTimeLabel->sizePolicy().hasHeightForWidth());
        progressTimeLabel->setSizePolicy(sizePolicy6);
        progressTimeLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(progressTimeLabel, 2, 0, 1, 1);

        fullScreenButton = new QPushButton(centralWidget);
        fullScreenButton->setObjectName(QStringLiteral("fullScreenButton"));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(fullScreenButton->sizePolicy().hasHeightForWidth());
        fullScreenButton->setSizePolicy(sizePolicy9);
        fullScreenButton->setCursor(QCursor(Qt::PointingHandCursor));
        fullScreenButton->setMouseTracking(false);
        fullScreenButton->setAcceptDrops(true);
        fullScreenButton->setToolTipDuration(-1);
        fullScreenButton->setAutoFillBackground(false);
        fullScreenButton->setStyleSheet(QStringLiteral(""));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/buttons/img/buttons/fullscreen-enter-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        fullScreenButton->setIcon(icon5);
        fullScreenButton->setFlat(true);

        gridLayout->addWidget(fullScreenButton, 3, 6, 1, 1);

        videoLayout = new QVBoxLayout();
        videoLayout->setSpacing(6);
        videoLayout->setObjectName(QStringLiteral("videoLayout"));
        videoLayout->setSizeConstraint(QLayout::SetNoConstraint);

        gridLayout->addLayout(videoLayout, 1, 0, 1, 7);

        addFileButton = new QPushButton(centralWidget);
        addFileButton->setObjectName(QStringLiteral("addFileButton"));
        sizePolicy4.setHeightForWidth(addFileButton->sizePolicy().hasHeightForWidth());
        addFileButton->setSizePolicy(sizePolicy4);
        addFileButton->setStyleSheet(QStringLiteral(""));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/buttons/img/buttons/add-file-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        addFileButton->setIcon(icon6);
        addFileButton->setFlat(true);

        gridLayout->addWidget(addFileButton, 3, 7, 1, 1);

        indexAudioLabel = new QLabel(centralWidget);
        indexAudioLabel->setObjectName(QStringLiteral("indexAudioLabel"));
        indexAudioLabel->setEnabled(false);
        sizePolicy6.setHeightForWidth(indexAudioLabel->sizePolicy().hasHeightForWidth());
        indexAudioLabel->setSizePolicy(sizePolicy6);
        indexAudioLabel->setFont(font1);
        indexAudioLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(indexAudioLabel, 6, 9, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        sizePolicy3.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy3);
        nextButton->setCursor(QCursor(Qt::PointingHandCursor));
        nextButton->setStyleSheet(QStringLiteral(""));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/buttons/img/buttons/media-skip-forward-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon7);
        nextButton->setFlat(true);

        gridLayout->addWidget(nextButton, 3, 5, 1, 1);

        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        sizePolicy4.setHeightForWidth(searchButton->sizePolicy().hasHeightForWidth());
        searchButton->setSizePolicy(sizePolicy4);
        searchButton->setCursor(QCursor(Qt::PointingHandCursor));
        searchButton->setLayoutDirection(Qt::LeftToRight);
        searchButton->setStyleSheet(QStringLiteral(""));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/buttons/img/buttons/search-3-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        searchButton->setIcon(icon8);
        searchButton->setFlat(true);

        gridLayout->addWidget(searchButton, 3, 10, 1, 1, Qt::AlignRight);

        addFolderButton = new QPushButton(centralWidget);
        addFolderButton->setObjectName(QStringLiteral("addFolderButton"));
        sizePolicy4.setHeightForWidth(addFolderButton->sizePolicy().hasHeightForWidth());
        addFolderButton->setSizePolicy(sizePolicy4);
        addFolderButton->setCursor(QCursor(Qt::PointingHandCursor));
        addFolderButton->setMouseTracking(false);
        addFolderButton->setStyleSheet(QStringLiteral(""));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/buttons/img/buttons/add-folder-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        addFolderButton->setIcon(icon9);
        addFolderButton->setFlat(true);

        gridLayout->addWidget(addFolderButton, 3, 8, 1, 1);

        allItemsLabel = new QLabel(centralWidget);
        allItemsLabel->setObjectName(QStringLiteral("allItemsLabel"));
        allItemsLabel->setEnabled(false);
        sizePolicy8.setHeightForWidth(allItemsLabel->sizePolicy().hasHeightForWidth());
        allItemsLabel->setSizePolicy(sizePolicy8);
        allItemsLabel->setFont(font);
        allItemsLabel->setLayoutDirection(Qt::LeftToRight);
        allItemsLabel->setStyleSheet(QStringLiteral(""));
        allItemsLabel->setFrameShape(QFrame::NoFrame);
        allItemsLabel->setFrameShadow(QFrame::Plain);
        allItemsLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(allItemsLabel, 0, 10, 1, 1, Qt::AlignRight);

        loadingLabel = new QLabel(centralWidget);
        loadingLabel->setObjectName(QStringLiteral("loadingLabel"));
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(loadingLabel->sizePolicy().hasHeightForWidth());
        loadingLabel->setSizePolicy(sizePolicy10);
        loadingLabel->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(loadingLabel, 6, 7, 1, 1);

        shuffleBox = new QCheckBox(centralWidget);
        shuffleBox->setObjectName(QStringLiteral("shuffleBox"));
        sizePolicy4.setHeightForWidth(shuffleBox->sizePolicy().hasHeightForWidth());
        shuffleBox->setSizePolicy(sizePolicy4);
        shuffleBox->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/buttons/img/buttons/shuffle-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        shuffleBox->setIcon(icon10);

        gridLayout->addWidget(shuffleBox, 4, 10, 1, 1);

        repeatBox = new QCheckBox(centralWidget);
        repeatBox->setObjectName(QStringLiteral("repeatBox"));
        sizePolicy4.setHeightForWidth(repeatBox->sizePolicy().hasHeightForWidth());
        repeatBox->setSizePolicy(sizePolicy4);
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
        repeatBox->setPalette(palette);
        repeatBox->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
""));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/buttons/img/buttons/repeat-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        repeatBox->setIcon(icon11);

        gridLayout->addWidget(repeatBox, 4, 7, 1, 3);

        fastForwardLayout = new QGridLayout();
        fastForwardLayout->setSpacing(6);
        fastForwardLayout->setObjectName(QStringLiteral("fastForwardLayout"));
        fast4Button = new QPushButton(centralWidget);
        fast4Button->setObjectName(QStringLiteral("fast4Button"));
        QSizePolicy sizePolicy11(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(fast4Button->sizePolicy().hasHeightForWidth());
        fast4Button->setSizePolicy(sizePolicy11);
        fast4Button->setMaximumSize(QSize(45, 30));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        fast4Button->setFont(font2);
        fast4Button->setStyleSheet(QStringLiteral(""));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/buttons/img/buttons/fast-forward-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        fast4Button->setIcon(icon12);
        fast4Button->setFlat(true);

        fastForwardLayout->addWidget(fast4Button, 0, 1, 1, 1);

        fast2Button = new QPushButton(centralWidget);
        fast2Button->setObjectName(QStringLiteral("fast2Button"));
        sizePolicy11.setHeightForWidth(fast2Button->sizePolicy().hasHeightForWidth());
        fast2Button->setSizePolicy(sizePolicy11);
        fast2Button->setMaximumSize(QSize(45, 30));
        fast2Button->setStyleSheet(QStringLiteral(""));
        fast2Button->setIcon(icon12);
        fast2Button->setFlat(true);

        fastForwardLayout->addWidget(fast2Button, 0, 0, 1, 1);


        gridLayout->addLayout(fastForwardLayout, 4, 5, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy12(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy12);
        QFont font3;
        font3.setPointSize(8);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        label->setFont(font3);
        label->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(label, 6, 0, 1, 6);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        muteButton = new QPushButton(centralWidget);
        muteButton->setObjectName(QStringLiteral("muteButton"));
        sizePolicy11.setHeightForWidth(muteButton->sizePolicy().hasHeightForWidth());
        muteButton->setSizePolicy(sizePolicy11);
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/buttons/img/buttons/mute-2-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        muteButton->setIcon(icon13);
        muteButton->setFlat(true);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, muteButton);

        volumeDownButton = new QPushButton(centralWidget);
        volumeDownButton->setObjectName(QStringLiteral("volumeDownButton"));
        sizePolicy11.setHeightForWidth(volumeDownButton->sizePolicy().hasHeightForWidth());
        volumeDownButton->setSizePolicy(sizePolicy11);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/buttons/img/buttons/volume-down-5-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        volumeDownButton->setIcon(icon14);
        volumeDownButton->setFlat(true);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, volumeDownButton);


        gridLayout->addLayout(formLayout_3, 4, 0, 1, 1);

        volumeUpButton = new QPushButton(centralWidget);
        volumeUpButton->setObjectName(QStringLiteral("volumeUpButton"));
        sizePolicy11.setHeightForWidth(volumeUpButton->sizePolicy().hasHeightForWidth());
        volumeUpButton->setSizePolicy(sizePolicy11);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/buttons/img/buttons/volume-up-4-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        volumeUpButton->setIcon(icon15);
        volumeUpButton->setFlat(true);

        gridLayout->addWidget(volumeUpButton, 4, 2, 1, 1, Qt::AlignLeft);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        menuLayout = new QHBoxLayout();
        menuLayout->setSpacing(6);
        menuLayout->setObjectName(QStringLiteral("menuLayout"));

        gridLayout_2->addLayout(menuLayout, 0, 0, 1, 1);

        MediaPlayer->setCentralWidget(centralWidget);

        retranslateUi(MediaPlayer);

        playlistWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(MediaPlayer);
    } // setupUi

    void retranslateUi(QMainWindow *MediaPlayer)
    {
        MediaPlayer->setWindowTitle(QApplication::translate("MediaPlayer", "Pigmend Player", nullptr));
        actionerw->setText(QApplication::translate("MediaPlayer", "erw", nullptr));
        actionrwe->setText(QApplication::translate("MediaPlayer", "rwe", nullptr));
        titleLabel->setText(QString());
        indexInfoLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        prevButton->setToolTip(QApplication::translate("MediaPlayer", "Previous", nullptr));
#endif // QT_NO_TOOLTIP
        prevButton->setText(QString());
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
        clearButton->setToolTip(QApplication::translate("MediaPlayer", "Clear playlist", nullptr));
#endif // QT_NO_TOOLTIP
        clearButton->setText(QString());
        durationLabel->setText(QApplication::translate("MediaPlayer", "00:00:00", nullptr));
        playlistLabel->setText(QApplication::translate("MediaPlayer", "Playlist:", nullptr));
#ifndef QT_NO_TOOLTIP
        stopButton->setToolTip(QApplication::translate("MediaPlayer", "Stop", nullptr));
#endif // QT_NO_TOOLTIP
        stopButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        currentItemLabel->setToolTip(QApplication::translate("MediaPlayer", "Number of current track", nullptr));
#endif // QT_NO_TOOLTIP
        currentItemLabel->setText(QString());
        indexVideoLabel->setText(QString());
        progressTimeLabel->setText(QApplication::translate("MediaPlayer", "00:00:00", nullptr));
#ifndef QT_NO_TOOLTIP
        fullScreenButton->setToolTip(QApplication::translate("MediaPlayer", "Full Screen", nullptr));
#endif // QT_NO_TOOLTIP
        fullScreenButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        addFileButton->setToolTip(QApplication::translate("MediaPlayer", "Add files", nullptr));
#endif // QT_NO_TOOLTIP
        addFileButton->setText(QString());
        indexAudioLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        nextButton->setToolTip(QApplication::translate("MediaPlayer", "Next", nullptr));
#endif // QT_NO_TOOLTIP
        nextButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        searchButton->setToolTip(QApplication::translate("MediaPlayer", "Search", nullptr));
#endif // QT_NO_TOOLTIP
        searchButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        addFolderButton->setToolTip(QApplication::translate("MediaPlayer", "Add folder", nullptr));
#endif // QT_NO_TOOLTIP
        addFolderButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        allItemsLabel->setToolTip(QApplication::translate("MediaPlayer", "Count of playlist items", nullptr));
#endif // QT_NO_TOOLTIP
        allItemsLabel->setText(QString());
        loadingLabel->setText(QString());
        shuffleBox->setText(QApplication::translate("MediaPlayer", "Shuffle", nullptr));
#ifndef QT_NO_TOOLTIP
        repeatBox->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        repeatBox->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        repeatBox->setText(QApplication::translate("MediaPlayer", "Repeat", nullptr));
#ifndef QT_NO_SHORTCUT
        repeatBox->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        fast4Button->setText(QApplication::translate("MediaPlayer", "4x", nullptr));
        fast2Button->setText(QApplication::translate("MediaPlayer", "2x", nullptr));
        label->setText(QApplication::translate("MediaPlayer", "Pigmend Player by Ivan Chapkailo \302\251 2018", nullptr));
        muteButton->setText(QString());
        volumeDownButton->setText(QString());
        volumeUpButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MediaPlayer: public Ui_MediaPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIAPLAYER_H
