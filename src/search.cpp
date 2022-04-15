/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "search.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setModal(true);

    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(checkMatches()));
    ui->searchPicLabel->setStyleSheet("image: url(:/custom/img/custom/search_no_match.png)");
    ui->searchPicLabel->hide();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        checkMatches();
    else if (event->key() == Qt::Key_Escape)
        this->close();

    event->accept();
}

void SearchDialog::setStartTips()
{
    setPlaceholer();
    ui->searchPicLabel->hide();
    ui->noMatchesLabel->clear();
    if (m_playlist.m_plData.empty())
    {
        ui->noMatchesLabel->setText(QString("Playlist is empty, here is nothing to search"));
        return;
    }
}

void SearchDialog::setPlaceholer()
{
    ui->searchLineEdit->clear();
    ui->searchLineEdit->setPlaceholderText(QString("search..."));
    ui->searchLineEdit->setFocus();
}

void SearchDialog::checkMatches()
{
    //QListWidgetItem *item = new QListWidgetItem();
    if(!ui->searchLineEdit->text().isEmpty())
    {
        for(auto it = m_playlist.m_plData.begin(); it != m_playlist.m_plData.end(); ++it)
        {
            // if here is accordance with current filename
            if (it.key().toLower().contains(QString(ui->searchLineEdit->text().toLower())))
            {
                //item->setText(it.key());
                emit matchesFound(QString(it.key()));
                ui->noMatchesLabel->setText(QString(it.key()));
                close();
                break;
            }
            else if(it == m_playlist.m_plData.end()-1)
            {
                ui->noMatchesLabel->setText(QString("No matches found..."));
                ui->searchPicLabel->show();
            }
        }
    }
    else if (!m_playlist.m_plData.empty())
        ui->noMatchesLabel->setText(QString("Please, input data or press cancel"));
}

void SearchDialog::updateTheme(styles_data_t *style)
{
	ui->cancelButton->setStyleSheet(style->backcolor);
	ui->okButton->setStyleSheet(style->backcolor);
	ui->searchLineEdit->setStyleSheet(style->color);
}
