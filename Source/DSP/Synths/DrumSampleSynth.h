#pragma once
#include "SamplerSynth.h"
#include "../Synth.h"


class DrumSampleSynth : public Synth {
public:
    void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                         juce::AudioBuffer<float> &toFill) override;

    void setSamplerSynth(Synth *samplerSynth, int i) {
        m_samplerSynth[i] = samplerSynth;
        dynamic_cast<SamplerSynth *>(samplerSynth)->setRespondsToMidiNote(i + 60);
    }

private:
    Synth *m_samplerSynth[4] = {nullptr};
};
