#include "RepeatingSequencerComponent.h"

#include "../../SettingsSingleton.h"

RepeatingSequencerComponent::RepeatingSequencerComponent(
    Settings::RepeatingSequencer &settings) : m_settings(settings) {
    m_sequencer.setRate(settings.rate);
    m_sequencer.setNote(settings.note);

    addAndMakeVisible(m_rateSlider);
    m_rateSlider.setRange(0.05, 10.0, 0.01);
    m_rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_rateSlider.setValue(m_sequencer.rate());
    m_rateSlider.addListener(this);

    addAndMakeVisible(m_noteSlider);
    m_noteSlider.setRange(0, 127, 1);
    m_noteSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_noteSlider.setValue(m_sequencer.note());
    m_noteSlider.addListener(this);
}

void RepeatingSequencerComponent::resized() {
    m_rateSlider.setBounds(10, 40, 180, 70);
    m_noteSlider.setBounds(10, 100, 180, 70);

    SequencerComponent::resized();
}

void RepeatingSequencerComponent::sliderValueChanged(juce::Slider *slider) {
    if (slider == &m_rateSlider) {
        m_sequencer.setRate(slider->getValue());
        m_settings.rate = slider->getValue();
        SettingsSingleton::getInstance()->save();
    } else if (slider == &m_noteSlider) {
        m_sequencer.setNote(slider->getValue());
        m_settings.note = slider->getValue();
        SettingsSingleton::getInstance()->save();
    }
}
