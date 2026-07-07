#pragma once

#include "Sequencer.h"
#include "DeviceComponent.h"


class SequencerComponent : public DeviceComponent {
public:
    SequencerComponent();

    virtual Sequencer *sequencer() = 0;
};
