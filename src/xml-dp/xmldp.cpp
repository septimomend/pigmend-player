/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "xmldp.h"
#include "../config-dp/config.h"

XMLDP::XMLDP()
{
}

XMLDP::~XMLDP()
{
}

styles_data_t *XMLDP::getStylesXML(QString &path, QString &theme_name)
{
	xml_document<> themes_xml;
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
	themes_xml.parse<parse_full | parse_no_data_nodes>(&buffer[0]);
	root_node = themes_xml.first_node("PigmendPlayer");

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
			themes_data->playlistTheme = theme_data_node->first_node("playlistTheme")->value();
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

about_data_t *XMLDP::getInfoAbout(QString &path)
{
	xml_document<> about_xml;
	about_data_t *about_data = new about_data_t;

	if (!about_data)
	{
		qCritical() << __FUNCTION__ << ": fail to allocate memory." << endl;
		return nullptr;
	}

	xml_node<> *root_node;
	ifstream about_file(path.toStdString().c_str());

	if (!about_file.is_open())
	{
		qCritical() << __FUNCTION__ << ": can't open file " << path << endl;
		return nullptr;
	}

	vector<char> buffer((istreambuf_iterator<char>(about_file)), istreambuf_iterator<char>());

	buffer.push_back('\0');
	about_xml.parse<parse_validate_closing_tags>(&buffer[0]);

	root_node = about_xml.first_node("PigmendPlayer");

	about_data->software_name = root_node->first_node("SoftwareName")->value();
	about_data->version = root_node->first_node("Version")->value();
	about_data->author_name = root_node->first_node("Author")->first_node("Name")->value();
	about_data->author_url = root_node->first_node("Author")->first_node("URL")->value();
	about_data->year = root_node->first_node("Year")->value();
	about_data->libs = root_node->first_node("Libs")->value();

	xml_node<> *releases_node = root_node->first_node("Releases");

	for (xml_node<> *release_data_node = releases_node->first_node("Release"); release_data_node; release_data_node = release_data_node->next_sibling())
	{
		about_data->releases_version.push_back(release_data_node->first_node("Version")->value());
		about_data->releases_url.push_back(release_data_node->first_node("URL")->value());
	}

	return about_data;
}

QString XMLDP::getAudioAnimation(QString path_to_xml, QString animation_name)
{
	xml_document<> animations_xml;
	xml_node<> *root_node;

    QString pathAudioAnimation(getDBXML());
    QString path(getDBXML());
	path.append(path_to_xml);

	ifstream animationsFile(path.toStdString().c_str());

	if (!animationsFile.is_open())
	{
		qCritical() << __FUNCTION__ << ": can't open file " << path << endl;
		abort();
	}

	vector<char> buffer((istreambuf_iterator<char>(animationsFile)), istreambuf_iterator<char>());

	buffer.push_back('\0');
	animations_xml.parse<parse_full | parse_no_data_nodes>(&buffer[0]);
	root_node = animations_xml.first_node("PPAnimations");

	xml_node<> *animations_node = root_node->first_node("AudioAnimations");
	QString current_animation = animation_name.isEmpty() ? root_node->first_node("CurrentAudioAnimation")->value() : animation_name;

	for(xml_node<> *animation_data_node = animations_node->first_node("Animation"); animation_data_node; animation_data_node = animation_data_node->next_sibling())
	{
		if (current_animation == animation_data_node->first_attribute("name")->value())
			return pathAudioAnimation.append(animation_data_node->first_node("Path")->value());
	}

	return "";
}
