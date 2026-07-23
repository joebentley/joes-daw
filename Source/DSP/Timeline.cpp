#include "Timeline.h"

#include "../SettingsSingleton.h"

void Timeline::renderNextBlock(Clock clock, const juce::AudioBuffer<float> &toFill) {
    m_settings.patternMap.contains(m_settings.patternTimeline[static_cast<size_t>(m_playhead)]);

    auto clockEvents = m_repeatingSequencer.generateEventsForTimes(clock.getTime(),
                                                                   clock.getTime(toFill.getNumSamples()));
}

void Timeline::addPatternToTimeline(const int patternID) const {
    m_settings.patternTimeline.push_back(patternID);
    SettingsSingleton::getInstance()->save();
}

void Timeline::setPattern(const int patternID, Settings::Pattern &pattern) const {
    m_settings.patternMap[patternID] = pattern;
    SettingsSingleton::getInstance()->save();
}

Settings::Pattern &Timeline::currentPattern() const {
    return m_settings.patternMap[m_playhead];
}

void Timeline::setPlayhead(int playhead) {
    m_playhead = playhead;
}

int Timeline::numPatterns() const {
    return static_cast<int>(m_settings.patternMap.size());
}

void Timeline::duplicatePattern() const {
    m_settings.patternMap[numPatterns()] = m_settings.patternMap[numPatterns() - 1];
}

void Timeline::clearPattern() const {
    m_settings.patternMap[m_playhead] = Settings::Pattern::standard();
}
