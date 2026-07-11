#pragma once
#include "../Synth.h"


class DrumSampleSynth : public Synth {
public:
    void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                         juce::AudioBuffer<float> &toFill) override;
};
