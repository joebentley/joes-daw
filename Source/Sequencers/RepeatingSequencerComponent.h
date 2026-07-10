#pragma once

#include "RepeatingSequencer.h"
#include "../SequencerComponent.h"
#include "../Settings.h"

class RepeatingSequencerComponent : public SequencerComponent, juce::Slider::Listener {
public:
    explicit RepeatingSequencerComponent(Settings::RepeatingSequencer &settings);

    void resized() override;

    Sequencer *sequencer() override { return &m_sequencer; }

    void sliderValueChanged(juce::Slider *) override;

private:
    Settings::RepeatingSequencer &m_settings;

    RepeatingSequencer m_sequencer;

    juce::Slider m_rateSlider;
    juce::Slider m_noteSlider;
};
