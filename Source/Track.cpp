#include "Track.h"

void Track::renderNextBlock(const Clock clock, juce::AudioBuffer<float> &toFill) const {
    jassert(m_sequencer != nullptr);
    jassert(m_synth != nullptr);

    auto events = m_sequencer->generateEventsForTimes(clock.getTime(), clock.getTime(toFill.getNumSamples()));
    m_synth->renderNextBlock(clock, events, toFill);
}

void Track::setSequencer(Sequencer *sequencer) {
    m_sequencer = sequencer;
}

void Track::setSynth(Synth *synth) {
    m_synth = synth;
}
