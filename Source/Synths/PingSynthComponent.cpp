#include "PingSynthComponent.h"

PingSynthComponent::PingSynthComponent() {
    addAndMakeVisible(m_frequencySlider);
    m_frequencySlider.setRange(100, 10000, 1);
    m_frequencySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_frequencySlider.setValue(m_synth.frequency());
    m_frequencySlider.addListener(this);
}

void PingSynthComponent::resized() {
    m_frequencySlider.setBounds(10, 10, 180, 180);

    SynthComponent::resized();
}

void PingSynthComponent::sliderValueChanged(juce::Slider *slider) {
    m_synth.setFrequency(slider->getValue());
}
