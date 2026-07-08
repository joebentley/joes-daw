#pragma once

#include "RandomSequencer.h"
#include "../SequencerComponent.h"

class RandomSequencerComponent : public SequencerComponent, juce::Slider::Listener {
public:
    RandomSequencerComponent();

    void resized() override;

    Sequencer *sequencer() override { return &m_sequencer; }

    void sliderValueChanged(juce::Slider *) override;

private:
    RandomSequencer m_sequencer;

    juce::Slider m_lowSlider;
    juce::Slider m_highSlider;
};
