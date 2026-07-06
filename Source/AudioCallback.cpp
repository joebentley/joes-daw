#include "AudioCallback.h"

#include "Sequencers/RepeatingSequencer.h"
#include "Synths/PingSynth.h"

AudioCallback::AudioCallback() {
    m_myTrack.setSequencerOwned(new RepeatingSequencer(2.0));
    m_myTrack.setSynthOwned(new PingSynth());
}

void AudioCallback::audioDeviceIOCallbackWithContext(const float *const *, int,
                                                     float *const *outputChannelData, int numOutputChannels,
                                                     int numSamples,
                                                     const juce::AudioIODeviceCallbackContext &) {
    jassert(numOutputChannels == 2);

    juce::AudioBuffer toFill(outputChannelData, numOutputChannels, numSamples);

    m_myTrack.renderNextBlock(m_clock, toFill);

    m_clock.addSampleCount(static_cast<uint64_t>(numSamples));
}

void AudioCallback::audioDeviceAboutToStart(juce::AudioIODevice *device) {
    m_clock.setSampleRate(device->getCurrentSampleRate());
}

void AudioCallback::audioDeviceStopped() {
}

