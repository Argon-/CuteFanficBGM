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
