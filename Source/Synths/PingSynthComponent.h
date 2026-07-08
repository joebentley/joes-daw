#pragma once

#include "PingSynth.h"
#include "../SynthComponent.h"

class PingSynthComponent : public SynthComponent, public juce::Slider::Listener {
public:
    PingSynthComponent();

    void resized() override;

    Synth *synth() override { return &m_synth; }

    void sliderValueChanged(juce::Slider *) override;

private:
    PingSynth m_synth;

    juce::Slider m_decaySlider;
};
