#include "AudioCallback.h"


void AudioCallback::audioDeviceIOCallbackWithContext(const float *const *, int,
                                                     float *const *outputChannelData, int numOutputChannels,
                                                     int numSamples,
                                                     const juce::AudioIODeviceCallbackContext &) {
    jassert(numOutputChannels == 2);

    for (int i = 0; i < 4; ++i) {
        if (m_tracks[i] == nullptr)
            return;
    }

    juce::AudioBuffer toFill(outputChannelData, numOutputChannels, numSamples);

    juce::Array<juce::AudioBuffer<float> > tracks;

    for (int i = 0; i < 4; ++i) {
        juce::AudioBuffer<float> track(numOutputChannels, numSamples);
        m_tracks[i]->renderNextBlock(m_clock, track);
        tracks.add(track);
    }

    for (int channel = 0; channel < 2; ++channel) {
        for (int sample = 0; sample < numSamples; ++sample) {
            float mixed = 0.0;
            for (int i = 0; i < 4; ++i) {
                if (!m_tracks[i]->muted()) {
                    mixed += tracks[i].getSample(channel, sample);
                }
            }
            toFill.setSample(channel, sample, mixed);
        }
    }

    m_clock.addSampleCount(static_cast<uint64_t>(numSamples));
}

void AudioCallback::audioDeviceAboutToStart(juce::AudioIODevice *device) {
    m_clock.setSampleRate(device->getCurrentSampleRate());
}

void AudioCallback::audioDeviceStopped() {
}

void AudioCallback::setTrack(Track *track, int n) {
    m_tracks[n] = track;
}


