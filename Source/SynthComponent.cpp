#include "SynthComponent.h"

SynthComponent::SynthComponent() {
    m_deviceTypeComboBox.addItem("PingSynth", 1);
    m_deviceTypeComboBox.setSelectedId(1);
}
