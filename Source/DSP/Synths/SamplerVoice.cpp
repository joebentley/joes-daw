#include "SamplerVoice.h"

std::tuple<float, float> SamplerVoice::nextStereoSample(double time) {
    if (m_sampleBuffer == nullptr)
        return {0.0, 0.0};

    const float *lChanToSample = m_sampleBuffer->getReadPointer(0);
    const float *rChanToSample;
    if (m_sampleBuffer->getNumChannels() == 1) {
        rChanToSample = m_sampleBuffer->getReadPointer(0);
    } else {
        rChanToSample = m_sampleBuffer->getReadPointer(1);
    }

    // For looping reverse play
    if (m_samplePointer < 0.0) {
        m_samplePointer = m_sampleBuffer->getNumSamples();
    }

    if (m_samplePointer > m_sampleBuffer->getNumSamples()) {
        setEnabled(false);
        return {0.0, 0.0};
    } else {
        auto sample = std::make_tuple(
            lChanToSample[static_cast<int>(round(m_samplePointer))],
            rChanToSample[static_cast<int>(round(m_samplePointer))]
        );

        m_samplePointer += m_samplePlaybackRate;

        return sample;
    }
}

void SamplerVoice::handleEvent(const Event event) {
    Voice::handleEvent(event);
    m_samplePointer = 0;
    m_samplePlaybackRate = rateFromMidiNote(event.midiNote);
}

double SamplerVoice::rateFromMidiNote(double midiNote) {
    constexpr double scale = 10.0;

    // rate 1.0 is MIDI note C = 60
    return (midiNote - 60.0) / scale + 1.0;
}
