#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Synth.h"

class SynthComponent : public juce::Component {
public:
    virtual Synth *synth() = 0;

    void paint(juce::Graphics &g) override;
};
