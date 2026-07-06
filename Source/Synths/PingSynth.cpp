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
                m_lastEventTime = eventBuffer[nextEventIndexToProcess].time;
                nextEventIndexToProcess++;
            }
        }

        const double volume = getVolume(t);
        lChan[i] = static_cast<float>(volume * sin(1000.0 * t));
        rChan[i] = static_cast<float>(volume * sin(1000.0 * t));
    }
}

double PingSynth::getVolume(const double t) const {
    return exp(-(t - m_lastEventTime));
}
