#include "StepSequencer.h"

juce::Array<Event> StepSequencer::generateEventsForTimes(double startTime, double endTime) {
    auto clockEvents = m_repeatingSequencer.generateEventsForTimes(startTime, endTime);

    juce::Array<Event> events;

    for (auto [time, note]: clockEvents) {
        const auto currentNote = m_notes[m_current];

        if (currentNote > 0)
            events.add(Event(time, static_cast<double>(currentNote)));

        m_current++;
        if (m_current > 15)
            m_current = 0;
    }

    return events;
}

void StepSequencer::randomiseInRange(int low, int high) {
    juce::Random random;

    for (auto &note: m_notes) {
        note = static_cast<int>(round(random.nextFloat() * static_cast<float>(high - low) + static_cast<float>(low)));
    }
}
