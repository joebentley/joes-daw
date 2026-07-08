#include "SequencerContainerComponent.h"

#include "Sequencers/RandomSequencerComponent.h"
#include "Sequencers/RepeatingSequencerComponent.h"


SequencerContainerComponent::SequencerContainerComponent(Track &trackToInitialise) : m_sequencerComponent(
    new RepeatingSequencerComponent()) {
    m_deviceTypeComboBox.addItem("RepeatingSequencer", 1);
    m_deviceTypeComboBox.addItem("RandomSequencer", 2);
    m_deviceTypeComboBox.setSelectedId(1);
    m_deviceTypeComboBox.addListener(this);

    addAndMakeVisible(m_sequencerComponent, 0);

    trackToInitialise.setSequencer(m_sequencerComponent->sequencer());
}

SequencerContainerComponent::~SequencerContainerComponent() {
    delete m_sequencerComponent;
}

void SequencerContainerComponent::resized() {
    m_sequencerComponent->setBounds(0, 0, 200, 200);
    DeviceContainerComponent::resized();
}

void SequencerContainerComponent::setListener(Listener *listener) {
    m_listener = listener;
}

void SequencerContainerComponent::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) {
    // combobox triggers this on setup, so we ignore it
    if (m_firstCall) {
        m_firstCall = false;
        return;
    }

    if (m_listener == nullptr)
        return;

    removeChildComponent(m_sequencerComponent);
    delete m_sequencerComponent;

    auto text = comboBoxThatHasChanged->getText();

    if (text == "RepeatingSequencer") {
        m_sequencerComponent = new RepeatingSequencerComponent();
    } else if (text == "RandomSequencer") {
        m_sequencerComponent = new RandomSequencerComponent();
    }

    addAndMakeVisible(m_sequencerComponent);
    m_listener->sequencerChanged(m_sequencerComponent->sequencer());
    resized();
}
