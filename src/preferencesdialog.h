#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include <qsettingsdialog.h>
#include <qsettingssettingsloader.h>
#include <qsettingspropertyentry.h>
#include <qsettingswidgetdialogengine.h>
#include <qsettingsdialogwidget.h>

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

// TODO create QDialog via designer and move into separate header
class PluginDialog : public QSettingsWidget<QDialog>
{
public:
    PluginDialog(QWidget *parent = nullptr) :
        QSettingsWidget(parent)
    {
        this->setWindowTitle("Plugins Installer");
        QHBoxLayout *layout = new QHBoxLayout;
        QLabel *label = new QLabel;
        label->setText("Demo, not functional");
        layout->addWidget(label);
        this->setLayout(layout);
    }

    void setValue(const QVariant &) override {}
    QVariant getValue() const override {
        return QVariant();
    }
    void resetValue() override {}
};

#endif // PREFERENCESDIALOG_H
