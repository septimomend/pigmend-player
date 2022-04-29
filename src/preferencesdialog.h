/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include <qsettingsdialog.h>
#include <qsettingssettingsloader.h>
#include <qsettingspropertyentry.h>
#include <qsettingswidgetdialogengine.h>
#include "plugin_installer/plugindialog.h"

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
    void initGeneralSection();
    void initViewSection();
    void initShortcutsSection();
    void initApplicationSection();
    void initAudioSection();
    void initVideoSection();

    QWidget *m_parentWidget;
    QSettings m_preferenceSettings;
    QSettingsDialog m_preferencesDialog;

public slots:
    void showPreferences();
    void saveSettings(bool closed);
};

class StateLoader : public QSimpleSettingsLoader
{
public:
    StateLoader(QVariant value = QVariant()) :
        value(value)
    {}

    bool load(QVariant &data, bool &userEdited) override {
        data = this->value;
        userEdited = true;
        return true;
    }
    bool save(const QVariant &data) override {
        this->value = data;
        return true;
    }
    bool reset() override {
        return true;
    }

private:
    QVariant value;
};

#endif // PREFERENCESDIALOG_H
