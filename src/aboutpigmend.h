/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef ABOUTPIGMEND_H
#define ABOUTPIGMEND_H

#include <QDialog>

namespace Ui {
class AboutPigmend;
}

class AboutPigmend : public QDialog
{
    Q_OBJECT

public:
    explicit AboutPigmend(QWidget *parent = 0);
    ~AboutPigmend();

private:
    Ui::AboutPigmend *ui;
};

#endif // ABOUTPIGMEND_H
