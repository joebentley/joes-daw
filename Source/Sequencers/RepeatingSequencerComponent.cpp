#include "RepeatingSequencerComponent.h"

RepeatingSequencerComponent::RepeatingSequencerComponent() {
    addAndMakeVisible(m_rateSlider);
    m_rateSlider.setRange(0.05, 5.0, 0.01);
    m_rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_rateSlider.setValue(m_sequencer.rate());
    m_rateSlider.addListener(this);
}

void RepeatingSequencerComponent::resized() {
    m_rateSlider.setBounds(10, 10, 180, 180);
}

void RepeatingSequencerComponent::sliderValueChanged(juce::Slider *slider) {
    m_sequencer.setRate(slider->getValue());
}
