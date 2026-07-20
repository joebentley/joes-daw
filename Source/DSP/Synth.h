#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "Clock.h"
#include "Event.h"
#include "Voice.h"

// Abstract base class for synths
class Synth {
public:
    virtual ~Synth() = default;

    virtual void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                                 juce::AudioBuffer<float> &toFill);

    Voice *getFirstFreeVoice() const;

protected:
    std::vector<std::unique_ptr<Voice>> m_voices;
};
