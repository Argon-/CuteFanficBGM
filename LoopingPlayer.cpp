#include "LoopingPlayer.h"
#include <QDebug>
#include <QTextStream>


LoopingPlayer::LoopingPlayer() : 
    audioConnected(false)
{
    qDebug() << "Created Player";
}


void LoopingPlayer::setUpAudioChain()
{
    mediaObject = new Phonon::MediaObject();
    mediaObject->setTransitionTime(500);
    audioOutput = new Phonon::AudioOutput(Phonon::NotificationCategory);
    audioPath = Phonon::createPath(mediaObject, audioOutput);
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish_cb()));
    audioConnected = audioPath.isValid();
}


bool LoopingPlayer::testSetAudioChain()
{
    if (!audioConnected) {
        this->setUpAudioChain();

        if (audioConnected) {
            QTextStream(stdout) << "Initialized audio chain";
            qDebug() << "Capabilities:";
            qDebug() << Phonon::BackendCapabilities::availableAudioOutputDevices();
            qDebug() << Phonon::BackendCapabilities::availableMimeTypes();
        }
        else {
            QTextStream(stdout) << "Initializing audio chain failed";
        }
    }
    return audioConnected;
}


void LoopingPlayer::play(const Phonon::MediaSource &cms)
{
    this->setCurrentTrack(cms);
    this->play();
}


void LoopingPlayer::play()
{
    qDebug() << "LoopingPlayer::play";
    if (!this->testSetAudioChain()) {
        return;
    }
    mediaObject->play();
}


void LoopingPlayer::enqueue(const Phonon::MediaSource &cms)
{
    this->currentSource = cms;
    this->enqueue();
}


void LoopingPlayer::enqueue()
{
    if (!this->testSetAudioChain()) {
        return;
    }
    mediaObject->enqueue(this->currentSource);
}


void LoopingPlayer::pause()
{
    qDebug() << "LoopingPlayer::pause";
    if (!this->testSetAudioChain()) {
        return;
    }
    mediaObject->pause();
}


void LoopingPlayer::aboutToFinish_cb()
{
    this->enqueue();
}


void LoopingPlayer::setInternalTrack(const Phonon::MediaSource &cms) {
    this->currentSource = cms;
}


void LoopingPlayer::setCurrentTrack(const Phonon::MediaSource &cms) {
    this->currentSource = cms;
    mediaObject->setCurrentSource(this->currentSource);
}


void LoopingPlayer::setVolume(float n)
{
    if (!this->testSetAudioChain()) {
        return;
    }
    audioOutput->setVolume(n);
}


void LoopingPlayer::togglePlaying()
{
    if (this->isPlaying()) {
        this->pause();
    }
    this->play();
}


void LoopingPlayer::togglePlaying(const Phonon::MediaSource &cms)
{
    this->setCurrentTrack(cms);
    this->togglePlaying();
}


LoopingPlayer::~LoopingPlayer()
{
    delete mediaObject;
}


bool LoopingPlayer::isPlaying()
{
    return audioConnected && mediaObject->state() == Phonon::PlayingState;
}


bool LoopingPlayer::isPaused()
{
    return audioConnected && mediaObject->state() == Phonon::PausedState;
}


bool LoopingPlayer::isStopped()
{
    return audioConnected && mediaObject->state() == Phonon::StoppedState;
}


bool LoopingPlayer::isLoadingOrBuffering()
{
    return audioConnected && (mediaObject->state() == Phonon::LoadingState || mediaObject->state() == Phonon::BufferingState);
}


bool LoopingPlayer::isFaulty()
{
    return audioConnected && mediaObject->state() == Phonon::ErrorState;
}
