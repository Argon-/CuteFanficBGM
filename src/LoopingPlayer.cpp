/* This file is part of CuteFanficBGM.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#include "LoopingPlayer.h"
#include <QTextStream>
#include <QFile>



LoopingPlayer::LoopingPlayer() : 
    playingClicked(false),
    mediaplayer(new QMediaPlayer(this)),
    playlist(new QMediaPlaylist(mediaplayer))
{
    mediaplayer->setPlaylist(playlist);
}


void LoopingPlayer::play()
{
    this->playingClicked = true;
    mediaplayer->play();
}


void LoopingPlayer::pause()
{
    this->playingClicked = false;
    mediaplayer->pause();
}


void LoopingPlayer::setTrack(const QString &s, bool loop) {
    if (!QFile::exists(s)) {
        //mediaplayer->pause();
        playlist->clear();
        return;
    }

    bool i = this->isPlaying() || this->playingClicked;
    playlist->clear();
    playlist->addMedia(QUrl::fromLocalFile(s));
    playlist->setCurrentIndex(0);

    if (loop)
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    else
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    if (i)
        this->play();
}


void LoopingPlayer::setVolume(int n)
{
    mediaplayer->setVolume(n);
}


void LoopingPlayer::togglePlaying()
{
    if (this->isPlaying())
        this->pause();
    else
        this->play();
}


bool LoopingPlayer::isAvailable()
{
    return mediaplayer && mediaplayer->isAvailable();
}


bool LoopingPlayer::isPlaying()
{
    return this->playingClicked || mediaplayer->state() == QMediaPlayer::PlayingState;
}


bool LoopingPlayer::isPaused()
{
    return mediaplayer->state() == QMediaPlayer::PausedState;
}


bool LoopingPlayer::isStopped()
{
    return mediaplayer->state() == QMediaPlayer::StoppedState;
}


bool LoopingPlayer::isLoadingOrBuffering()
{
    return mediaplayer->mediaStatus() == QMediaPlayer::BufferingMedia || 
            mediaplayer->mediaStatus() == QMediaPlayer::LoadingMedia;
}


bool LoopingPlayer::isFaulty()
{
    return mediaplayer->mediaStatus() == QMediaPlayer::UnknownMediaStatus || 
            mediaplayer->mediaStatus() == QMediaPlayer::InvalidMedia;
}


LoopingPlayer::~LoopingPlayer()
{
}
