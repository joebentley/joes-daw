#include "TrackComponent.h"

TrackComponent::TrackComponent() : m_sequencerContainerComponent(m_track), m_synthContainerComponent(m_track) {
    addAndMakeVisible(m_mutedButton);
    m_mutedButton.addListener(this);
    m_mutedButton.setToggleState(false, juce::NotificationType::dontSendNotification);

    addAndMakeVisible(m_sequencerContainerComponent);
    addAndMakeVisible(m_synthContainerComponent);

    m_sequencerContainerComponent.setListener(this);
    m_synthContainerComponent.setListener(this);
}

void TrackComponent::resized() {
    constexpr int padding = 10;
    constexpr int size = 200;

    m_mutedButton.setBounds(90, 20, 40, 40);

    m_sequencerContainerComponent.setBounds(padding, padding + 50, size - padding, size - padding);

    m_synthContainerComponent.setBounds(padding, 2 * padding + size + 50, size - padding, size - padding);
}

void TrackComponent::buttonClicked(juce::Button *button) {
    if (button == &m_mutedButton) {
        m_track.setMuted(!m_track.muted());
    }
}

void TrackComponent::sequencerChanged(Sequencer *sequencer) {
    m_track.setSequencer(sequencer);
}

void TrackComponent::synthChanged(Synth *synth) {
    m_track.setSynth(synth);
}
