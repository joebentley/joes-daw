#pragma once

#include "../Synth.h"

class PingSynth : public Synth {
public:
    [[nodiscard]] double decayRate() const {
        return m_decayRate;
    }

    void setDecayRate(double decayRate) {
        m_decayRate = decayRate;
    }

    [[nodiscard]] double frequency() const {
        return m_frequency;
    }

    void setFrequency(double frequency) {
        m_frequency = frequency;
    }

    void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                         juce::AudioBuffer<float> &toFill) override;

private:
    [[nodiscard]] double getVolume(double t) const;

    double m_lastEventTime = 0.0;
    double m_decayRate = 10.0;
    double m_frequency = 1000.0;
};
