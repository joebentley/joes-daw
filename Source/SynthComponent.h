#pragma once

#include "Synth.h"
#include "DeviceContainerComponent.h"

class SynthComponent : public juce::Component {
public:
    virtual Synth *synth() = 0;
};
