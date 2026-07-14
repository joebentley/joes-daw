#include "Clock.h"

double Clock::getTime(int sampleOffset) const {
    return static_cast<double>(m_samples + static_cast<uint64_t>(sampleOffset)) / m_sampleRate;
}

void Clock::addSampleCount(uint64_t samples) {
    m_samples += samples;
}

void Clock::setSampleRate(double sampleRate) {
    m_sampleRate = sampleRate;
}
