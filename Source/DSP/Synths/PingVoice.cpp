#include "PingVoice.h"

float PingVoice::nextSample(const double t) {
    if (m_enabled) {
        const double volume = getVolume(t);

        if (volume <= 0.001)
            setEnabled(false);

        const double frequency =
                juce::MidiMessage::getMidiNoteInHertz(static_cast<int>(round(m_currentEvent.midiNote)));
        return static_cast<float>(volume * sin(juce::MathConstants<double>::twoPi * frequency * t));
    }
    return 0;
}

double PingVoice::getVolume(const double t) const {
    return exp(-(t - m_currentEvent.time) * m_decayRate);
}
