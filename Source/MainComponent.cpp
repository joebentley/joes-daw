#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent() {
    addAndMakeVisible(m_showAudioDeviceSelectorWindowButton);
    m_showAudioDeviceSelectorWindowButton.addListener(this);

    m_audioDeviceManager.initialiseWithDefaultDevices(0, 2);
    m_audioDeviceManager.addAudioCallback(&m_audioCallback);

    for (int i = 0; i < 4; ++i) {
        addAndMakeVisible(m_trackComponents[i]);
        m_audioCallback.setTrack(m_trackComponents[i].track(), i);
    }

    setSize(870, 600);
}

MainComponent::~MainComponent() {
    if (m_audioDeviceSelectorWindow != nullptr)
        delete m_audioDeviceSelectorWindow;

    m_audioDeviceManager.removeAudioCallback(&m_audioCallback);
}

//==============================================================================
void MainComponent::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::grey);

    for (int i = 0; i < 4; ++i) {
        const float x = static_cast<float>(i * 220 - 5);
        g.drawLine(x, 30, x, static_cast<float>(getHeight() - 40), 2);
    }
}

void MainComponent::resized() {
    m_showAudioDeviceSelectorWindowButton.setBounds(getWidth() - 110, getHeight() - 35, 100, 25);

    for (int i = 0; i < 4; ++i) {
        m_trackComponents[i].setBounds(i * 220, 0, 200, 800);
    }
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
