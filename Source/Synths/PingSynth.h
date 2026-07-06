#pragma once

#include "../Synth.h"

class PingSynth : public Synth {
public:
    void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                         juce::AudioBuffer<float> &toFill) override;

private:
    [[nodiscard]] double getVolume(double t) const;

    double m_lastEventTime = 0.0;
};
