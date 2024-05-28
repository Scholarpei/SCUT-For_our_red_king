#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QSoundEffect>

class MusicPlayer
{
public:
    MusicPlayer();
    QSoundEffect* sound = nullptr;
    void play(QString address = "",bool repeat = 1);
    void stop();
};

#endif // MUSICPLAYER_H
