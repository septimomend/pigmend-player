#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QWidget>
#include <qsettingsdialog.h>
#include <qsettingssettingsloader.h>
#include <qsettingspropertyentry.h>

class PreferencesDialog : public QWidget
{
    Q_OBJECT

public:
    PreferencesDialog();
    ~PreferencesDialog();

    void updateTheme(QString &style);

private:
    void initParentWidget();
    void initSections();

    QWidget *m_parentWidget;
    QSettings m_preferenceSettings;
    QSettingsDialog m_preferencesDialog;

public slots:
    void showPreferences();
    void saveSettings(bool closed);
};

#endif // PREFERENCESDIALOG_H
