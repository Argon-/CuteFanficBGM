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
 
#ifndef LOOPINGPLAYER_H
#define LOOPINGPLAYER_H

#include <QObject>
#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>



class LoopingPlayer : public QObject
{
    Q_OBJECT

public:
    explicit LoopingPlayer();
    ~LoopingPlayer();

    void pause();
    void play();
    void togglePlaying();
    void setVolume(int n);
    void setTrack(const QString &s, bool loop = true);
    bool hasNoSong();
    bool isAvailable();
    bool isPlaying();
    bool isPaused();
    bool isStopped();
    bool isLoadingOrBuffering();
    bool isFaulty();

private:
    bool playingClicked;
    QMediaPlayer   *mediaplayer;
    QMediaPlaylist *playlist;

};

#endif // LOOPINGPLAYER_H
