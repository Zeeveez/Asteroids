#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>

namespace Asteroids {
    class Audio {
    private:
        ALCdevice* device;
        ALCcontext* context;

    public:
        Audio();
        ~Audio();
        static void list_audio_devices();
    };
}

#endif