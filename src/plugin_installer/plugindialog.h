/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QDialog>
#include <qsettingsdialogwidget.h>
#include "../constants.h"

namespace Ui {
class PluginDialog;
}

class PluginDialog : public QSettingsWidget<QDialog>
{
    Q_OBJECT

public:
    explicit PluginDialog(QWidget *parent = nullptr);
    ~PluginDialog();

    void setValue(const QVariant &) override;
    QVariant getValue() const override;
    void resetValue() override;
    static void updateTheme(styles_data_t *style);

    static styles_data_t *m_style;

private:
    Ui::PluginDialog *ui;

    void initStylesheet();
};

#endif // PLUGINDIALOG_H
