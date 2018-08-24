/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "aboutpigmend.h"
#include "ui_aboutpigmend.h"

AboutPigmend::AboutPigmend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutPigmend)
{
    ui->setupUi(this);
    ui->player_name->setText("<font color=\"#59A581\">Pigmend</font> <font color=\"#F0F4F8\">Player</font>");
    ui->author_label->setText("<a href=\"https://github.com/septimomend\"><font color=\"#F05A2F\">Ivan Chapkailo</font></a>"
        "<font color=\"grey\"> © </font><font color=\"#F05A2F\">2018</font>");
    ui->author_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->author_label->setOpenExternalLinks(true);
    ui->version->setText("<font color=\"grey\">Version: </font><font color=\"#F05A2F\">1.0</font>");
    ui->description->setText("<font color=\"grey\">Pigmend Player is simple, fast and crossplatformed<br/>application.<br/>"
                             "Supported OS: Windows, Linux, Mac.<br/><br/>"
                             "<u>Currently supported formats:</u><br/>"
                             " • Audio: MP3, WAV, FLAC;<br/>"
                             " • Video: MP4, AVI, MKV.</font>");
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

AboutPigmend::~AboutPigmend()
{
    delete ui;
}
