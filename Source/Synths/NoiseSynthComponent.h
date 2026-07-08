#pragma once

#include "NoiseSynth.h"
#include "../SynthComponent.h"

class NoiseSynthComponent : public SynthComponent, public juce::Slider::Listener {
public:
    NoiseSynthComponent();

    void resized() override;

    Synth *synth() override { return &m_synth; }

    void sliderValueChanged(juce::Slider *) override;

private:
    NoiseSynth m_synth;

    juce::Slider m_decayRateSlider;
};
