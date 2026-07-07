#pragma once

#include "Synth.h"
#include "DeviceComponent.h"

class SynthComponent : public DeviceComponent {
public:
    SynthComponent();

    virtual Synth *synth() = 0;
};
