/*
MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

LINK: https://github.com/septimomend/pigmend-player
*/

#include "mediaplayer.h"
#include "config_src/config.h"
#include <QApplication>
#include <QScreen>

#define CONFIG_INIT_PATH PRO_FILE_PWD "/../config/config.ini"

int main(int argc, char *argv[])
{
	conf_data_t *conf_data;
	const char *init_config_file = CONFIG_INIT_PATH;

	if (!(conf_data = config_init(init_config_file)))
		return 1;

	char *theme_config_file = static_cast<char*>(config_get_data(THEME_CONFIG, conf_data));
	qDebug() << theme_config_file;

    QApplication a(argc, argv);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screen_geometry = screen->geometry();

    MediaPlayer *mediaPlayer = new MediaPlayer(screen_geometry);
    mediaPlayer->show();

    return a.exec();
}
