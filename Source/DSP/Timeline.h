#pragma once

#include "Clock.h"
#include <juce_audio_basics/juce_audio_basics.h>

#include "../Settings.h"
#include "Sequencers/RepeatingSequencer.h"

class Timeline {
public:
    explicit Timeline(Settings::Timeline &settings) : m_settings(settings) {
    }

    void renderNextBlock(Clock clock, const juce::AudioBuffer<float> &toFill);

    void addPatternToTimeline(int patternID) const;

    void setPattern(int patternID, Settings::Pattern &pattern) const;

    Settings::Pattern &currentPattern() const;

    void setPlayhead(int playhead);

    [[nodiscard]] int numPatterns() const;

    void newEmptyPattern() const;

    void clearPattern() const;

private:
    Settings::Timeline &m_settings;

    RepeatingSequencer m_repeatingSequencer{0.25};

    int m_playhead = 0;
};
