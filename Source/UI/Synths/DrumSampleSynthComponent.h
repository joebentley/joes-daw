#pragma once
#include "SamplerSynthComponent.h"
#include "../SynthComponent.h"
#include "../../Settings.h"
#include "../../DSP/Synths/DrumSampleSynth.h"


class DrumSampleSynthComponent : public SynthComponent {
public:
    explicit DrumSampleSynthComponent(Settings::DrumSampleSynth &settings);

    void resized() override;

    Synth *synth() override { return &m_drumSampleSynth; }

private:
    SamplerSynthComponent m_samplerSynthComponent[4];

    DrumSampleSynth m_drumSampleSynth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumSampleSynthComponent)
};
