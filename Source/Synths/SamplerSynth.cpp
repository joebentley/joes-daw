#include "SamplerSynth.h"

SamplerSynth::SamplerSynth() {
    m_audioFormatManager.registerBasicFormats();
}

void SamplerSynth::renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                                   juce::AudioBuffer<float> &toFill) {
    if (m_sampleBuffer.getNumSamples() == 0)
        return;

    const auto lChanToFill = toFill.getWritePointer(0);
    const auto rChanToFill = toFill.getWritePointer(1);
    const float *lChanToSample = m_sampleBuffer.getReadPointer(0);
    const float *rChanToSample;
    if (m_sampleBuffer.getNumChannels() == 1) {
        rChanToSample = m_sampleBuffer.getReadPointer(0);
    } else {
        rChanToSample = m_sampleBuffer.getReadPointer(1);
    }

    int nextEventIndexToProcess = 0;
    for (int i = 0; i < toFill.getNumSamples(); ++i) {
        const double t = clock.getTime(i);

        if (nextEventIndexToProcess < eventBuffer.size()) {
            if (t > eventBuffer[nextEventIndexToProcess].time) {
                m_samplePointer = 0;
                nextEventIndexToProcess++;
            }
        }

        if (m_samplePointer > m_sampleBuffer.getNumSamples()) {
            lChanToFill[i] = 0.0;
            rChanToFill[i] = 0.0;
        } else {
            lChanToFill[i] = lChanToSample[m_samplePointer];
            rChanToFill[i] = rChanToSample[m_samplePointer];
        }

        m_samplePointer++;
    }
}

void SamplerSynth::setFile(const juce::File &file) {
    m_sampleFile = file;

    if (file.existsAsFile()) {
        const auto reader = m_audioFormatManager.createReaderFor(m_sampleFile);
        m_samplePointer = 0;
        m_sampleBuffer.setSize(static_cast<int>(reader->numChannels), static_cast<int>(reader->lengthInSamples));
        reader->read(&m_sampleBuffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
        delete reader;
    }
}
