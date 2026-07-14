#include "NoiseSynthComponent.h"

#include "../../SettingsSingleton.h"

NoiseSynthComponent::NoiseSynthComponent(Settings::NoiseSynth &settings) : m_settings(settings) {
    m_synth.setDecayRate(settings.decayRate);

    addAndMakeVisible(m_decayRateSlider);
    m_decayRateSlider.setRange(0.1, 30.0, 0.1);
    m_decayRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_decayRateSlider.setValue(m_synth.decayRate());
    m_decayRateSlider.addListener(this);
}

void NoiseSynthComponent::resized() {
    m_decayRateSlider.setBounds(10, 0, 180, 110);

    SynthComponent::resized();
}

void NoiseSynthComponent::sliderValueChanged(juce::Slider *slider) {
    m_synth.setDecayRate(slider->getValue());
    m_settings.decayRate = slider->getValue();
    SettingsSingleton::getInstance()->save();
}
