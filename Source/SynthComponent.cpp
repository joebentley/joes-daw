#include "SynthComponent.h"

void SynthComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 2);
}
