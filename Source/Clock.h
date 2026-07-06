#pragma once
#include <cstdint>

class AudioCallback;

class Clock {
public:
    [[nodiscard]] double getTime(int sampleOffset = 0) const;

private:
    double m_sampleRate = 0.0;
    uint64_t m_samples = 0;

    void addSampleCount(uint64_t samples);

    void setSampleRate(double sampleRate);

    friend AudioCallback;
};
