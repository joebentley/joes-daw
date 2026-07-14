#include "DeviceContainerComponent.h"

DeviceContainerComponent::DeviceContainerComponent() {
    addAndMakeVisible(m_deviceTypeComboBox);
}

void DeviceContainerComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 2);
}

void DeviceContainerComponent::resized() {
    m_deviceTypeComboBox.setBounds(140, 10, 40, 20);
}
