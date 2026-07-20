#pragma once

#include "../Synth.h"

class PingSynth : public Synth {
public:
    PingSynth();

    [[nodiscard]] double decayRate() const {
        return m_decayRate;
    }

    void setDecayRate(double decayRate);

private:
    double m_decayRate = 10.0;
};
