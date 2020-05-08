#include "audio.h"
#include <cstddef>
#include <cstdio>
#include <string.h>

namespace Asteroids {
    Audio::Audio(WAV wav) {
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


        ALuint source;
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

        ALuint buffer;
        alGenBuffers((ALuint)1, &buffer);
        // check for errors

        if (wav.bitsPerSample == 8) {
            alBufferData(buffer, AL_FORMAT_MONO8, &(wav.data[0]), wav.samples, wav.sampleRate);
        }else if (wav.bitsPerSample == 16) {
            alBufferData(buffer, AL_FORMAT_MONO16, &(wav.data[0]), wav.samples, wav.sampleRate);
        }

        alSourcei(source, AL_BUFFER, buffer);
        // check for errors




        alSourcePlay(source);
        //// check for errors
        //ALint source_state;
        //alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        //// check for errors
        //while (source_state == AL_PLAYING) {
        //    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        //    // check for errors
        //}


        //alDeleteSources(1, &source);
        //alDeleteBuffers(1, &buffer);
    }

    Audio::~Audio() {
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    void Audio::list_audio_devices() {
        const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
        const ALCchar* device = devices, * next = devices + 1;
        size_t len = 0;

        fprintf(stdout, "Devices list:\n");
        fprintf(stdout, "----------\n");
        while (device && *device != '\0' && next && *next != '\0') {
            fprintf(stdout, "%s\n", device);
            len = strlen(device);
            device += (len + 1);
            next += (len + 2);
        }
        fprintf(stdout, "----------\n");
    }
}