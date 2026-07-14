#include "AudioDeviceSelectorWindow.h"

#include <juce_audio_utils/gui/juce_AudioDeviceSelectorComponent.h>

AudioDeviceSelectorWindow::AudioDeviceSelectorWindow(juce::Colour backgroundColour,
                                                     juce::AudioDeviceManager &audioDeviceManager)
    : DocumentWindow("Audio settings", backgroundColour, closeButton, false) {
    setContentOwned(new juce::AudioDeviceSelectorComponent(audioDeviceManager, 0, 0, 2, 2, false, false, true, false),
                    true);
}

void AudioDeviceSelectorWindow::closeButtonPressed() {
    delete this;
}
