#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QSoundEffect>

class MusicPlayer
{
public:
    MusicPlayer();
    ~MusicPlayer();
    QSoundEffect* sound = nullptr;
    void play(QString address = "",bool repeat = 1);
    void stop();
    void setVolumeProportion(float v);//设置音量比例，0-1
};

#endif // MUSICPLAYER_H
