#include "WAV.h"
#include <fstream>
#include <iostream>

namespace Asteroids {
    WAV::WAV(const char* file) {
        std::ifstream f(file, std::ios::binary);


        // File header
        uint32_t chunkID;
        f.read(reinterpret_cast<char*>(&chunkID), sizeof(chunkID));
        std::cout << (chunkID == 0x46464952);    // "RIFF"

        uint32_t chunkSize;
        f.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));

        uint32_t format;
        f.read(reinterpret_cast<char*>(&format), sizeof(format));
        std::cout << (format == 0x45564157);    // "WAVE"


        // Sub-Chunk 1
        uint32_t subchunk1ID;
        f.read(reinterpret_cast<char*>(&subchunk1ID), sizeof(subchunk1ID));
        std::cout << (subchunk1ID == 0x20746d66);    // " fmt"

        uint32_t subchunk1Size;
        f.read(reinterpret_cast<char*>(&subchunk1Size), sizeof(subchunk1Size));

        f.read(reinterpret_cast<char*>(&audioFormat), sizeof(audioFormat));
        std::cout << (audioFormat == 1);    // PCM format
        f.read(reinterpret_cast<char*>(&channels), sizeof(channels));
        f.read(reinterpret_cast<char*>(&sampleRate), sizeof(sampleRate));
        f.read(reinterpret_cast<char*>(&byteRate), sizeof(byteRate));
        f.read(reinterpret_cast<char*>(&blockAlign), sizeof(blockAlign));
        f.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(bitsPerSample));
        std::cout << "\nFile details for " << file << ":\n"
            << "Audio Format:\t\t" << (audioFormat == 1 ? "PCM" : "Unknown") << "\n"
            << "Channels:\t\t" << channels << "\n"
            << "Sample Rate:\t\t" << sampleRate << "\n"
            << "Byte Rate:\t\t" << byteRate << "\n"
            << "Block Align:\t\t" << blockAlign << "\n"
            << "Bits Per Sample:\t" << bitsPerSample << "\n";


        // Sub-Chunk 2
        uint32_t subchunk2ID;
        f.read(reinterpret_cast<char*>(&subchunk2ID), sizeof(subchunk2ID));
        std::cout << (subchunk2ID == 0x61746164);    // "data"

        uint32_t subchunk2Size;
        f.read(reinterpret_cast<char*>(&subchunk2Size), sizeof(subchunk2Size));

        samples = subchunk2Size / channels / bitsPerSample * 8;

        //  Data
        data.reserve(samples);
        if (bitsPerSample == 8) {
            char dat;
            for (int i = 0; i < samples; i++) {
                f.read(reinterpret_cast<char*>(&dat), sizeof(char));
                data.push_back(dat);
            }
        } else if (bitsPerSample == 16) {
            int16_t dat;
            for (int i = 0; i < samples; i++) {
                f.read(reinterpret_cast<char*>(&dat), sizeof(int16_t));
                data.push_back(dat);
            }
        }
        f.close();
    }
}