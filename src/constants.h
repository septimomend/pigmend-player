/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtWidgets>

struct styles_data_t
{
	QString current_theme;
	QString backcolor;
	QString color;
	QString transbackcolor;
	QString menucolor;
	QString progressSliderTheme;
	QString volumeSliderTheme;
	QString playlistTheme;
};

struct about_data_t
{
	QString software_name;
	QString version;
	QString author_name;
	QString author_url;
	QString year;
	QString contributors;
	QString libs;
	QString resources;
	QStringList releases_version;
	QStringList releases_url;
};

#endif // CONSTANTS_H
