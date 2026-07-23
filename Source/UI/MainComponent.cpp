#include "MainComponent.h"

#include "../SettingsSingleton.h"


//==============================================================================
MainComponent::MainComponent(Settings::Settings &settings)
    : m_settings(settings),
      m_timeline(settings.timeline),
      m_patternComponent(std::make_unique<PatternComponent>(m_timeline.currentPattern())) {
    addAndMakeVisible(m_volumeSlider);
    m_volumeSlider.setRange(-60, 0.0, 0.1);
    m_volumeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 30);
    m_volumeSlider.addListener(this);
    m_audioCallback.setMasterVolume(settings.masterVolume);
    m_volumeSlider.setValue(m_audioCallback.masterVolume());

    addAndMakeVisible(m_showAudioDeviceSelectorWindowButton);
    m_showAudioDeviceSelectorWindowButton.addListener(this);

    m_audioDeviceManager.initialiseWithDefaultDevices(0, 2);
    m_audioDeviceManager.addAudioCallback(&m_audioCallback);

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

    setSize(870, 600);
}

MainComponent::~MainComponent() {
    if (m_audioDeviceSelectorWindow != nullptr)
        delete m_audioDeviceSelectorWindow;

    m_audioDeviceManager.removeAudioCallback(&m_audioCallback);

    SettingsSingleton::getInstance()->clearSingletonInstance();
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    constexpr int toolbarOffsetX = 4;
    constexpr int toolbarOffsetY = 4;

    m_chosenPatternSlider.setBounds(toolbarOffsetX, toolbarOffsetY, 90, 20);
    m_newPatternButton.setBounds(toolbarOffsetX + 95, toolbarOffsetY, 30, 20);
    m_clearPatternButton.setBounds(toolbarOffsetX + 95 + 35, toolbarOffsetY, 30, 20);

    m_patternComponent->setBounds(0, 20, getWidth(), getHeight() - 20);

    m_volumeSlider.setBounds(0, getHeight() - 35, 200, 25);
    m_showAudioDeviceSelectorWindowButton.setBounds(getWidth() - 110, getHeight() - 35, 100, 25);
}

void MainComponent::buttonClicked(juce::Button *button) {
    if (button == &m_showAudioDeviceSelectorWindowButton) {
        m_audioDeviceSelectorWindow = new AudioDeviceSelectorWindow(
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), m_audioDeviceManager);
        m_audioDeviceSelectorWindow->addToDesktop();
        m_audioDeviceSelectorWindow->centreWithSize(500, 500);
        m_audioDeviceSelectorWindow->setVisible(true);
    } else if (button == &m_newPatternButton) {
        m_timeline.duplicatePattern();
        const int newPatternIndex = m_timeline.numPatterns() - 1;
        m_chosenPatternSlider.setValue(newPatternIndex);
        switchPattern(newPatternIndex);
    } else if (button == &m_clearPatternButton) {
        m_timeline.clearPattern();
        switchPattern(static_cast<int>(m_chosenPatternSlider.getValue()));
    }
}

void MainComponent::sliderValueChanged(juce::Slider *slider) {
    if (slider == &m_volumeSlider) {
        m_audioCallback.setMasterVolume(slider->getValue());
        m_settings.masterVolume = m_audioCallback.masterVolume();
        SettingsSingleton::getInstance()->save();
    } else if (slider == &m_chosenPatternSlider) {
        const int chosenPatternIndex = static_cast<int>(m_chosenPatternSlider.getValue());

        // Cap range of slider. We can't use setRange since it doesn't support a range with only one value allowed
        if (chosenPatternIndex > m_timeline.numPatterns() - 1)
            m_chosenPatternSlider.setValue(chosenPatternIndex - 1);
        else
            switchPattern(chosenPatternIndex);
    }
}

void MainComponent::switchPattern(const int i) {
    m_timeline.setPlayhead(i);
    auto newPatternComponent = std::make_unique<PatternComponent>(m_timeline.currentPattern());
    newPatternComponent->setAudioCallbackTracks(m_audioCallback);
    removeChildComponent(m_patternComponent.get());
    m_patternComponent = std::move(newPatternComponent);
    addAndMakeVisible(*m_patternComponent);
    resized();
}
