#include "Track.h"

void Track::renderNextBlock(Clock clock, juce::AudioBuffer<float> &toFill) {
    jassert(m_sequencer != nullptr);
    jassert(m_synth != nullptr);

    auto events = m_sequencer->generateEventsForTimes(clock.getTime(), clock.getTime(toFill.getNumSamples()));
    m_synth->renderNextBlock(clock, events, toFill);
}

void Track::setSequencerOwned(Sequencer *sequencer) {
    m_sequencer = sequencer;
}

void Track::setSynthOwned(Synth *synth) {
    m_synth = synth;
}

Track::~Track() {
    delete m_sequencer;
    delete m_synth;
}
