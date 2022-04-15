/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

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
    void matchesFound(QString);

public slots:
    void setStartTips();

protected:
    void keyPressEvent(QKeyEvent *event) override;

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
