#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "Clock.h"
#include "Event.h"

// Abstract base class for synths
class Synth {
public:
    virtual ~Synth() = default;

    virtual void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                                 juce::AudioBuffer<float> &toFill) = 0;
};
