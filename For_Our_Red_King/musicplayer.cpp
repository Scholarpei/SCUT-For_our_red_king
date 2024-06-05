#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{
    // this->sound = new QSoundEffect;
}

MusicPlayer::~MusicPlayer()
{
    delete this->sound;
}

void MusicPlayer::play(QString address,bool repeat)
{
    if(this->sound != nullptr)
        delete this->sound;
    this->sound = new QSoundEffect;
    this->sound->setSource(QUrl::fromLocalFile(address));
    this->sound->setVolume(0.8f);
    if(repeat)
        this->sound->setLoopCount(QSoundEffect::Infinite);
    else
        this->sound->setLoopCount(1);
    //设置循环播放次数
    this->sound->play();
}

void MusicPlayer::setVolumeProportion(float v)
{
    this->sound->setVolume(v);
}

void MusicPlayer::stop()
{
    if(this->sound != nullptr)
        this->sound->stop();
}
