#include "RepeatingSequencer.h"

RepeatingSequencer::RepeatingSequencer(const double rate, const double note) : m_rate(rate), m_note(note) {
}

juce::Array<Event> RepeatingSequencer::generateEventsForTimes(double startTime, double endTime) {
    juce::Array<Event> events;

    if (m_lastEvent < 0.0) {
        m_lastEvent = startTime;
        events.add(Event{startTime});
        return events;
    }

    const double period = 1.0 / m_rate;
    jassert(endTime - startTime < period);

    double nextEvent = m_lastEvent + period;
    if (startTime <= nextEvent && nextEvent <= endTime) {
        m_lastEvent = nextEvent;
        events.add(Event{nextEvent, m_note});
        return events;
    }

    return events;
}
