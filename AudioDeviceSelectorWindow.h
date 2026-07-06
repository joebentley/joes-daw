#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>

class AudioDeviceSelectorWindow : public juce::DocumentWindow {
public:
    AudioDeviceSelectorWindow(juce::Colour backgroundColour, juce::AudioDeviceManager &audioDeviceManager);

    void closeButtonPressed() override;
};
