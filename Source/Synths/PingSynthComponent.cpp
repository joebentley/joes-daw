#include "PingSynthComponent.h"

PingSynthComponent::PingSynthComponent() {
    addAndMakeVisible(m_decaySlider);
    m_decaySlider.setRange(0.1, 30.0, 0.1);
    m_decaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_decaySlider.setValue(m_synth.decayRate());
    m_decaySlider.addListener(this);
}

void PingSynthComponent::resized() {
    m_decaySlider.setBounds(10, 10, 180, 180);

    SynthComponent::resized();
}

void PingSynthComponent::sliderValueChanged(juce::Slider *slider) {
    m_synth.setDecayRate(slider->getValue());
}
