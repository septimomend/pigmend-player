/*

MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SEARCH_H
#define SEARCH_H

#include <QDebug>
#include <QDialog>
#include <QListWidgetItem>
#include <QShortcut>

#include "playlistSingleton.h"
#include "xml-dp/xmldp.h"

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();

    void setPlaceholer();
	void updateTheme(styles_data_t *style);

signals:
    void matchesFound(QListWidgetItem *);

public slots:
    void setStartTips();

private slots:
    void checkMatches();

private:
    Ui::SearchDialog *ui;
    PlaylistSingleton &m_playlist = PlaylistSingleton::getInstance();

    // shortcuts
    QShortcut *m_okSC;
    QShortcut *m_cancelSC;
};

#endif // SEARCH_H
