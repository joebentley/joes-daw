#include "MainComponent.h"

#include "../SettingsSingleton.h"


//==============================================================================
MainComponent::MainComponent(Settings::Settings &settings)
    : m_settings(settings),
      m_audioCallback(m_timeline),
      m_timeline(settings.timeline),
      m_timelineComponent(settings.timeline),
      m_patternContainerComponent(m_timeline, m_audioCallback) {
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

    addAndMakeVisible(m_mainTabbedComponent);
    m_mainTabbedComponent.addTab("timeline", getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
                                 &m_timelineComponent, false);
    m_mainTabbedComponent.addTab("pattern", getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
                                 &m_patternContainerComponent, false);

    addAndMakeVisible(m_songModeToggleButton);
    m_songModeToggleButton.setButtonText("song mode");
    m_songModeToggleButton.addListener(this);

    setSize(878, 600);
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
    m_mainTabbedComponent.setBounds(4, 4, getWidth() - 8, getHeight() - 44);

    m_volumeSlider.setBounds(0, getHeight() - 35, 200, 25);
    m_songModeToggleButton.setBounds(getWidth() / 2 - 30, getHeight() - 35, 100, 25);
    m_showAudioDeviceSelectorWindowButton.setBounds(getWidth() - 110, getHeight() - 35, 100, 25);
}

void MainComponent::buttonClicked(juce::Button *button) {
    if (button == &m_showAudioDeviceSelectorWindowButton) {
        m_audioDeviceSelectorWindow = new AudioDeviceSelectorWindow(
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), m_audioDeviceManager);
        m_audioDeviceSelectorWindow->addToDesktop();
        m_audioDeviceSelectorWindow->centreWithSize(500, 500);
        m_audioDeviceSelectorWindow->setVisible(true);
    } else if (button == &m_songModeToggleButton) {
        m_timeline.setPlaying(m_songModeToggleButton.getToggleState());
    }
}

void MainComponent::sliderValueChanged(juce::Slider *slider) {
    if (slider == &m_volumeSlider) {
        m_audioCallback.setMasterVolume(slider->getValue());
        m_settings.masterVolume = m_audioCallback.masterVolume();
        SettingsSingleton::getInstance()->save();
    }
}
