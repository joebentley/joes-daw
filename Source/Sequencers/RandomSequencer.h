#pragma once
#include "../Sequencer.h"


class RandomSequencer : public Sequencer {
public:
    explicit RandomSequencer(double low = 0.5, double high = 2.0);

    juce::Array<Event> generateEventsForTimes(double startTime, double endTime) override;

    [[nodiscard]] double low() const {
        return m_low;
    }

    void setLow(double low) {
        m_low = low;
        m_lastEvent = -1.0;
    }

    [[nodiscard]] double high() const {
        return m_high;
    }

    void setHigh(double high) {
        m_high = high;
        m_lastEvent = -1.0;
    }

private:
    double m_lastEvent = -1.0;
    double m_low;
    double m_high;
    double m_rate = 0.0;

    void generateRandomRate();

    juce::Random m_random;
};
