#include "RandomSequencer.h"

RandomSequencer::RandomSequencer(const double lowRate, const double highRate,
                                 const int lowNote, const int highNote) : m_lowRate(lowRate),
                                                                          m_highRate(highRate), m_lowNote(lowNote),
                                                                          m_highNote(highNote) {
    generateRandomRate();
    generateRandomNote();
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
        events.add(Event{nextEvent, static_cast<double>(m_note)});
        generateRandomRate();
        generateRandomNote();
        return events;
    }

    return events;
}

void RandomSequencer::generateRandomRate() {
    auto t = m_random.nextDouble();
    m_rate = t * (m_highRate - m_lowRate) + m_lowRate;
}

void RandomSequencer::generateRandomNote() {
    auto t = m_random.nextDouble();
    m_note = static_cast<int>(round(t * (m_highNote - m_lowNote))) + m_lowNote;
}
