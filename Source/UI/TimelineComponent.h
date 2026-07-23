#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../DSP/Timeline.h"

class TimelineComponent : public juce::Component {
public:
    explicit TimelineComponent(Settings::Timeline settings);

private:
    Settings::Timeline m_settings;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimelineComponent)
};
