/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef XMLDP_H
#define XMLDP_H

#include "tinyxml2/tinyxml2.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "constants.h"

#include <QtWidgets>
#include <fstream>
#include <vector>

using namespace tinyxml2;
using namespace  rapidxml;
using namespace  std;

class XMLDP
{
public:
	XMLDP();	// cstr
	~XMLDP();	// dstr

	styles_data_t *getStylesXML(QString &path, QString &theme_name);
	int setStylesXML(QString &path, QString &theme_name);
	about_data_t *getInfoAbout(QString &path);
};

#endif // XMLDP_H
