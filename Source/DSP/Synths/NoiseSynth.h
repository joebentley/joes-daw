#pragma once

#include "../Synth.h"

class NoiseSynth : public Synth {
public:
    [[nodiscard]] double decayRate() const {
        return m_decayRate;
    }

    void setDecayRate(double decayRate) {
        m_decayRate = decayRate;
    }

    void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                         juce::AudioBuffer<float> &toFill) override;

private:
    [[nodiscard]] double getVolume(double t) const;

    double m_lastEventTime = 0.0;
    double m_decayRate = 10.0;

    juce::Random m_random;
};
