#include "MainComponent.h"

#include "Sequencers/RepeatingSequencerComponent.h"
#include "Synths/PingSynthComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    addAndMakeVisible(m_showAudioDeviceSelectorWindowButton);
    m_showAudioDeviceSelectorWindowButton.addListener(this);

    m_audioDeviceManager.initialiseWithDefaultDevices(0, 2);
    m_audioDeviceManager.addAudioCallback(&m_audioCallback);

    addAndMakeVisible(m_trackComponent);
    m_trackComponent.setSequencerComponentOwned(new RepeatingSequencerComponent());
    m_trackComponent.setSynthComponentOwned(new PingSynthComponent());
    m_audioCallback.setTrack(m_trackComponent.track());

    setSize(800, 800);
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

    g.setFont(juce::FontOptions(16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized() {
    m_showAudioDeviceSelectorWindowButton.setBounds(getWidth() - 110, getHeight() - 35, 100, 25);

    m_trackComponent.setBounds(0, 0, 400, 800);
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
