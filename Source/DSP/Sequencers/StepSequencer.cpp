#include "StepSequencer.h"

juce::Array<Event> StepSequencer::generateEventsForTimes(double startTime, double endTime) {
    auto clockEvents = m_repeatingSequencer.generateEventsForTimes(startTime, endTime);

    juce::Array<Event> events;

    for (auto [time, _note]: clockEvents) {
        for (const auto currentNote: m_notes[m_current]) {
            if (currentNote > 0)
                events.add(Event(time, static_cast<double>(currentNote)));
        }

        m_current++;
        if (m_current > 15)
            m_current = 0;
    }

    return events;
}

bool StepSequencer::addNote(const int step, const int note) {
    if (step >= 0 && step < 16) {
        if (std::ranges::find(m_notes[step], note) != m_notes[step].end())
            return false;

        m_notes[step].push_back(note);

        return true;
    }
    return false;
}

bool StepSequencer::removeNote(const int step, const int note) {
    if (step >= 0 && step < 16) {
        if (const auto it = std::ranges::find(m_notes[step], note); it != m_notes[step].end()) {
            m_notes[step].erase(it);
            return true;
        }
        return false;
    }
    return false;
}
