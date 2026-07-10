#include "RandomSequencerComponent.h"

#include "../SettingsSingleton.h"

RandomSequencerComponent::RandomSequencerComponent(Settings::RandomSequencer &settings) : m_settings(settings) {
    m_sequencer.setLowNote(settings.lowNote);
    m_sequencer.setHighNote(settings.highNote);
    m_sequencer.setLowRate(settings.lowRate);
    m_sequencer.setHighRate(settings.highRate);

    addAndMakeVisible(m_highRateSlider);
    m_highRateSlider.setRange(0.05, 10.0, 0.01);
    m_highRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_highRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    m_highRateSlider.setValue(m_sequencer.highRate());
    m_highRateSlider.addListener(this);

    addAndMakeVisible(m_lowRateSlider);
    m_lowRateSlider.setRange(0.05, 10.0, 0.01);
    m_lowRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_lowRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    m_lowRateSlider.setValue(m_sequencer.lowRate());
    m_lowRateSlider.addListener(this);

    addAndMakeVisible(m_highNoteSlider);
    m_highNoteSlider.setRange(0, 127, 1);
    m_highNoteSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_highNoteSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    m_highNoteSlider.setValue(m_sequencer.highNote());
    m_highNoteSlider.addListener(this);

    addAndMakeVisible(m_lowNoteSlider);
    m_lowNoteSlider.setRange(0, 127, 1);
    m_lowNoteSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_lowNoteSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    m_lowNoteSlider.setValue(m_sequencer.lowNote());
    m_lowNoteSlider.addListener(this);
}

void RandomSequencerComponent::resized() {
    m_lowRateSlider.setBounds(20, 30, 80, 75);
    m_highRateSlider.setBounds(100, 30, 80, 75);

    m_lowNoteSlider.setBounds(20, 105, 80, 75);
    m_highNoteSlider.setBounds(100, 105, 80, 75);

    SequencerComponent::resized();
}

void RandomSequencerComponent::sliderValueChanged(juce::Slider *slider) {
    if (slider == &m_lowRateSlider || slider == &m_highRateSlider) {
        auto high = std::max(m_lowRateSlider.getValue(), m_highRateSlider.getValue());
        auto low = std::min(m_lowRateSlider.getValue(), m_highRateSlider.getValue());

        m_sequencer.setHighRate(high);
        m_sequencer.setLowRate(low);
        m_settings.highRate = high;
        m_settings.lowRate = low;
        SettingsSingleton::getInstance()->save();
    }

    if (slider == &m_lowNoteSlider || slider == &m_highNoteSlider) {
        auto high = static_cast<int>(round(std::max(m_lowNoteSlider.getValue(), m_highNoteSlider.getValue())));
        auto low = static_cast<int>(round(std::min(m_lowNoteSlider.getValue(), m_highNoteSlider.getValue())));

        m_sequencer.setHighNote(high);
        m_sequencer.setLowNote(low);
        m_settings.highNote = high;
        m_settings.lowNote = low;
        SettingsSingleton::getInstance()->save();
    }
}
