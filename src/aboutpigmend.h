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
