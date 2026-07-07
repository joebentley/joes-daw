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

private:
    Sequencer *m_sequencer = nullptr;
    Synth *m_synth = nullptr;
};
