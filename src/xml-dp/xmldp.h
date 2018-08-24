#ifndef XMLDP_H
#define XMLDP_H

#include "tinyxml2/tinyxml2.h"
#include "rapidxml-1.13/rapidxml.hpp"

#include <QtWidgets>
#include <fstream>
#include <vector>

using namespace tinyxml2;
using namespace  rapidxml;
using namespace  std;

struct styles_data_t
{
	QString current_theme;
	QString backcolor;
	QString color;
	QString transbackcolor;
	QString menucolor;
	QString progressSliderTheme;
	QString volumeSliderTheme;
};

class XMLDP
{
public:
	XMLDP();	// cstr
	~XMLDP();	// dstr

	styles_data_t *getStylesXML(QString &path, QString &theme_name);
	int setStylesXML(QString &path, QString &theme_name);

private:
	rapidxml::xml_document<> m_themes_xml;
};

#endif // XMLDP_H
