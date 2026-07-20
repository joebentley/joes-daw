#pragma once

#include "../Voice.h"

class PingVoice : public Voice {
public:
    float nextSample(double time) override;

    void setDecayRate(const double decayRate) {
        m_decayRate = decayRate;
    }

private:
    [[nodiscard]] double getVolume(double t) const;

    double m_decayRate = 10.0;
};
