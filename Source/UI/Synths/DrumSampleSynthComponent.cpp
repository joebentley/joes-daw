#include "DrumSampleSynthComponent.h"

DrumSampleSynthComponent::DrumSampleSynthComponent(Settings::DrumSampleSynth &settings)
    : m_samplerSynthComponent{
        SamplerSynthComponent(settings.drumSample[0]),
        SamplerSynthComponent(settings.drumSample[1]),
        SamplerSynthComponent(settings.drumSample[2]),
        SamplerSynthComponent(settings.drumSample[3])
    } {
    addAndMakeVisible(m_samplerSynthComponent[0]);
    addAndMakeVisible(m_samplerSynthComponent[1]);
    addAndMakeVisible(m_samplerSynthComponent[2]);
    addAndMakeVisible(m_samplerSynthComponent[3]);

    for (int i = 0; i < 4; ++i) {
        m_drumSampleSynth.setSamplerSynth(m_samplerSynthComponent[i].synth(), i);
    }
}

void DrumSampleSynthComponent::resized() {
    m_samplerSynthComponent[0].setBounds(0, 0, 200, 30);
    m_samplerSynthComponent[1].setBounds(0, 40, 200, 30);
    m_samplerSynthComponent[2].setBounds(0, 80, 200, 30);
    m_samplerSynthComponent[3].setBounds(0, 120, 200, 30);

    SynthComponent::resized();
}
