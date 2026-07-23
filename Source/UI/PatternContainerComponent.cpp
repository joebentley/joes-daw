#include "PatternContainerComponent.h"

PatternContainerComponent::PatternContainerComponent(Timeline &timeline, AudioCallback &audioCallback)
    : m_timeline(timeline),
      m_audioCallback(audioCallback),
      m_patternComponent(std::make_unique<PatternComponent>(m_timeline.currentPattern())) {
    m_chosenPatternSlider.setSliderStyle(juce::Slider::IncDecButtons);
    m_chosenPatternSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    m_chosenPatternSlider.setRange(0, 16, 1);
    m_chosenPatternSlider.addListener(this);
    addAndMakeVisible(m_chosenPatternSlider);

    m_newPatternButton.setButtonText("new");
    m_newPatternButton.addListener(this);
    addAndMakeVisible(m_newPatternButton);

    m_clearPatternButton.setButtonText("clr");
    m_clearPatternButton.addListener(this);
    addAndMakeVisible(m_clearPatternButton);

    m_patternComponent->setAudioCallbackTracks(m_audioCallback);
    addAndMakeVisible(*m_patternComponent);
}

void PatternContainerComponent::resized() {
    constexpr int toolbarOffsetX = 4;
    constexpr int toolbarOffsetY = 4;

    m_chosenPatternSlider.setBounds(toolbarOffsetX, toolbarOffsetY, 90, 20);
    m_newPatternButton.setBounds(toolbarOffsetX + 95, toolbarOffsetY, 30, 20);
    m_clearPatternButton.setBounds(toolbarOffsetX + 95 + 35, toolbarOffsetY, 30, 20);

    m_patternComponent->setBounds(0, 20, getWidth(), getHeight() - 20);
}

void PatternContainerComponent::buttonClicked(juce::Button *button) {
    if (button == &m_newPatternButton) {
        m_timeline.duplicatePattern();
        const int newPatternIndex = m_timeline.numPatterns() - 1;
        m_chosenPatternSlider.setValue(newPatternIndex);
        switchPattern(newPatternIndex);
    } else if (button == &m_clearPatternButton) {
        m_timeline.clearPattern();
        switchPattern(static_cast<int>(m_chosenPatternSlider.getValue()));
    }
}

void PatternContainerComponent::sliderValueChanged(juce::Slider *slider) {
    if (slider == &m_chosenPatternSlider) {
        const int chosenPatternIndex = static_cast<int>(m_chosenPatternSlider.getValue());

        // Cap range of slider. We can't use setRange since it doesn't support a range with only one value allowed
        if (chosenPatternIndex > m_timeline.numPatterns() - 1)
            m_chosenPatternSlider.setValue(chosenPatternIndex - 1);
        else
            switchPattern(chosenPatternIndex);
    }
}

void PatternContainerComponent::switchPattern(int i) {
    m_timeline.setPlayhead(i);
    // We create the new one before removing the old one to prevent segfault in the audio thread
    auto newPatternComponent = std::make_unique<PatternComponent>(m_timeline.currentPattern());
    newPatternComponent->setAudioCallbackTracks(m_audioCallback);
    removeChildComponent(m_patternComponent.get());
    m_patternComponent = std::move(newPatternComponent);
    addAndMakeVisible(*m_patternComponent);
    resized();
}
