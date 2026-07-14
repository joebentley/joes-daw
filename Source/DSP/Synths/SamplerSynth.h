#pragma once
#include "../Synth.h"

#include <juce_audio_formats/juce_audio_formats.h>

class SamplerSynth : public Synth {
public:
    SamplerSynth();

    void renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                         juce::AudioBuffer<float> &toFill) override;

    void setFile(const juce::File &file);

private:
    juce::AudioFormatManager m_audioFormatManager;
    juce::File m_sampleFile;
    juce::File m_queuedSampleFile;
    juce::AudioBuffer<float> m_sampleBuffer;

    double m_samplePointer = 0.0;
    double m_samplePlaybackRate = 1.0;

    void loadSampleFile();

    double m_lastEventTime = 0.0;
    double m_decayRate = 10.0;

    static double rateFromMidiNote(double midiNote);
};

