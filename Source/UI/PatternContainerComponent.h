#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "PatternComponent.h"
#include "../DSP/AudioCallback.h"
#include "../DSP/Timeline.h"

class PatternContainerComponent : public juce::Component, public juce::Button::Listener, public juce::Slider::Listener,
                                  AudioCallback::Listener {
public:
    PatternContainerComponent(Timeline &timeline, AudioCallback &audioCallback);

    void resized() override;

    void buttonClicked(juce::Button *) override;

    void sliderValueChanged(juce::Slider *) override;

    void patternChanged(int newPatternIndex) override;

private:
    juce::Slider m_chosenPatternSlider;
    juce::TextButton m_newPatternButton;
    juce::TextButton m_clearPatternButton;

    Timeline &m_timeline;
    AudioCallback &m_audioCallback;
    std::unique_ptr<PatternComponent> m_patternComponent;

    void switchPattern(int patternID);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatternContainerComponent)
};

