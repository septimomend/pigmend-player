/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef MEDIAFILECONTROLLER_H
#define MEDIAFILECONTROLLER_H

#include <QWidget>
#include <QFileDialog>
#include <thread>
#include <QDebug>
#include <QDirIterator>
#include <mutex>

using namespace std;

#include "playlistSingleton.h"

class MediafileController : public QWidget
{
    Q_OBJECT
public:
    explicit MediafileController(QWidget *parent = nullptr);

    static void indexFiles(MediafileController *mc);

signals:
    void filesChosen();
    void filesFound(int, int, bool);

public slots:
    void openFile();                    // opens dialog for choosing files and adding them to the playlist QMap
    void openFolder();                  // opens dialog for choosing folder and adding its contains to the playlist QMap

public:
    static int s_audiofiles, s_videofiles;

private:
    QString m_lastPath;                 // string that remembers last path after opening files/folder
    PlaylistSingleton &m_playlist = PlaylistSingleton::getInstance();   // singleton instance
    mutex m_mtx;
};

#endif // MEDIAFILECONTROLLER_H
