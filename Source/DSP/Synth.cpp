#include "Synth.h"

void Synth::renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                            juce::AudioBuffer<float> &toFill) {
    jassert(m_voices.size() > 0);

    int nextEventIndexToProcess = 0;

    const auto lChan = toFill.getWritePointer(0);
    const auto rChan = toFill.getWritePointer(1);

    for (int i = 0; i < toFill.getNumSamples(); ++i) {
        lChan[i] = 0;
        rChan[i] = 0;
    }

    for (int i = 0; i < toFill.getNumSamples(); ++i) {
        const double t = clock.getTime(i);

        if (nextEventIndexToProcess < eventBuffer.size()) {
            if (t > eventBuffer[nextEventIndexToProcess].time) {
                getFirstFreeVoice()->handleEvent(eventBuffer[nextEventIndexToProcess]);
                nextEventIndexToProcess++;
            }
        }

        for (const auto &v: m_voices) {
            if (v->enabled()) {
                const auto sample = v->nextStereoSample(t);
                lChan[i] += std::get<0>(sample);
                rChan[i] += std::get<1>(sample);
            }
        }
    }
}

Voice *Synth::getFirstFreeVoice() const {
    jassert(m_voices.size() > 0);

    for (const auto &v: m_voices) {
        if (!v->enabled())
            return v.get();
    }

    // Steal first voice
    Voice *stolenVoice = m_voices[0].get();
    stolenVoice->setEnabled(false);
    return stolenVoice;
}
