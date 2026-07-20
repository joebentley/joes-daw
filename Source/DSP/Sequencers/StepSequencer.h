#pragma once
#include "RepeatingSequencer.h"
#include "../Sequencer.h"


class StepSequencer : public Sequencer {
public:
    juce::Array<Event> generateEventsForTimes(double startTime, double endTime) override;

    [[nodiscard]] std::vector<int> getStep(const int i) const {
        if (i >= 0 && i < 16)
            return m_notes[i];
        return {};
    }

    bool addNote(int step, int note);

    bool removeNote(int step, int note);

    [[nodiscard]] bool isNoteOn(int step, int note) const;

    [[nodiscard]] int current() const { return m_current; }

private:
    std::vector<int> m_notes[16] = {};
    int m_current = 0;

    RepeatingSequencer m_repeatingSequencer{8};
};
