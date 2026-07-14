#include "ScrollingLabelComponent.h"


ScrollingLabelComponent::ScrollingLabelComponent(juce::String initialText, bool bounceBackAndForth)
    : m_text(std::move(initialText)), m_bounceBackAndForth(bounceBackAndForth) {
    startTimerHz(60);
}

void ScrollingLabelComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::greenyellow);
    g.drawSingleLineText(m_text, m_scroll, 20, juce::Justification::left);
}

void ScrollingLabelComponent::timerCallback() {
    if (m_text.isEmpty())
        return;

    m_scroll += m_scrollDir;

    const float textWidth = juce::TextLayout::getStringWidth(juce::AttributedString(m_text));
    const float scrollPos = abs(static_cast<float>(m_scroll));

    if (m_bounceBackAndForth && scrollPos > textWidth - static_cast<float>(getWidth()) + 5) {
        m_scrollDir *= -1;
    } else if (!m_bounceBackAndForth && scrollPos > textWidth) {
        m_scroll = getWidth();
    }

    repaint();
}
