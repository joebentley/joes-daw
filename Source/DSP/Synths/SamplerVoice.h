#pragma once
#include "../Voice.h"

#include <juce_audio_formats/juce_audio_formats.h>

class SamplerVoice : public Voice {
public:
    std::tuple<float, float> nextStereoSample(double time) override;

    void handleEvent(Event event) override;

    void setBuffer(juce::AudioBuffer<float> *sampleBuffer) { m_sampleBuffer = sampleBuffer; }

    void setRespondsToMidiNote(const int respondsToMidiNote) { m_respondsToMidiNote = respondsToMidiNote; }

private:
    juce::AudioBuffer<float> *m_sampleBuffer = nullptr;

    double m_samplePointer = 0.0;
    double m_samplePlaybackRate = 1.0;

    double m_decayRate = 10.0;

    int m_respondsToMidiNote = -1;

    static double rateFromMidiNote(double midiNote);
};
