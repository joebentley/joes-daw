#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

#include "Clock.h"
#include "Sequencer.h"
#include "Synth.h"


class Track {
public:
    void renderNextBlock(Clock clock, juce::AudioBuffer<float> &toFill);

    void setSequencerOwned(Sequencer *sequencer);

    void setSynthOwned(Synth *synth);

    ~Track();

private:
    Sequencer *m_sequencer = nullptr;
    Synth *m_synth = nullptr;
};
