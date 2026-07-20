#include "SamplerSynth.h"

#include "SamplerVoice.h"

SamplerSynth::SamplerSynth() {
    m_audioFormatManager.registerBasicFormats();

    for (int i = 0; i < 16; ++i) {
        m_voices.push_back(std::make_unique<SamplerVoice>());
    }
}

void SamplerSynth::renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                                   juce::AudioBuffer<float> &toFill) {
    if (m_queuedSampleFile != m_sampleFile) {
        loadSampleFile();
    }

    if (m_sampleBuffer.getNumSamples() == 0) {
        toFill.clear();
        return;
    }

    Synth::renderNextBlock(clock, eventBuffer, toFill);
}

void SamplerSynth::setFile(const juce::File &file) {
    m_queuedSampleFile = file;
}

void SamplerSynth::setRespondsToMidiNote(const int respondsToMidiNote) const {
    for (auto &voice: m_voices) {
        dynamic_cast<SamplerVoice *>(voice.get())->setRespondsToMidiNote(respondsToMidiNote);
    }
}

void SamplerSynth::loadSampleFile() {
    m_sampleFile = m_queuedSampleFile;

    if (m_sampleFile.existsAsFile()) {
        const auto reader = m_audioFormatManager.createReaderFor(m_sampleFile);
        m_sampleBuffer.setSize(static_cast<int>(reader->numChannels), static_cast<int>(reader->lengthInSamples));
        reader->read(&m_sampleBuffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
        delete reader;
    }

    for (auto &voice: m_voices) {
        dynamic_cast<SamplerVoice *>(voice.get())->setBuffer(&m_sampleBuffer);
    }
}
