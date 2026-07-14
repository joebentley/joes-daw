#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <utility>

class ScrollingLabelComponent : public juce::Component, juce::Timer {
public:
    explicit ScrollingLabelComponent(juce::String initialText = "", bool bounceBackAndForth = false);

    void paint(juce::Graphics &g) override;

    void setText(const juce::String &text) {
        m_text = text;
    }

    void timerCallback() override;

private:
    juce::String m_text;

    bool m_bounceBackAndForth;

    int m_scroll = 0;
    int m_scrollDir = -1;
};
