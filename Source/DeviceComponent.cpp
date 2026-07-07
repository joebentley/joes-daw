#include "DeviceComponent.h"

DeviceComponent::DeviceComponent() {
    addAndMakeVisible(m_deviceTypeComboBox);
}

void DeviceComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 2);
}

void DeviceComponent::resized() {
    m_deviceTypeComboBox.setBounds(140, 10, 40, 20);
}
