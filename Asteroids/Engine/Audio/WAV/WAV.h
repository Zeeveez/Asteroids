#ifndef WAV_H
#define WAV_H
#include <cstdint>
#include <variant>
#include <vector>

namespace Engine {
    class WAV {
    private:
        uint16_t audioFormat;   // 1 == PCM
        uint32_t byteRate;
        uint16_t blockAlign;    //  Bytes per sample across all channels
    public:
        uint16_t channels;
        uint32_t sampleRate;
        uint16_t bitsPerSample;
        uint32_t samples;
        std::vector<char> data8 = {};
        std::vector<int16_t> data16 = {};

        WAV(const char* file);
    };
}

#endif