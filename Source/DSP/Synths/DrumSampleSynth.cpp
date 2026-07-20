#include "DrumSampleSynth.h"

void DrumSampleSynth::renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                                      juce::AudioBuffer<float> &toFill) {
    toFill.clear();

    for (const auto synth: m_samplerSynth) {
        if (synth != nullptr) {
            juce::AudioBuffer<float> toFillSingleVoice(2, toFill.getNumSamples());
            synth->renderNextBlock(clock, eventBuffer, toFillSingleVoice);

            toFill.addFrom(0, 0, toFillSingleVoice, 0, 0, toFillSingleVoice.getNumSamples());
            toFill.addFrom(1, 0, toFillSingleVoice, 1, 0, toFillSingleVoice.getNumSamples());
        }
    }
}
