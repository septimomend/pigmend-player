/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "mediaplayer.h"
#include <QApplication>
#include <QScreen>

#define CONFIG_INIT_PATH PRO_FILE_PWD "/../config/config.ini"

int main(int argc, char *argv[])
{
	conf_data_t *conf_data;
	const char *init_config_file = CONFIG_INIT_PATH;

	if (!(conf_data = config_init(init_config_file)))
		return 1;

    QApplication a(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screen_geometry = screen->geometry();

	MediaPlayer *mediaPlayer = new MediaPlayer(screen_geometry, conf_data);
    mediaPlayer->show();

    return a.exec();
}
