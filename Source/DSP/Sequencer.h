#pragma once

#include "juce_core/juce_core.h"
#include "Event.h"

// Abstract base class for sequencers
class Sequencer {
public:
    virtual ~Sequencer() = default;

    virtual juce::Array<Event> generateEventsForTimes(double startTime, double endTime) = 0;
};
