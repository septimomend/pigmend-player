/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef ABOUTPIGMEND_H
#define ABOUTPIGMEND_H

#include "config-dp/config.h"
#include "xml-dp/xmldp.h"

#include <QDialog>

namespace Ui {
class AboutPigmend;
}

class AboutPigmend : public QDialog
{
    Q_OBJECT

public:
	explicit AboutPigmend(conf_data_t *conf_data, QWidget *parent = nullptr);
    ~AboutPigmend();

private:
	void loadInfoAbout();

private:
    Ui::AboutPigmend *ui;

	conf_data_t *m_conf_data;
	XMLDP m_xmldp;
};

#endif // ABOUTPIGMEND_H
