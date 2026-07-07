#include "SequencerComponent.h"

void SequencerComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 2);
}
