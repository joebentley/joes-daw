#include "AudioCallback.h"

void AudioCallback::audioDeviceIOCallbackWithContext(const float *const *, int,
                                                     float *const *outputChannelData, int numOutputChannels,
                                                     int numSamples,
                                                     const juce::AudioIODeviceCallbackContext &) {
    jassert(numOutputChannels == 2);


    for (int channel = 0; channel < 2; channel++) {
        float *outputChannel = outputChannelData[channel];
        for (int i = 0; i < numSamples; i++) {
            double t = getTime(i);
            outputChannel[i] = static_cast<float>(0.2 * sin(1000.f * t));
        }
    }

    m_samples += static_cast<uint64_t>(numSamples);
}

void AudioCallback::audioDeviceAboutToStart(juce::AudioIODevice *device) {
    m_sampleRate = device->getCurrentSampleRate();
}

void AudioCallback::audioDeviceStopped() {
}

double AudioCallback::getTime(int samplesOffset) {
    return static_cast<double>(m_samples + static_cast<uint64_t>(samplesOffset)) / m_sampleRate;
}
