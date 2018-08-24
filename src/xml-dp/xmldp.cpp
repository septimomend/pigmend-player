/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "xmldp.h"

XMLDP::XMLDP()
{
}

XMLDP::~XMLDP()
{
}

styles_data_t *XMLDP::getStylesXML(QString &path, QString &theme_name)
{
	styles_data_t *themes_data = new styles_data_t;

	xml_node<> *root_node;
	ifstream themesFile(path.toStdString().c_str());

	if (!themesFile.is_open())
	{
		qCritical() << __FUNCTION__ << ": can't open file " << path << endl;
		abort();
	}

	vector<char> buffer((istreambuf_iterator<char>(themesFile)), istreambuf_iterator<char>());

	buffer.push_back('\0');
	m_themes_xml.parse<rapidxml::parse_full | rapidxml::parse_no_data_nodes>(&buffer[0]);
	root_node = m_themes_xml.first_node("PigmendPlayer");

	xml_node<> *themes_node = root_node->first_node("Themes");
	themes_data->current_theme = theme_name.isEmpty() ? themes_node->first_node("CurrentTheme")->value() : theme_name;

	for(xml_node<> *theme_data_node = themes_node->first_node("Theme"); theme_data_node; theme_data_node = theme_data_node->next_sibling())
	{
		if (themes_data->current_theme == theme_data_node->first_attribute()->value())
		{
			themes_data->backcolor = theme_data_node->first_node("backcolor")->value();
			themes_data->color = theme_data_node->first_node("color")->value();
			themes_data->transbackcolor = theme_data_node->first_node("transbackcolor")->value();
			themes_data->menucolor = theme_data_node->first_node("menucolor")->value();
			themes_data->progressSliderTheme = theme_data_node->first_node("progressSliderTheme")->value();
			themes_data->volumeSliderTheme = theme_data_node->first_node("volumeSliderTheme")->value();
		}
	}

	if (themes_data->color.isEmpty())
	{
		qWarning() << __FUNCTION__ << ": Undefined theme" << endl;
		return nullptr;
	}

	return themes_data;
}

int XMLDP::setStylesXML(QString &path, QString &theme_name)
{
	int rc = -1;
	tinyxml2::XMLDocument xml_doc;

	tinyxml2::XMLError eResult = xml_doc.LoadFile(path.toStdString().c_str());

	if (eResult != tinyxml2::XML_SUCCESS)
	{
		qCritical() << __FUNCTION__ << ": can't open file " << path << endl;
		abort();
	}

	tinyxml2::XMLNode *root = xml_doc.FirstChildElement("PigmendPlayer");

	if (root == nullptr)
	{
		qWarning() << __FUNCTION__ << ": no root child" << endl;
		return rc;
	}

	tinyxml2::XMLElement *themes = root->FirstChildElement("Themes");
	if (!themes)
	{
		qWarning() << __FUNCTION__ << "No themes" << endl;
		return rc;
	}

	tinyxml2::XMLElement *curr_theme = themes->FirstChildElement("CurrentTheme");
	if (!curr_theme)
	{
		qWarning() << __FUNCTION__ << "Can't set current theme" << endl;
		return rc;
	}

	curr_theme->SetText(theme_name.toStdString().c_str());

	xml_doc.SaveFile(path.toStdString().c_str());

	rc = 0;
	return rc;
}
