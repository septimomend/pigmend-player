/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "mediaplayer.h"
#include "constants.h"
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

#if DEBUG_CONF
#define CONFIG_INIT_PATH PRO_FILE_PWD "/../config/config.ini"
#endif

class TranslatorInjector : public QTranslator
{
public:
    QString translate(const char *context, const char *sourceText, const char *disambiguation, int n) const override
    {
        if (context == QStringLiteral("AudioChannelEnum"))
        {
            if (!strcmp(sourceText, "Stereo"))
                return "Stereo";
            else if (!strcmp(sourceText, "Channel4"))
                return "4-channel";
            else if (!strcmp(sourceText, "Channel4_1"))
                return "4.1-channel";
            else if (!strcmp(sourceText, "Channel5"))
                return "5-channel";
            else if (!strcmp(sourceText, "Channel5_1"))
                return "5.1-channel";
            else if (!strcmp(sourceText, "AC3"))
                return "AC3 Passthrough";
            else
                return sourceText;
        }
        if (context == QStringLiteral("SupportedLanguagesEnum"))
        {
            if (!strcmp(sourceText, "EN"))
                return "English";
            else if (!strcmp(sourceText, "UA"))
                return "Ukrainian";
            else
                return sourceText;
        }
        else
            return QTranslator::translate(context, sourceText, disambiguation, n);
    }
};

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
    TranslatorInjector tj;
    QApplication::installTranslator(&tj);

    REGISTER_FLAG_CONVERTERS(MetaWrapper::AudioChannelEnum);

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

#if DEBUG_CONF
    const char *database = CONFIG_INIT_PATH;
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
