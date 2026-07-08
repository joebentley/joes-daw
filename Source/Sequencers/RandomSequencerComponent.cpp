#include "RandomSequencerComponent.h"

RandomSequencerComponent::RandomSequencerComponent() {
    addAndMakeVisible(m_highSlider);
    m_highSlider.setRange(0.05, 10.0, 0.01);
    m_highSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_highSlider.setValue(m_sequencer.high());
    m_highSlider.addListener(this);

    addAndMakeVisible(m_lowSlider);
    m_lowSlider.setRange(0.05, 10.0, 0.01);
    m_lowSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_lowSlider.setValue(m_sequencer.low());
    m_lowSlider.addListener(this);
}

void RandomSequencerComponent::resized() {
    m_lowSlider.setBounds(10, 40, 180, 70);
    m_highSlider.setBounds(10, 100, 180, 70);

    SequencerComponent::resized();
}

void RandomSequencerComponent::sliderValueChanged(juce::Slider *) {
    auto high = std::max(m_lowSlider.getValue(), m_highSlider.getValue());
    auto low = std::min(m_lowSlider.getValue(), m_highSlider.getValue());

    m_sequencer.setHigh(high);
    m_sequencer.setLow(low);
}
