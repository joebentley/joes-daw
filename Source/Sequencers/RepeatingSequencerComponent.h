#pragma once

#include "RepeatingSequencer.h"
#include "../SequencerComponent.h"

class RepeatingSequencerComponent : public SequencerComponent, juce::Slider::Listener {
public:
    RepeatingSequencerComponent();

    void resized() override;

    Sequencer *sequencer() override { return &m_sequencer; }

    void sliderValueChanged(juce::Slider *) override;

private:
    RepeatingSequencer m_sequencer;

    juce::Slider m_rateSlider;
    juce::Slider m_noteSlider;
};
