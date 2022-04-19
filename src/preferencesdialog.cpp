#include <QApplication>

#include "preferencesdialog.h"
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
    qDebug() << QApplication::applicationDirPath()  << endl;
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
    /*
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QString,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "appName"),
                                          "App name"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QString,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "companyName"),
                                          "Company name"));

    m_preferencesDialog.setGroup("versionGroup", 0, "Version", true, "Please configure the version");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Int,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "version/major"),
                                          "Major",
                                          false,
                                          QString(),
                                          {{"minimum", 0}, {"maximum", 9}}));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Int,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "version/minor"),
                                          "Minor",
                                          false,
                                          QString(),
                                          {{"minimum", 0}, {"maximum", 9}}));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Int,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "version/patch"),
                                          "Patch",
                                          false,
                                          QString(),
                                          {{"minimum", 0}, {"maximum", 9}}));

    m_preferencesDialog.unsetGroup();
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QString,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "authorName"),
                                          "Load Programmer",
                                          true));

    m_preferencesDialog.setSection("more", "More Stuff");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Bool,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "allow/A"),
                                          "Allow Option A"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Bool,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "allow/B"),
                                          "Allow Option B"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::Bool,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "allow/C"),
                                          "Allow Option C"));
*/
    m_preferencesDialog.setCategory(SECTION_GENERAL, SECTION_GENERAL, QIcon(SECTION_GENERAL_ICON));
    m_preferencesDialog.setSection(".");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QUrl,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretUrl"),
                                          "Very secret url"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretColor"),
                                          "Very secret color"));

    m_preferencesDialog.setCategory(SECTION_VIEW, SECTION_VIEW, QIcon(SECTION_VIEW_ICON));
    m_preferencesDialog.setSection(".");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QDateTime,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretUrl"),
                                          "Very secret url"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretColor"),
                                          "Very secret color"));

    m_preferencesDialog.setCategory(SECTION_SHORTCUTS, SECTION_SHORTCUTS, QIcon(SECTION_SHORTCUTS_ICON));
    m_preferencesDialog.setSection(SECTION_SHORTCUTS);
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "add_file_key"),
                                          "Add file"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "add_folder_key"),
                                          "Add folder"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "exit_key"),
                                          "Exit"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "play_pause_key"),
                                          "Play/pause"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "forward_key"),
                                          "Forward for 10s"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "backward_key"),
                                          "Backward for 10s"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "volume_up_key"),
                                          "Volume up"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "volume_down_key"),
                                          "Volume down"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "mute_key"),
                                          "Mute"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "window_size_1_key"),
                                          "Window size 1"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "window_size_2_key"),
                                          "Window size 2"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "window_size_3_key"),
                                          "Window size 3"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "window_size_4_key"),
                                          "Window size 4"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "maximize_key"),
                                          "Maximize"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "maximize_key"),
                                          "Maximize"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "full_screen_key"),
                                          "Full screen"));

    m_preferencesDialog.setCategory(SECTION_APPLICATION, SECTION_APPLICATION, QIcon(SECTION_APPLICATION_ICON));
    m_preferencesDialog.setSection(".");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QDateTime,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretUrl"),
                                          "Very secret url"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretColor"),
                                          "Very secret color"));

    m_preferencesDialog.setCategory(SECTION_AUDIO, SECTION_AUDIO, QIcon(SECTION_AUDIO_ICON));
    m_preferencesDialog.setSection(".");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QDateTime,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretUrl"),
                                          "Very secret url"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretColor"),
                                          "Very secret color"));

    m_preferencesDialog.setCategory(SECTION_VIDEO, SECTION_VIDEO, QIcon(SECTION_VIDEO_ICON));
    m_preferencesDialog.setSection(".");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QFont,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretUrl"),
                                          "Very secret url"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretColor"),
                                          "Very secret color"));

    m_preferencesDialog.setCategory(SECTION_ABOUT, SECTION_ABOUT, QIcon(SECTION_ABOUT_ICON));
    m_preferencesDialog.setSection(".");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QKeySequence,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretUrl"),
                                          "Very secret url"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretColor"),
                                          "Very secret color"));
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
