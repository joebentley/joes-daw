#pragma once

#include "Clock.h"
#include <juce_audio_devices/juce_audio_devices.h>

#include "Track.h"

class AudioCallback : public juce::AudioIODeviceCallback {
public:
    void audioDeviceIOCallbackWithContext(const float *const *inputChannelData, int numInputChannels,
                                          float *const *outputChannelData, int numOutputChannels, int numSamples,
                                          const juce::AudioIODeviceCallbackContext &context) override;

    void audioDeviceAboutToStart(juce::AudioIODevice *device) override;

    void audioDeviceStopped() override;

    void setTrack(Track *track);

private:
    Clock m_clock;

    Track *m_myTrack = nullptr;
};
