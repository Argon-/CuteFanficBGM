#ifndef LOOPINGPLAYER_H
#define LOOPINGPLAYER_H

#include <Phonon/AudioOutput.h>
#include <Phonon/SeekSlider.h>
#include <Phonon/MediaObject.h>
#include <Phonon/VolumeSlider.h>
#include <Phonon/BackendCapabilities.h>
#include <Phonon/Effect.h>
#include <Phonon/EffectParameter.h>
#include <Phonon/ObjectDescriptionModel.h>
#include <QList>



class LoopingPlayer : public QObject
{
    Q_OBJECT

public:
    explicit LoopingPlayer();
    ~LoopingPlayer();

    bool isPlaying();
    bool isPaused();
    bool isStopped();
    bool isLoadingOrBuffering();
    bool isFaulty();
    void pause();
    void play(const Phonon::MediaSource &cms);
    void play();
    void togglePlaying();
    void togglePlaying(const Phonon::MediaSource &cms);
    void enqueue(const Phonon::MediaSource &cms);
    void enqueue();
    void setVolume(float n);
    void setUpAudioChain();
    bool testSetAudioChain();
    void setInternalTrack(const Phonon::MediaSource &cms);
    void setCurrentTrack(const Phonon::MediaSource &cms);

private:
    bool audioConnected;
    Phonon::MediaSource  currentSource;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    Phonon::Path         audioPath;

public slots:
    void aboutToFinish_cb();

};

#endif // LOOPINGPLAYER_H
