#include "TrackComponent.h"

#include "SettingsSingleton.h"

TrackComponent::TrackComponent(Settings::Track &settings)
    : m_settings(settings),
      m_sequencerContainerComponent(m_track, settings.sequencer),
      m_synthContainerComponent(m_track, settings.synth) {
    addAndMakeVisible(m_enabledButton);
    m_enabledButton.addListener(this);
    m_enabledButton.setToggleState(settings.enabled, juce::NotificationType::dontSendNotification);
    m_track.setEnabled(settings.enabled);

    addAndMakeVisible(m_sequencerContainerComponent);
    addAndMakeVisible(m_synthContainerComponent);

    m_sequencerContainerComponent.setListener(this);
    m_synthContainerComponent.setListener(this);
}

void TrackComponent::resized() {
    constexpr int padding = 10;
    constexpr int size = 200;

    m_enabledButton.setBounds(90, 20, 40, 40);

    m_sequencerContainerComponent.setBounds(padding, padding + 50, size - padding, size - padding);

    m_synthContainerComponent.setBounds(padding, 2 * padding + size + 50, size - padding, size - padding);
}

void TrackComponent::buttonClicked(juce::Button *button) {
    if (button == &m_enabledButton) {
        m_track.setEnabled(!m_track.enabled());
        m_settings.enabled = m_track.enabled();
        SettingsSingleton::getInstance()->save();
    }
}

void TrackComponent::sequencerChanged(Sequencer *sequencer) {
    m_track.setSequencer(sequencer);
}

void TrackComponent::synthChanged(Synth *synth) {
    m_track.setSynth(synth);
}
