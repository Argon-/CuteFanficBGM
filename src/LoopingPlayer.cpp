#include "LoopingPlayer.h"
#include <QDebug>
#include <QTextStream>



LoopingPlayer::LoopingPlayer() : 
    playingClicked(false),
    mediaplayer(new QMediaPlayer(this)),
    playlist(new QMediaPlaylist(mediaplayer))
{
    //playlist->setPlaybackMode(QMediaPlaylist::Loop);
    mediaplayer->setPlaylist(playlist);

    /*
    if (mediaplayer->availability() == QMultimedia::Available) {
        qDebug() << "Player available";
        service = mediaplayer->service();
        if (service != NULL) {
            qDebug() << "   Retrieved service";
            gaplessCtrl = qobject_cast<QMediaGaplessPlaybackControl *>(
                service->requestControl("org.qt-project.qt.mediaplayercontrol/5.0"));
            if (gaplessCtrl != NULL) {
                qDebug() << "      Retrieved QMediaGaplessPlaybackControl";
                service->releaseControl(gaplessCtrl);
                gaplessCtrl->setCrossfadeTime(5000);
                qDebug() << "      Released QMediaGaplessPlaybackControl";
            }
            else {
                qDebug() << "      QMediaGaplessPlaybackControl is null!";
            }
        }
        else {
            qDebug() << "   Service is null!";
        }
    }
    else {
        qDebug() << "Player not available:" << mediaplayer->availability();
    }
    */
}


void LoopingPlayer::play()
{
    qDebug() << "LoopingPlayer::play";
    this->playingClicked = true;
    mediaplayer->play();
}


void LoopingPlayer::pause()
{
    qDebug() << "LoopingPlayer::pause";
    this->playingClicked = false;
    mediaplayer->pause();
}


void LoopingPlayer::setTrack(const QString &s, bool loop) {
    if (s.isEmpty()) {
        mediaplayer->pause();
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
