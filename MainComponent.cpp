#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    setSize(600, 400);
    addAndMakeVisible(m_showAudioDeviceSelectorWindowButton);
    m_showAudioDeviceSelectorWindowButton.addListener(this);
}

MainComponent::~MainComponent() {
    if (m_audioDeviceSelectorWindow != nullptr)
        delete m_audioDeviceSelectorWindow;
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::FontOptions(16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized() {
    m_showAudioDeviceSelectorWindowButton.setBounds(300, 300, 100, 30);
}

void MainComponent::buttonClicked(juce::Button *button) {
    if (button == &m_showAudioDeviceSelectorWindowButton) {
        m_audioDeviceSelectorWindow = new AudioDeviceSelectorWindow(
            getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), m_audioDeviceManager);
        m_audioDeviceSelectorWindow->addToDesktop();
        m_audioDeviceSelectorWindow->centreWithSize(500, 500);
        m_audioDeviceSelectorWindow->setVisible(true);
    }
}
