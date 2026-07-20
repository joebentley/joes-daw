#include "PingSynth.h"
#include "PingVoice.h"

PingSynth::PingSynth() {
    for (int i = 0; i < 8; i++) {
        m_voices.push_back(std::make_unique<PingVoice>());
    }
}

void PingSynth::setDecayRate(double decayRate) {
    m_decayRate = decayRate;

    for (auto &v: m_voices) {
        dynamic_cast<PingVoice *>(v.get())->setDecayRate(m_decayRate);
    }
}
