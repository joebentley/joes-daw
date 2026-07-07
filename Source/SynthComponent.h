#pragma once

#include "Synth.h"
#include "DeviceComponent.h"

class SynthComponent : public DeviceComponent {
public:
    virtual Synth *synth() = 0;
};
