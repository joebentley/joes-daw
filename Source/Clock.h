#pragma once
#include "AudioCallback.h"


class Clock {
public:
    [[nodiscard]] double getTime(int sampleOffset = 0) const;

private:
    double m_sampleRate = 0.0;
    uint64_t m_samples = 0;

    void setSampleCount(uint64_t samples);

    void setSampleRate(double sampleRate);

    friend AudioCallback;
};
