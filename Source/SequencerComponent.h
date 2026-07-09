#pragma once

#include "Sequencer.h"
#include <juce_gui_basics/juce_gui_basics.h>

class SequencerComponent : public juce::Component {
public:
    virtual Sequencer *sequencer() = 0;
};
