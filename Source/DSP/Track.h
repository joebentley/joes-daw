#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

#include "Clock.h"
#include "Sequencer.h"
#include "Synth.h"


class Track {
public:
    void renderNextBlock(Clock clock, juce::AudioBuffer<float> &toFill) const;

    void setSequencer(Sequencer *sequencer);

    void setSynth(Synth *synth);

    [[nodiscard]] bool enabled() const {
        return m_enabled;
    }

    /// Note that tracks are still rendered even if not enabled, they are just added with gain zero
    void setEnabled(bool enabled) {
        m_enabled = enabled;
    }

private:
    Sequencer *m_sequencer = nullptr;
    Synth *m_synth = nullptr;

    bool m_enabled = true;
};
