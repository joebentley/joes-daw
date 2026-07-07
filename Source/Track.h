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

    [[nodiscard]] bool muted() const {
        return m_muted;
    }

    /// Note that tracks are still rendered even if muted, they are just added with gain zero
    void setMuted(bool muted) {
        m_muted = muted;
    }

private:
    Sequencer *m_sequencer = nullptr;
    Synth *m_synth = nullptr;

    bool m_muted = true;
};
