#include "SequencerComponent.h"

SequencerComponent::SequencerComponent() {
    m_deviceTypeComboBox.addItem("RepeatingSequencer", 1);
    m_deviceTypeComboBox.setSelectedId(1);
}
