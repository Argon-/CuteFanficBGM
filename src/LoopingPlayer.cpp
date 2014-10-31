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
    this->mediaplayer->play();
}


void LoopingPlayer::pause()
{
    this->playingClicked = false;
    this->mediaplayer->pause();
}


void LoopingPlayer::setTrack(const QString &s, bool loop) {
    if (!QFile::exists(s)) {
        //mediaplayer->pause();
        this->playlist->clear();
        return;
    }

    bool i = this->isPlaying() || this->playingClicked;
    this->playlist->clear();
    this->playlist->addMedia(QUrl::fromLocalFile(s));
    this->playlist->setCurrentIndex(0);

    if (loop)
        this->playlist->setPlaybackMode(QMediaPlaylist::Loop);
    else
        this->playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

    if (i)
        this->play();
}


void LoopingPlayer::setVolume(int n)
{
    this->mediaplayer->setVolume(n);
}


void LoopingPlayer::togglePlaying()
{
    if (this->isPlaying())
        this->pause();
    else
        this->play();
}


bool LoopingPlayer::hasNoSong()
{
    return this->playlist->isEmpty();
}


bool LoopingPlayer::isAvailable()
{
    return this->mediaplayer && this->mediaplayer->isAvailable();
}


bool LoopingPlayer::isPlaying()
{
    return this->playingClicked || this->mediaplayer->state() == QMediaPlayer::PlayingState;
}


bool LoopingPlayer::isPaused()
{
    return this->mediaplayer->state() == QMediaPlayer::PausedState;
}


bool LoopingPlayer::isStopped()
{
    return this->mediaplayer->state() == QMediaPlayer::StoppedState;
}


bool LoopingPlayer::isLoadingOrBuffering()
{
    return this->mediaplayer->mediaStatus() == QMediaPlayer::BufferingMedia || 
           this->mediaplayer->mediaStatus() == QMediaPlayer::LoadingMedia;
}


bool LoopingPlayer::isFaulty()
{
    return this->mediaplayer->mediaStatus() == QMediaPlayer::UnknownMediaStatus || 
           this->mediaplayer->mediaStatus() == QMediaPlayer::InvalidMedia;
}


LoopingPlayer::~LoopingPlayer()
{
}
