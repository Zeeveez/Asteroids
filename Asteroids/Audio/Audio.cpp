#include "audio.h"
#include <cstddef>
#include <cstdio>
#include <string.h>

namespace Asteroids {
    ALCdevice* Audio::device = nullptr;
    ALCcontext* Audio::context = nullptr;

    Audio::Audio(WAV wav) {
        if (!device && !context) {
            throw;
        }

        alGenSources((ALuint)1, &source);
        // check for errors
        alSourcef(source, AL_PITCH, 1);
        // check for errors
        alSourcef(source, AL_GAIN, 1);
        // check for errors
        alSource3f(source, AL_POSITION, 0, 0, 0);
        // check for errors
        alSource3f(source, AL_VELOCITY, 0, 0, 0);
        // check for errors
        alSourcei(source, AL_LOOPING, AL_FALSE);
        // check for errros

        alGenBuffers((ALuint)1, &buffer);
        // check for errors

        if (wav.bitsPerSample == 8) {
            alBufferData(buffer, AL_FORMAT_MONO8, &(wav.data[0]), wav.samples, wav.sampleRate);
        }else if (wav.bitsPerSample == 16) {
            alBufferData(buffer, AL_FORMAT_MONO16, &(wav.data[0]), wav.samples, wav.sampleRate);
        }

        alSourcei(source, AL_BUFFER, buffer);
        // check for errors
    }

    Audio::~Audio() {
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
    }

    void Audio::LoadDeviceAndContext() {
        device = alcOpenDevice(NULL);
        if (!device) {
            throw;
        }

        context = alcCreateContext(device, NULL);
        if (!alcMakeContextCurrent(context)) {
            throw;
        }
        if (alGetError() != AL_NO_ERROR) {
            throw;
        }
    }

    void Audio::UnloadDeviceAndContext() {
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    void Audio::Play() {
        alSourcePlay(source);
    }

    void Audio::Pause() {
        alSourcePause(source);
    }

    void Audio::Stop() {
        alSourceStop(source);
    }
}