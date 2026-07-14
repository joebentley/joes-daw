#pragma once

#include "../DSP/Synth.h"
#include <juce_gui_basics/juce_gui_basics.h>

class SynthComponent : public juce::Component {
public:
    virtual Synth *synth() = 0;
};
