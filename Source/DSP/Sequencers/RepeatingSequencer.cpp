#include "RepeatingSequencer.h"

RepeatingSequencer::RepeatingSequencer(const double rate, const double note) : m_rate(rate), m_note(note) {
}

juce::Array<Event> RepeatingSequencer::generateEventsForTimes(double startTime, double endTime) {
    juce::Array<Event> events;

    const double period = 1.0 / m_rate;
    jassert(endTime - startTime < period);

    if (m_lastEvent < 0.0) {
        while (m_lastEvent < startTime)
            m_lastEvent += period;

        events.add(Event{m_lastEvent, m_note});
        return events;
    }

    double nextEvent = m_lastEvent + period;
    if (startTime <= nextEvent && nextEvent <= endTime) {
        m_lastEvent = nextEvent;
        events.add(Event{nextEvent, m_note});
        return events;
    }

    // This can happen if we increase the rate slider too quickly
    if (nextEvent < startTime)
        m_lastEvent = -1.0;

    return events;
}
