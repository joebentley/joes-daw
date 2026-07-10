#include "SynthContainerComponent.h"

#include "SettingsSingleton.h"
#include "Synths/NoiseSynthComponent.h"
#include "Synths/PingSynthComponent.h"

SynthContainerComponent::SynthContainerComponent(Track &trackToInitialise,
                                                 Settings::Synth &settings)
    : m_settings(settings), m_synthComponent(createInitialSynthComponent()) {
    m_deviceTypeComboBox.addItem("PingSynth", 1);
    m_deviceTypeComboBox.addItem("NoiseSynth", 2);

    switch (settings.type) {
        case Settings::SynthType::PING_SYNTH:
            m_deviceTypeComboBox.setSelectedId(1);
            break;
        case Settings::SynthType::NOISE_SYNTH:
            m_deviceTypeComboBox.setSelectedId(2);
            break;
    }

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
        m_settings.type = Settings::SynthType::PING_SYNTH;
        m_settings.pingSynth = Settings::PingSynth{10.0};
        m_synthComponent = new PingSynthComponent(m_settings.pingSynth);
    } else if (text == "NoiseSynth") {
        m_settings.type = Settings::SynthType::NOISE_SYNTH;
        m_settings.noiseSynth = Settings::NoiseSynth{10.0};
        m_synthComponent = new NoiseSynthComponent(m_settings.noiseSynth);
    }
    SettingsSingleton::getInstance()->save();

    addAndMakeVisible(m_synthComponent, 0);
    m_listener->synthChanged(m_synthComponent->synth());
    resized();
}

SynthComponent *SynthContainerComponent::createInitialSynthComponent() const {
    switch (m_settings.type) {
        case Settings::SynthType::PING_SYNTH:
            return new PingSynthComponent(m_settings.pingSynth);
        case Settings::SynthType::NOISE_SYNTH:
            return new NoiseSynthComponent(m_settings.noiseSynth);
    }
    jassertfalse;
    return nullptr;
}
