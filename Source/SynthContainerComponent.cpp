#include "SynthContainerComponent.h"

#include "Synths/NoiseSynthComponent.h"
#include "Synths/PingSynthComponent.h"

SynthContainerComponent::SynthContainerComponent(Track &trackToInitialise) : m_synthComponent(
    new PingSynthComponent()) {
    m_deviceTypeComboBox.addItem("PingSynth", 1);
    m_deviceTypeComboBox.addItem("NoiseSynth", 2);
    m_deviceTypeComboBox.setSelectedId(1);
    m_deviceTypeComboBox.addListener(this);

    addAndMakeVisible(m_synthComponent, 0);

    trackToInitialise.setSynth(m_synthComponent->synth());
}

SynthContainerComponent::~SynthContainerComponent() {
    delete m_synthComponent;
}

void SynthContainerComponent::resized() {
    m_synthComponent->setBounds(0, 0, 200, 200);
    DeviceContainerComponent::resized();
}

void SynthContainerComponent::setListener(Listener *listener) {
    m_listener = listener;
}

void SynthContainerComponent::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) {
    // combobox triggers this on setup, so we ignore it
    if (m_firstCall) {
        m_firstCall = false;
        return;
    }

    if (m_listener == nullptr)
        return;

    removeChildComponent(m_synthComponent);
    delete m_synthComponent;

    auto text = comboBoxThatHasChanged->getText();

    if (text == "PingSynth") {
        m_synthComponent = new PingSynthComponent();
    } else if (text == "NoiseSynth") {
        m_synthComponent = new NoiseSynthComponent();
    }

    addAndMakeVisible(m_synthComponent, 0);
    m_listener->synthChanged(m_synthComponent->synth());
    resized();
}
