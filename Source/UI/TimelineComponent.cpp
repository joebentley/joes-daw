#include "TimelineComponent.h"

#include "../SettingsSingleton.h"

TimelineComponent::TimelineComponent(Settings::Timeline &settings) : m_settings(settings) {
    addAndMakeVisible(m_timelineEditor);

    juce::String text = "";
    for (auto i: settings.patternTimeline) {
        text += i;
        text += ",";
    }

    text = text.dropLastCharacters(1);

    m_timelineEditor.setText(text);
    m_timelineEditor.addListener(this);
}

void TimelineComponent::resized() {
    m_timelineEditor.setBounds(20, 20, 150, 20);
}

void TimelineComponent::textEditorTextChanged(juce::TextEditor &textEditor) {
    juce::StringArray stringArray;
    stringArray.addTokens(textEditor.getText(), ",", "");

    m_settings.patternTimeline.clear();
    for (auto patternID: stringArray) {
        m_settings.patternTimeline.push_back(patternID.getIntValue());
    }

    SettingsSingleton::getInstance()->save();
}
