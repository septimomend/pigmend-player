/*
MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
