#include <QApplication>

#include "preferencesdialog.h"
#include "qsettingsextendedtypes.h"
#include "constants.h"
#include "config-dp/config.h"

#if DEBUG
#include <QDebug>
#endif

using namespace preferences_constants;

PreferencesDialog::PreferencesDialog() :
    m_parentWidget(NULL),
#if DEBUG
    m_preferenceSettings(QApplication::applicationDirPath() + "/../config/settings.ini", QSettings::IniFormat)
#else
    m_preferenceSettings(QApplication::applicationDirPath() + "/config/settings.ini", QSettings::IniFormat)
#endif
{
    initParentWidget();
    initSections();

    connect(&m_preferencesDialog, SIGNAL(saved(bool)), this, SLOT(saveSettings(bool)));
}

PreferencesDialog::~PreferencesDialog()
{
    delete m_parentWidget;
}

void PreferencesDialog::initParentWidget()
{
    m_parentWidget = new QWidget;
    //m_parentWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    if (!m_parentWidget)
    {
#if DEBUG
        qDebug() << "Failed to allocate preferences parent widget" << endl;
#endif
        return;
    }
}

void PreferencesDialog::initSections()
{
    initGeneralSection();
    initShortcutsSection();
    initViewSection();
    initApplicationSection();
    initAudioSection();
    initVideoSection();
}

void PreferencesDialog::initGeneralSection()
{
    m_preferencesDialog.setCategory(SECTION_GENERAL, SECTION_GENERAL, QIcon(SECTION_GENERAL_ICON));
    m_preferencesDialog.setSection(SECTION_GENERAL);

    m_preferencesDialog.appendEntry(new QSettingsEntry(777777, new StateLoader(), "Install plugins (notifications, subtitle downloader etc)"));
}

void PreferencesDialog::initViewSection()
{
    m_preferencesDialog.setCategory(SECTION_VIEW, SECTION_VIEW, QIcon(SECTION_VIEW_ICON));
    m_preferencesDialog.setSection(SECTION_VIEW);

    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_VIEW"/theme_color"), "Theme color"));
}

void PreferencesDialog::initShortcutsSection()
{
    m_preferencesDialog.setCategory(SECTION_SHORTCUTS, SECTION_SHORTCUTS, QIcon(SECTION_SHORTCUTS_ICON));
    m_preferencesDialog.setSection(SECTION_SHORTCUTS);

    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/add_file_key"), "Add file"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/add_folder_key"), "Add folder"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/exit_key"), "Exit"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/play_pause_key"), "Play/pause"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/forward_key"), "Forward for 10s"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/backward_key"), "Backward for 10s"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/volume_up_key"), "Volume up"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/volume_down_key"), "Volume down"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/mute_key"), "Mute"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/window_size_1_key"), "Window size 1"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/window_size_2_key"), "Window size 2"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/window_size_3_key"), "Window size 3"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/window_size_4_key"), "Window size 4"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/maximize_key"), "Maximize"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_SHORTCUTS"/full_screen_key"), "Full screen"));
}

void PreferencesDialog::initApplicationSection()
{
    m_preferencesDialog.setCategory(SECTION_APPLICATION, SECTION_APPLICATION, QIcon(SECTION_APPLICATION_ICON));
    m_preferencesDialog.setSection(SECTION_APPLICATION);

    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Bool, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_APPLICATION"/default_app"), "Set as default media application"));
}

void PreferencesDialog::initAudioSection()
{
    m_preferencesDialog.setCategory(SECTION_AUDIO, SECTION_AUDIO, QIcon(SECTION_AUDIO_ICON));
    m_preferencesDialog.setSection(SECTION_AUDIO);


    m_preferencesDialog.appendEntry(new QSettingsEntry(qMetaTypeId<MetaWrapper::AudioChannelEnum>(), new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_AUDIO"/audio_type"), "Audio type"));
}

void PreferencesDialog::initVideoSection()
{
    m_preferencesDialog.setCategory(SECTION_VIDEO, SECTION_VIDEO, QIcon(SECTION_VIDEO_ICON));
    m_preferencesDialog.setSection(SECTION_VIDEO);

    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Bool, new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_VIDEO"/load_subtitles"), "Load external subtitle files for current video"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(qMetaTypeId<IntRange>(), new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_VIDEO"/bightness"), "Brightness"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(qMetaTypeId<IntRange>(), new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_VIDEO"/contrast"), "Contrast"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(qMetaTypeId<IntRange>(), new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_VIDEO"/saturation"), "Saturation"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(qMetaTypeId<IntRange>(), new QSettingsSettingsLoader(&m_preferenceSettings, SECTION_VIDEO"/hue"), "Hue"));
}

void PreferencesDialog::showPreferences()
{
    m_preferencesDialog.execSettings(m_parentWidget);
}

void PreferencesDialog::saveSettings(bool closed)
{
#if DEBUG
    qDebug() << "Changes saved, close flag: " << closed << endl;
#endif
}

void PreferencesDialog::updateTheme(QString &style)
{
    m_parentWidget->setStyleSheet(style);
}
