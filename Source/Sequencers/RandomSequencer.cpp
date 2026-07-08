#include "RandomSequencer.h"

RandomSequencer::RandomSequencer(const double low, const double high) : m_low(low), m_high(high) {
    generateRandomRate();
}

juce::Array<Event> RandomSequencer::generateEventsForTimes(double startTime, double endTime) {
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
        events.add(Event{nextEvent});
        generateRandomRate();
        return events;
    }

    return events;
}

void RandomSequencer::generateRandomRate() {
    auto t = m_random.nextDouble();
    m_rate = t * (m_high - m_low) + m_low;
}
