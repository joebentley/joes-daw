#include "NoiseSynthComponent.h"

NoiseSynthComponent::NoiseSynthComponent() {
    addAndMakeVisible(m_decayRateSlider);
    m_decayRateSlider.setRange(0.1, 30.0, 0.1);
    m_decayRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_decayRateSlider.setValue(m_synth.decayRate());
    m_decayRateSlider.addListener(this);
}

void NoiseSynthComponent::resized() {
    m_decayRateSlider.setBounds(10, 10, 180, 180);

    SynthComponent::resized();
}

void NoiseSynthComponent::sliderValueChanged(juce::Slider *slider) {
    m_synth.setDecayRate(slider->getValue());
}
