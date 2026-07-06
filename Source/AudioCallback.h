#pragma once

#include <juce_audio_devices/juce_audio_devices.h>

class AudioCallback : public juce::AudioIODeviceCallback {
public:
    void audioDeviceIOCallbackWithContext(const float *const *inputChannelData, int numInputChannels,
                                          float *const *outputChannelData, int numOutputChannels, int numSamples,
                                          const juce::AudioIODeviceCallbackContext &context) override;

    void audioDeviceAboutToStart(juce::AudioIODevice *device) override;

    void audioDeviceStopped() override;

private:
    double getTime(int samplesOffset);

    uint64_t m_samples = 0;
    double m_sampleRate = 0.0;
};
