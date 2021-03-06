/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "aboutpigmend.h"
#include "ui_aboutpigmend.h"

AboutPigmend::AboutPigmend(conf_data_t *conf_data, QWidget *parent) :
	QDialog(parent), ui(new Ui::AboutPigmend), m_conf_data(conf_data)
{
    ui->setupUi(this);
	setModal(true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(close()));

	loadInfoAbout();
}

AboutPigmend::~AboutPigmend()
{
    delete ui;
}

void AboutPigmend::loadInfoAbout()
{
	QString about_file = PRO_FILE_PWD;
	about_file.append(static_cast<char*>(config_get_data(ABOUT_CONFIG, m_conf_data)));

	about_data_t *about = m_xmldp.getInfoAbout(about_file);

	if (!about)
	{
		qWarning() << __FUNCTION__ << ": detected nullptr" << endl;
		return;
	}

	ui->player_name->setText("<font color=\"#59A581\">" + about->software_name.split(" ").at(0) +
		"</font> <font color=\"#F0F4F8\">" + about->software_name.split(" ").at(1) + "</font>");
	ui->author_label->setText("<a href=\"" + about->author_url + "\"><font color=\"#F05A2F\">" + about->author_name + "</font></a>"
		"<font color=\"grey\"> © </font><font color=\"#F05A2F\">" + about->year + "</font>");
	ui->author_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui->author_label->setOpenExternalLinks(true);
	ui->version->setText("<font color=\"grey\">Version: </font><font color=\"#F05A2F\">" + about->version + "</font>");
	ui->description->setText("<font color=\"grey\">Pigmend Player is simple, fast and crossplatformed<br/>application.<br/>"
							 "Supported OS: Windows, Linux, Mac.<br/><br/>"
							 "<u>Currently supported formats:</u><br/>"
							 " • Audio: MP3, WAV, FLAC;<br/>"
							 " • Video: MP4, AVI, MKV.</font>");
}
