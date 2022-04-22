/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "plugindialog.h"
#include "ui_plugindialog.h"

styles_data_t *PluginDialog::m_style;

PluginDialog::PluginDialog(QWidget *parent) :
    ui(new Ui::PluginDialog)
{
    (void)parent;
    initStylesheet();

    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

PluginDialog::~PluginDialog()
{
    delete ui;
}

void PluginDialog::setValue(const QVariant &)
{
}

QVariant PluginDialog::getValue() const
{
    return QVariant();
}

void PluginDialog::resetValue()
{
}

void PluginDialog::updateTheme(styles_data_t *style)
{
    m_style = style;
}

void PluginDialog::initStylesheet()
{
    ui->setupUi(this);
    setWindowTitle("Plugins Installer");
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/icon/img/icons/pigmend_setup.png"));
    setStyleSheet(m_style->pluginsTheme);
    ui->okButton->setStyleSheet(m_style->backcolor);
}
