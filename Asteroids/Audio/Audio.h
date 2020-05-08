#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include "WAV/WAV.h"

namespace Asteroids {
    class Audio {
    private:
        static ALCdevice* device;
        static ALCcontext* context;
        ALuint source;
        ALuint buffer;

    public:
        static void LoadDeviceAndContext();
        static void UnloadDeviceAndContext();
        Audio(WAV wav);
        ~Audio();
        void Play();
        void Pause();
        void Stop();
    };
}

#endif