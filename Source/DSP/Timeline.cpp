#include "Timeline.h"

#include <juce_events/juce_events.h>

#include "../SettingsSingleton.h"

bool Timeline::shouldChangePattern(const Clock &clock, int numSamples) {
    if (!m_playing)
        return false;

    jassert(m_settings.patternMap.contains(m_settings.patternTimeline[static_cast<size_t>(getCurrentPatternID())]));

    const auto clockEvents = m_repeatingSequencer.generateEventsForTimes(clock.getTime(),
                                                                         clock.getTime(numSamples));

    return !clockEvents.isEmpty();
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
    return m_settings.patternMap[getCurrentPatternID()];
}

Settings::Pattern &Timeline::getPattern(int patternID) const {
    return m_settings.patternMap[patternID];
}

int Timeline::getCurrentPatternID() const {
    return m_settings.patternTimeline[static_cast<size_t>(m_playhead)];
}

int Timeline::numPatterns() const {
    return static_cast<int>(m_settings.patternMap.size());
}

void Timeline::duplicateCurrentPattern() const {
    m_settings.patternMap[numPatterns()] = m_settings.patternMap[numPatterns() - 1];
    SettingsSingleton::getInstance()->save();
}

void Timeline::clearCurrentPattern() const {
    m_settings.patternMap[getCurrentPatternID()] = Settings::Pattern::standard();
    SettingsSingleton::getInstance()->save();
}

void Timeline::setPlaying(const bool playing) {
    m_playing = playing;
}

void Timeline::incrementPlayhead() {
    m_playhead = (m_playhead + 1) % static_cast<int>(m_settings.patternTimeline.size());
}
