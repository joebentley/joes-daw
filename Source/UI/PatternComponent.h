#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "TrackComponent.h"
#include "../Settings.h"

class PatternComponent : public juce::Component {
public:
    explicit PatternComponent(Settings::Pattern &settings);

    void paint(juce::Graphics &g) override;

    void resized() override;

    void setAudioCallbackTracks(AudioCallback &audioCallback);

private:
    Settings::Pattern &m_settings;

    TrackComponent m_trackComponents[4];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatternComponent)
};
