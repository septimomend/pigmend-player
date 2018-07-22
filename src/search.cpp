/*
MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "search.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(checkMatches()));
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::setStartTips()
{
    setPlaceholer();
    ui->noMatchesLabel->clear();
    if (m_playlist.m_plData.empty())
    {
        ui->noMatchesLabel->setText(QString("Playlist is empty, here are nothing to search"));
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
    QListWidgetItem *item = new QListWidgetItem();
    if(!ui->searchLineEdit->text().isEmpty())
    {
        for(auto it = m_playlist.m_plData.begin(); it != m_playlist.m_plData.end(); ++it)
        {
            // if here is accordance with current filename
            if (it.key().toLower().contains(QString(ui->searchLineEdit->text().toLower())))
            {
                item->setText(it.key());
                emit matchesFound(item);
                ui->noMatchesLabel->setText(QString(it.key()));
                close();
                break;
            }
            else if(it == m_playlist.m_plData.end()-1)
                ui->noMatchesLabel->setText(QString("No matches, please, try again"));
        }
    }
    else
        ui->noMatchesLabel->setText(QString("Please, input data or press cancel"));
}

void SearchDialog::updateTheme(QString theme)
{
    QString backcolor;
    QString color;

    if(theme == "blue mend")
    {
        backcolor = "background-color: rgb(0, 170, 127); color: rgb(0, 170, 127);";
        color = "color: rgb(0, 170, 127)";
    }
    else if(theme == "orange mend")
    {
        backcolor = "background-color: rgb(255, 85, 0); color: rgb(255, 85, 0);";
        color = "color: rgb(255, 85, 0)";
    }
    else if (theme == "grey mend")
    {
        backcolor = "background-color: rgb(105, 105, 105); color: rgb(105, 105, 105);";
        color = "color: rgb(105, 105, 105)";
    }
    else if (theme == "dark grey mend")
    {
        backcolor = "background-color: rgb(47, 79, 79); color: rgb(47, 79, 79);";
        color = "color: rgb(47, 79, 79)";
    }
    else
    {
        qDebug() << "Undefined theme data";
        return;
    }

    ui->cancelButton->setStyleSheet(backcolor);
    ui->okButton->setStyleSheet(backcolor);
    ui->searchLineEdit->setStyleSheet(color);
}
