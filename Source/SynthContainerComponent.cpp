#include "SynthContainerComponent.h"

#include "SettingsSingleton.h"
#include "Synths/NoiseSynthComponent.h"
#include "Synths/PingSynthComponent.h"
#include "Synths/SamplerSynthComponent.h"

SynthContainerComponent::SynthContainerComponent(Track &trackToInitialise,
                                                 Settings::Synth &settings)
    : m_settings(settings), m_synthComponent(createInitialSynthComponent()) {
    m_deviceTypeComboBox.addItem("PingSynth", 1);
    m_deviceTypeComboBox.addItem("NoiseSynth", 2);
    m_deviceTypeComboBox.addItem("SamplerSynth", 3);

    switch (settings.type) {
        case Settings::SynthType::PING_SYNTH:
            m_deviceTypeComboBox.setSelectedId(1);
            break;
        case Settings::SynthType::NOISE_SYNTH:
            m_deviceTypeComboBox.setSelectedId(2);
            break;
        case Settings::SynthType::SAMPLER_SYNTH:
            m_deviceTypeComboBox.setSelectedId(3);
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

    const auto oldComponent = m_synthComponent;

    auto text = comboBoxThatHasChanged->getText();

    if (text == "PingSynth") {
        m_settings.type = Settings::SynthType::PING_SYNTH;
        auto settings = Settings::PingSynth{10.0};
        m_settings.settings = settings;
        m_synthComponent = new PingSynthComponent(settings);
    } else if (text == "NoiseSynth") {
        m_settings.type = Settings::SynthType::NOISE_SYNTH;
        auto settings = Settings::NoiseSynth{10.0};
        m_settings.settings = settings;
        m_synthComponent = new NoiseSynthComponent(settings);
    } else if (text == "SamplerSynth") {
        m_settings.type = Settings::SynthType::SAMPLER_SYNTH;
        auto settings = Settings::SamplerSynth{""};
        m_settings.settings = settings;
        m_synthComponent = new SamplerSynthComponent(settings);
    }
    SettingsSingleton::getInstance()->save();

    addAndMakeVisible(m_synthComponent, 0);
    m_listener->synthChanged(m_synthComponent->synth());

    // Wait until listeners have all been notified to change until deleting to
    // avoid race condition in AudioCallback. Proper solution is mutex
    delete oldComponent;
    resized();
}

SynthComponent *SynthContainerComponent::createInitialSynthComponent() const {
    switch (m_settings.type) {
        case Settings::SynthType::PING_SYNTH:
            return new PingSynthComponent(std::get<Settings::PingSynth>(m_settings.settings));
        case Settings::SynthType::NOISE_SYNTH:
            return new NoiseSynthComponent(std::get<Settings::NoiseSynth>(m_settings.settings));
        case Settings::SynthType::SAMPLER_SYNTH:
            return new SamplerSynthComponent(std::get<Settings::SamplerSynth>(m_settings.settings));
    }
    jassertfalse;
    return nullptr;
}
