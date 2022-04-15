/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "mediafileController.h"

int MediafileController::s_audiofiles = 0;
int MediafileController::s_videofiles = 0;

MediafileController::MediafileController(QWidget *parent) : QWidget(parent)
{
    m_lastPath = "/home";
    m_playlist.m_plData.clear();

    std::thread thr(&indexFiles, this);
    thr.detach();
}

void MediafileController::openFile()
{
    QFileDialog fileDialog(this);

    // open file dialog for choosing media files
    QStringList filenames = fileDialog.getOpenFileNames(this,tr("Add files"), m_lastPath,
        tr("All files (*);;"
           "Media (*.mp3 *.mp4);;"
           "Audio (*.mp3, *.wav, *.flac);;"
           "Video (*.mp4);;"
           "Film (*.avi, *.mkv)"));

    // writing chosen files to QMap container by pair of filename and its path
    if (!filenames.isEmpty() )
    {
        for (int i =0;i<filenames.count();i++)
        {
            QFile f(filenames.at(i));
            QFileInfo fileInfo(f.fileName());
            m_playlist.m_plData.insert(fileInfo.fileName(), fileInfo.canonicalFilePath());
        }

        m_lastPath = filenames.last(); // remember last path
        emit filesChosen();            // signal to filling playlist widget by filenames
    }
}

void MediafileController::openFolder()
{
    QFileDialog fileDialog(this);

    // open file dialog for choosing media folder
    QString dir = fileDialog.getExistingDirectory(this, tr("Open Directory"), m_lastPath,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QStringList result;
    QStringList pattern;
    pattern << "*.mp3" << "*.mp4" << "*.avi" << "*.mkv" << "*.flac" << "*.wav";  // set pattern for choosing files
    //QDir currentDir(dir);
    //const QString prefix = dir + QLatin1Char('/');

	QDirIterator dir_it(dir, pattern, QDir::Files, QDirIterator::Subdirectories);
	
	while (dir_it.hasNext())
	{
		QFileInfo fileInfo(dir_it.next());
		m_playlist.m_plData.insert(fileInfo.fileName(), fileInfo.canonicalFilePath());
	}

    // read all files from folder in accordance to pattern
   /* foreach (const QString &match, currentDir.entryList(pattern, QDir::Files | QDir::NoSymLinks))
        result.append(prefix + match);

    if (result.isEmpty())
        return;

    // writing files to QMap container by pair of filename and its path
    for (int i = 0; i < result.size(); i++)
    {
        QFile f(result.at(i));
        QFileInfo fileInfo(f.fileName());
        m_playlist.m_plData.insert(fileInfo.fileName(), fileInfo.canonicalFilePath());
	}*/

    // delete last part of path '/*'
    int pos = dir.lastIndexOf(QChar('/'));
    m_lastPath = dir.left(pos);

	if (!m_playlist.m_plData.isEmpty())
		emit filesChosen();            // signal to filling playlist widget by filenames
}

void MediafileController::indexFiles(MediafileController* mc)
{
    lock_guard<mutex> locker(mc->m_mtx);

    QStringList extensions;
    extensions << "*.mp3" << "*.mp4" << "*.wav" << "*.avi" << "*.mkv" << "*.flac";

#ifdef WIN32
    QDirIterator itC("C://", QStringList() << "*.mp3" << "*.mp4", QDir::Files, QDirIterator::Subdirectories);
    while (itC.hasNext())
    {
        QString file = itC.next();
        if (file.contains(QString(".mp3")) || file.contains(QString(".wav")) || file.contains(QString(".flac")))
            ++s_audiofiles;
        if (file.contains(QString(".mp4")) || file.contains(QString(".avi")) || file.contains(QString(".mkv")))
            ++s_videofiles;
        mc->filesFound(s_audiofiles, s_videofiles, false);
    }
    QDirIterator itD("D://", extensions, QDir::Files, QDirIterator::Subdirectories);
    while (itD.hasNext())
    {
        iQString file = itD.next();
        if (file.contains(QString(".mp3")) || file.contains(QString(".wav")) || file.contains(QString(".flac")))
            ++s_audiofiles;
        if (file.contains(QString(".mp4")) || file.contains(QString(".avi")) || file.contains(QString(".mkv")))
            ++s_videofiles;
        mc->filesFound(s_audiofiles, s_videofiles, false);
    }
    QDirIterator itE("E://", extensions, QDir::Files, QDirIterator::Subdirectories);
    while (itE.hasNext())
    {
        iQString file = itE.next();
        if (file.contains(QString(".mp3")) || file.contains(QString(".wav")) || file.contains(QString(".flac")))
            ++s_audiofiles;
        if (file.contains(QString(".mp4")) || file.contains(QString(".avi")) || file.contains(QString(".mkv")))
            ++s_videofiles;
        mc->filesFound(s_audiofiles, s_videofiles, false);
    }
    QDirIterator itF("F://", QStringList() << extensions, QDir::Files, QDirIterator::Subdirectories);
    while (itF.hasNext())
    {
        QString file = itF.next();
        if (file.contains(QString(".mp3")) || file.contains(QString(".wav")) || file.contains(QString(".flac")))
            ++s_audiofiles;
        if (file.contains(QString(".mp4")) || file.contains(QString(".avi")) || file.contains(QString(".mkv")))
            ++s_videofiles;
        mc->filesFound(s_audiofiles, s_videofiles, false);
    }
    emit mc->filesFound(s_audiofiles, s_videofiles, true);
#elif unix
    QDirIterator it("/home", extensions, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext())
    {
        QString file = it.next();
        if (file.contains(QString(".mp3")) || file.contains(QString(".wav")) || file.contains(QString(".flac")))
            ++s_audiofiles;
        if (file.contains(QString(".mp4")) || file.contains(QString(".avi")) || file.contains(QString(".mkv")))
            ++s_videofiles;
        emit mc->filesFound(s_audiofiles, s_videofiles, false);
    }
    emit mc->filesFound(s_audiofiles, s_videofiles, true);
#endif
}
