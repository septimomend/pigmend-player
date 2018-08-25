/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "playlistSingleton.h"

PlaylistSingleton::PlaylistSingleton(QObject *parent)
{
	parent = nullptr;
}

PlaylistSingleton::~PlaylistSingleton()
{

}

PlaylistSingleton& PlaylistSingleton::getInstance()
{
    static PlaylistSingleton instance;
    return instance;
}

size_t PlaylistSingleton::clearPlaylistData()
{
    if(!m_plData.isEmpty())
    {
        m_plData.clear();
        m_shuffledData.clear();
    }
	return size_t(m_plData.size());
}

size_t PlaylistSingleton::makeShuffle(bool shuffleMode)
{
    // if the suffle mode is enabled - copy filepath of playlist data to the vector
    // and shuffle this vector by random_shuffle() algorithm
    m_shuffledData.clear();
    if(shuffleMode)
    {
        for(auto it = m_plData.begin(); it != m_plData.end(); ++it)
            m_shuffledData.push_back(it.value());
        std::random_shuffle(m_shuffledData.begin(), m_shuffledData.end());
    }
    else
        m_shuffledData.clear();

	return size_t(m_shuffledData.size());
}
