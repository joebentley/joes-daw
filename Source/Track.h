#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

#include "Clock.h"
#include "Sequencer.h"
#include "Synth.h"


class Track {
    void renderNextBlock(Clock clock, juce::AudioBuffer<float> &toFill);

private:
    Sequencer *m_sequencer = nullptr;
    Synth *m_synth = nullptr;
};
