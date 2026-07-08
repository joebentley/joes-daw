#pragma once

#include "Sequencer.h"
#include "DeviceContainerComponent.h"


class SequencerComponent : public juce::Component {
public:
    virtual Sequencer *sequencer() = 0;
};
