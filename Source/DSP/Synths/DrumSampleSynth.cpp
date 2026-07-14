#include "DrumSampleSynth.h"

void DrumSampleSynth::renderNextBlock(const Clock &clock, const juce::Array<Event> &eventBuffer,
                                      juce::AudioBuffer<float> &toFill) {
    if (m_samplerSynth[m_chosenSample] == nullptr) {
        toFill.clear();
        return;
    }

    if (eventBuffer.size() > 0) {
        setChosenSampleFromMidiNote(static_cast<int>(eventBuffer[0].midiNote));
    }

    auto midiNoteFixedEvents = eventBuffer;

    for (auto &[time, midiNote]: midiNoteFixedEvents) {
        midiNote = 60.0;
    }

    m_samplerSynth[m_chosenSample]->renderNextBlock(clock, midiNoteFixedEvents, toFill);
}

void DrumSampleSynth::setChosenSampleFromMidiNote(int midiNote) {
    // sample 0 = middle C = 60

    m_chosenSample = midiNote - 60;
    if (m_chosenSample < 0)
        m_chosenSample = 0;
    if (m_chosenSample > 3)
        m_chosenSample = 3;
}
