#pragma once

#include "../Sequencer.h"

/// Repeating sequencer that repeats events starting at time 0.0
/// This means that two repeating sequencers that have rates
/// that are multiples of each other will be synced
class RepeatingSequencer : public Sequencer {
public:
    explicit RepeatingSequencer(double rate = 1.0, double note = 60.0);

    juce::Array<Event> generateEventsForTimes(double startTime, double endTime) override;

    [[nodiscard]] double rate() const {
        return m_rate;
    }

    void setRate(double rate) {
        m_lastEvent = -1.0;
        m_rate = rate;
    }

    [[nodiscard]] double note() const {
        return m_note;
    }

    void setNote(double note) {
        m_note = note;
    }

private:
    double m_lastEvent = -1.0;
    double m_rate;
    double m_note;
};
