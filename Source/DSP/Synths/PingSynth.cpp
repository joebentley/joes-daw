#include "PingSynth.h"

void PingSynth::renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                                juce::AudioBuffer<float> &toFill) {
    int nextEventIndexToProcess = 0;

    auto lChan = toFill.getWritePointer(0);
    auto rChan = toFill.getWritePointer(1);

    for (int i = 0; i < toFill.getNumSamples(); i++) {
        const double t = clock.getTime(i);

        if (nextEventIndexToProcess < eventBuffer.size()) {
            if (t > eventBuffer[nextEventIndexToProcess].time) {
                m_lastEvent = eventBuffer[nextEventIndexToProcess];
                nextEventIndexToProcess++;
            }
        }

        const double volume = getVolume(t);
        const double frequency = juce::MidiMessage::getMidiNoteInHertz(static_cast<int>(round(m_lastEvent.midiNote)));
        const float sample = static_cast<float>(volume * sin(juce::MathConstants<double>::twoPi * frequency * t));
        lChan[i] = sample;
        rChan[i] = sample;
    }
}

double PingSynth::getVolume(const double t) const {
    return exp(-(t - m_lastEvent.time) * m_decayRate);
}
