#pragma once

#include "RandomSequencer.h"
#include "../SequencerComponent.h"
#include "../Settings.h"

class RandomSequencerComponent : public SequencerComponent, juce::Slider::Listener {
public:
    explicit RandomSequencerComponent(Settings::RandomSequencer &settings);

    void resized() override;

    Sequencer *sequencer() override { return &m_sequencer; }

    void sliderValueChanged(juce::Slider *) override;

private:
    Settings::RandomSequencer &m_settings;

    RandomSequencer m_sequencer;

    juce::Slider m_lowRateSlider;
    juce::Slider m_highRateSlider;

    juce::Slider m_lowNoteSlider;
    juce::Slider m_highNoteSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RandomSequencerComponent)
};
