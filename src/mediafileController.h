/*

MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
