#include "TrackComponent.h"

TrackComponent::TrackComponent() {
    addAndMakeVisible(m_mutedButton);
    m_mutedButton.addListener(this);
    m_mutedButton.setToggleState(false, juce::NotificationType::dontSendNotification);
}

TrackComponent::~TrackComponent() {
    delete m_sequencerComponent;
    delete m_synthComponent;
}

void TrackComponent::resized() {
    constexpr int padding = 10;
    constexpr int size = 200;

    m_mutedButton.setBounds(90, 20, 40, 40);

    if (m_sequencerComponent != nullptr)
        m_sequencerComponent->setBounds(padding, padding + 50, size - padding, size - padding);

    if (m_synthComponent != nullptr)
        m_synthComponent->setBounds(padding, 2 * padding + size + 50, size - padding, size - padding);
}

void TrackComponent::buttonClicked(juce::Button *button) {
    if (button == &m_mutedButton) {
        m_track.setMuted(!m_track.muted());
    }
}

void TrackComponent::setSynthComponentOwned(SynthComponent *synthComponent) {
    if (m_synthComponent != nullptr) {
        removeChildComponent(m_synthComponent);
        delete m_synthComponent;
    }

    m_synthComponent = synthComponent;
    m_track.setSynth(m_synthComponent->synth());
    addAndMakeVisible(m_synthComponent);
    resized();
}

void TrackComponent::setSequencerComponentOwned(SequencerComponent *sequencerComponent) {
    if (m_sequencerComponent != nullptr) {
        removeChildComponent(m_sequencerComponent);
        delete m_sequencerComponent;
    }

    m_sequencerComponent = sequencerComponent;
    m_track.setSequencer(m_sequencerComponent->sequencer());
    addAndMakeVisible(m_sequencerComponent);
    resized();
}
