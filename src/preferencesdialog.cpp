#include "preferencesdialog.h"
#include "ui_preferences.h"

#include <qsettingsdialog.h>
#include <qsettingssettingsloader.h>
#include <qsettingspropertyentry.h>

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window);
    setModal(true);

    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(showSettings()));

    ui->listWidget->addItem("Test");
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::showSettings()
{
//    QSettings settings(QApplication::applicationDirPath() + "/test.ini", QSettings::IniFormat);
//    //create the dialog
//    QSettingsDialog dialog;
//    // add a new entry
//    dialog.appendEntry(new QSettingsEntry(QMetaType::QString,// <- The display id. In this case, an edit for a QString is loaded, a QLineEdit
//                                          new QSettingsSettingsLoader(&settings, "appName"),// <- The loader loads a value with the key "appName" from the settings
//                                          "App name"));//Other properties of the entry, i.e. The label text

//    //show the dialog (blocking)
//    dialog.execSettings();

    QSettingsDialog dialog;

        QObject::connect(&dialog, &QSettingsDialog::saved, [](bool close) {
            qDebug() << "---- Save completed" << (close ? "with" : "without") << "closing ----";
        });
        QObject::connect(&dialog, &QSettingsDialog::resetted, []() {
            qDebug() << "---- Reset completed ----";
        });
        QObject::connect(&dialog, &QSettingsDialog::canceled, []() {
            qDebug() << "---- Dialog was canceled ----";
        });

        QObject::connect(qApp, &QApplication::applicationNameChanged, []() {
            qDebug() << "Name was changed!!! To" << QApplication::applicationName();
        });

        dialog.appendEntry(new QSettingsPropertyEntry("applicationName", qApp, "property"));

        QSettings settings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);
        dialog.appendEntry(new QSettingsEntry(QMetaType::QDateTime,
                                              new QSettingsSettingsLoader(&settings, "datetime"),
                                              "settings.ini"));

        dialog.openSettings();
}
