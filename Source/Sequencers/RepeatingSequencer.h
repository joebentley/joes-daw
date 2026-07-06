#pragma once

#include "../Sequencer.h"

class RepeatingSequencer : public Sequencer {
public:
    explicit RepeatingSequencer(double rate = 1.0);

    juce::Array<Event> generateEventsForTimes(double startTime, double endTime) override;

private:
    double m_lastEvent = -1.0;
    double m_rate;
};
