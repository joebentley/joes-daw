#pragma once

#include "../Sequencer.h"

class RepeatingSequencer : public Sequencer {
public:
    explicit RepeatingSequencer(double rate = 1.0);

    juce::Array<Event> generateEventsForTimes(double startTime, double endTime) override;

    [[nodiscard]] double rate() const {
        return m_rate;
    }

    void setRate(double rate) {
        m_rate = rate;
        m_lastEvent = -1.0;
    }

private:
    double m_lastEvent = -1.0;
    double m_rate;
};
