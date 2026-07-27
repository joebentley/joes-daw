#pragma once

#include "Clock.h"

#include "../Settings.h"
#include "Sequencers/RepeatingSequencer.h"

class Timeline {
public:
    explicit Timeline(Settings::Timeline &settings) : m_settings(settings) {
    }

    [[nodiscard]] bool shouldChangePattern(const Clock &clock, int numSamples);

    void addPatternToTimeline(int patternID) const;

    void setPattern(int patternID, Settings::Pattern &pattern) const;

    [[nodiscard]] Settings::Pattern &currentPattern() const;

    [[nodiscard]] Settings::Pattern &getPattern(int patternID) const;

    [[nodiscard]] int getCurrentPatternID() const;

    [[nodiscard]] int numPatterns() const;

    void duplicateCurrentPattern() const;

    void clearCurrentPattern() const;

    void setPlaying(bool playing);

    void incrementPlayhead();

private:
    Settings::Timeline &m_settings;

    RepeatingSequencer m_repeatingSequencer{0.5};

    bool m_playing = false;
    int m_playhead = 0;
};
