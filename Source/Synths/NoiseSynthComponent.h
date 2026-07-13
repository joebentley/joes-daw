#pragma once

#include "NoiseSynth.h"
#include "../Settings.h"
#include "../SynthComponent.h"

class NoiseSynthComponent : public SynthComponent, public juce::Slider::Listener {
public:
    explicit NoiseSynthComponent(Settings::NoiseSynth &settings);

    void resized() override;

    Synth *synth() override { return &m_synth; }

    void sliderValueChanged(juce::Slider *) override;

private:
    Settings::NoiseSynth &m_settings;

    NoiseSynth m_synth;

    juce::Slider m_decayRateSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoiseSynthComponent)
};
