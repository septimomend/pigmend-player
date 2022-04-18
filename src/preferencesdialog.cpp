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
    m_preferenceSettings(QApplication::applicationDirPath() + "/../config/settings.ini", QSettings::IniFormat)
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
    m_preferencesDialog.setSection(".");
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QDateTime,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretUrl"),
                                          "Very secret url"));
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
                                          new QSettingsSettingsLoader(&m_preferenceSettings, "secretColor"),
                                          "Very secret color"));

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
    m_preferencesDialog.appendEntry(new QSettingsEntry(QMetaType::QDateTime,
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
