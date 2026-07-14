#include "AudioCallback.h"

inline void protectYourEars(float *buffer, int sampleCount) {
    if (buffer == nullptr) { return; }
    bool firstWarning = true;
    for (int i = 0; i < sampleCount; ++i) {
        float x = buffer[i];
        bool silence = false;
        if (std::isnan(x)) {
            DBG("!!! WARNING: nan detected in audio buffer, silencing !!!");
            silence = true;
        } else if (std::isinf(x)) {
            DBG("!!! WARNING: inf detected in audio buffer, silencing !!!");
            silence = true;
        } else if (x < -2.0f || x > 2.0f) {
            // screaming feedback
            DBG("!!! WARNING: sample out of range, silencing !!!");
            silence = true;
        } else if (x < -1.0f) {
            if (firstWarning) {
                DBG("!!! WARNING: sample out of range, clamping !!!");
                firstWarning = false;
            }
            buffer[i] = -1.0f;
        } else if (x > 1.0f) {
            if (firstWarning) {
                DBG("!!! WARNING: sample out of range, clamping !!!");
                firstWarning = false;
            }
            buffer[i] = 1.0f;
        }
        if (silence) {
            memset(buffer, 0, sampleCount * sizeof(float));
            return;
        }
    }
}


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
    toFill.clear();

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
                if (m_tracks[i]->enabled()) {
                    mixed += tracks[i].getSample(channel, sample);
                }
            }
            mixed *= static_cast<float>(juce::Decibels::decibelsToGain(m_masterVolume));

            // Hard limiter. Won't protect against NaN, etc.
            if (mixed > 1.0) {
                mixed = 1.0;
            }

            toFill.setSample(channel, sample, mixed);
        }
    }

    const auto lchan = toFill.getWritePointer(0);
    const auto rchan = toFill.getWritePointer(1);

    protectYourEars(lchan, numSamples);
    protectYourEars(rchan, numSamples);

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

void AudioCallback::setMasterVolume(const double masterVolumeDb) {
    m_masterVolume = masterVolumeDb;
}

double AudioCallback::masterVolume() const {
    return m_masterVolume;
}
