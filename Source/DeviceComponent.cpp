#include "DeviceComponent.h"

DeviceComponent::DeviceComponent() {
}

void DeviceComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 2);
}

void DeviceComponent::resized() {
    Component::resized();
}
