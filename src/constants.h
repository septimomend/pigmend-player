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
    QString buttonTheme;
    QString buttonCheckedTheme;
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
	QString software_url;
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

struct animation_info_t
{
	QString animation_name;
	QString animation_path;
};

namespace constants
{
// animations
static const char *NONE_ANIMATION = "noneAnimation";
static const char *DEFAULT_ANIMATION = "defaultAnimation";
}

#endif // CONSTANTS_H
