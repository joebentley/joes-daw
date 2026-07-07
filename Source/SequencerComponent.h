#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Sequencer.h"

class SequencerComponent : public juce::Component {
public:
    virtual Sequencer *sequencer() = 0;

    void paint(juce::Graphics &g) override;
};
