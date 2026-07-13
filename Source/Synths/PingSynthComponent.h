#pragma once

#include "PingSynth.h"
#include "../Settings.h"
#include "../SynthComponent.h"

class PingSynthComponent : public SynthComponent, public juce::Slider::Listener {
public:
    explicit PingSynthComponent(Settings::PingSynth &settings);

    void resized() override;

    Synth *synth() override { return &m_synth; }

    void sliderValueChanged(juce::Slider *) override;

private:
    Settings::PingSynth &m_settings;

    PingSynth m_synth;

    juce::Slider m_decaySlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PingSynthComponent)
};
