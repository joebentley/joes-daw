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

    void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                         juce::AudioBuffer<float> &toFill) override;

private:
    [[nodiscard]] double getVolume(double t) const;

    Event m_lastEvent;
    double m_decayRate = 10.0;
};
