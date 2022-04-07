/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "mediaplayer.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QScreen>
#include <QDebug>

/*
 * TODO
 * Logger
 * Avoid hardcode - use defines
 * */

#if DEBUG
#define CONFIG_INIT_PATH PRO_FILE_PWD "/../config/config.ini"
#endif

void errorMsg(QString msg)
{
    QMessageBox msgErr;
    msgErr.setText(msg);
    msgErr.setIcon(QMessageBox::Critical);
    msgErr.setWindowTitle("Error");
    msgErr.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("PigmendPlayer");
    a.setApplicationVersion("1.1");

    QCommandLineParser cmdParser;
    cmdParser.setApplicationDescription("Pigmend Player - crossplatform media player");
    cmdParser.addHelpOption();
    cmdParser.addVersionOption();

    QCommandLineOption configFileOption(QStringList() << "c" << "config",
        QApplication::translate("PigmendPlayer", "Specify configuration file"),
        QApplication::translate("PigmendPlayer", "file"));

    QCommandLineOption databaseDirOption(QStringList() << "x" << "xmlbase",
        QApplication::translate("PigmendPlayer", "Specify XML database directory"),
        QApplication::translate("PigmendPlayer", "directory"));

    cmdParser.addOption(configFileOption);
    cmdParser.addOption(databaseDirOption);
    cmdParser.process(a);

    QStringList configFile = cmdParser.values(configFileOption);

    if (configFile.empty())
    {
        qCritical() << "Critical: No configuration file found" << endl;
        errorMsg("No configuration file found");
        return 1;
    }

    QStringList xmlDir = cmdParser.values(databaseDirOption);

    if (xmlDir.empty())
    {
        qCritical() << "Critical: No database directory found" << endl;
        errorMsg("No database directory found");
        return 1;
    }

#if DEBUG
	const char *init_config_file = CONFIG_INIT_PATH;
#else
    QByteArray confFile = configFile.takeFirst().toLocal8Bit();
    const char *init_config_file = confFile.constData();
    QByteArray xmlDb = xmlDir.takeFirst().toLocal8Bit();
    const char *database = xmlDb.constData();
#endif

    conf_data_t *conf_data;

    if (!(conf_data = config_init(init_config_file)))
    {
        qCritical() << "Critical: Invalid configuration file" << endl;
        errorMsg("Invalid configuration file");
		return 1;
    }

    setDBXML(database);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screen_geometry = screen->geometry();

	MediaPlayer *mediaPlayer = new MediaPlayer(screen_geometry, conf_data);
    mediaPlayer->show();
    mediaPlayer->postInit();

    return a.exec();
}
