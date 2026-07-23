#include "TimelineComponent.h"

TimelineComponent::TimelineComponent(Settings::Timeline &settings) : m_settings(settings) {
    addAndMakeVisible(m_timelineEditor);
}

void TimelineComponent::resized() {
    m_timelineEditor.setBounds(20, 20, 150, 20);
}
