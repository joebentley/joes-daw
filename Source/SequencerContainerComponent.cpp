#include "SequencerContainerComponent.h"

#include "SettingsSingleton.h"
#include "Sequencers/RandomSequencerComponent.h"
#include "Sequencers/RepeatingSequencerComponent.h"


SequencerContainerComponent::SequencerContainerComponent(Track &trackToInitialise,
                                                         Settings::Sequencer &settings)
    : m_settings(settings),
      m_sequencerComponent(createInitialSequencerComponent()) {
    m_deviceTypeComboBox.addItem("RepeatingSequencer", 1);
    m_deviceTypeComboBox.addItem("RandomSequencer", 2);

    switch (settings.type) {
        case Settings::SequencerType::REPEATING_SEQUENCER:
            m_deviceTypeComboBox.setSelectedId(1);
            break;
        case Settings::SequencerType::RANDOM_SEQUENCER:
            m_deviceTypeComboBox.setSelectedId(2);
            break;
    }

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
        m_settings.type = Settings::SequencerType::REPEATING_SEQUENCER;
        m_settings.repeatingSequencer = Settings::RepeatingSequencer{.rate = 1.0, .note = 60.0};
        m_sequencerComponent = new RepeatingSequencerComponent(m_settings.repeatingSequencer);
    } else if (text == "RandomSequencer") {
        m_settings.type = Settings::SequencerType::RANDOM_SEQUENCER;
        m_settings.randomSequencer = Settings::RandomSequencer{
            .lowRate = 0.5, .highRate = 2.0, .lowNote = 40, .highNote = 80
        };
        m_sequencerComponent = new RandomSequencerComponent(m_settings.randomSequencer);
    }
    SettingsSingleton::getInstance()->save();

    addAndMakeVisible(m_sequencerComponent, 0);
    m_listener->sequencerChanged(m_sequencerComponent->sequencer());
    resized();
}

SequencerComponent *SequencerContainerComponent::createInitialSequencerComponent() const {
    switch (m_settings.type) {
        case Settings::SequencerType::REPEATING_SEQUENCER:
            return new RepeatingSequencerComponent(m_settings.repeatingSequencer);
        case Settings::SequencerType::RANDOM_SEQUENCER:
            return new RandomSequencerComponent(m_settings.randomSequencer);
    }
    jassertfalse;
    return nullptr;
}
