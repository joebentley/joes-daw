#pragma once
#include "../Sequencer.h"


class RandomSequencer : public Sequencer {
public:
    explicit RandomSequencer(double lowRate = 0.5, double highRate = 2.0, int lowNote = 40, int highNote = 80);

    juce::Array<Event> generateEventsForTimes(double startTime, double endTime) override;

    [[nodiscard]] double lowRate() const {
        return m_lowRate;
    }

    void setLowRate(double lowRate) {
        m_lowRate = lowRate;
    }

    [[nodiscard]] double highRate() const {
        return m_highRate;
    }

    void setHighRate(double highRate) {
        m_highRate = highRate;
    }

    [[nodiscard]] int lowNote() const {
        return m_lowNote;
    }

    void setLowNote(int lowNote) {
        m_lowNote = lowNote;
    }

    [[nodiscard]] int highNote() const {
        return m_highNote;
    }

    void setHighNote(int highNote) {
        m_highNote = highNote;
    }

private:
    double m_lastEvent = -1.0;

    double m_lowRate;
    double m_highRate;
    double m_rate = 0.0;

    int m_lowNote;
    int m_highNote;
    int m_note = 60;

    void generateRandomRate();

    void generateRandomNote();

    juce::Random m_random;
};
