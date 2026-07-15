#pragma once
#include "RepeatingSequencer.h"
#include "../Sequencer.h"


class StepSequencer : public Sequencer {
public:
    juce::Array<Event> generateEventsForTimes(double startTime, double endTime) override;

    [[nodiscard]] int getStep(const int i) const {
        if (i >= 0 && i < 16)
            return m_notes[i];
        return -1;
    }

    // Returns true if the step changed
    bool setStep(const int i, const int note) {
        if (i >= 0 && i < 16) {
            if (m_notes[i] == note)
                return false;

            m_notes[i] = note;
            return true;
        }
        return false;
    }

    [[nodiscard]] int current() const { return m_current; }

    void randomiseInRange(int low, int high);

private:
    int m_notes[16] = {};
    int m_current = 0;

    RepeatingSequencer m_repeatingSequencer{8};
};
