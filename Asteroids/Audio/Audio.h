#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include "WAV/WAV.h"

namespace Asteroids {
    class Audio {
    private:
        ALCdevice* device;
        ALCcontext* context;

    public:
        Audio(WAV wav);
        ~Audio();
        static void list_audio_devices();
    };
}

#endif