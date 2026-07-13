#pragma once

#include "SamplerSynth.h"
#include "../Settings.h"
#include "../SynthComponent.h"


class SamplerSynthComponent : public SynthComponent, public juce::Button::Listener {
public:
    explicit SamplerSynthComponent(Settings::SamplerSynth &settings);

    void resized() override;

    Synth *synth() override { return &m_samplerSynth; }

    void buttonClicked(juce::Button *) override;

private:
    Settings::SamplerSynth &m_settings;

    SamplerSynth m_samplerSynth;

    juce::TextEditor m_sampleFilePathTextEditor;
    juce::TextButton m_sampleFileChooserButton;

    std::unique_ptr<juce::FileChooser> m_sampleFileChooser = std::make_unique<juce::FileChooser>(
        "Select sample...", juce::File::getSpecialLocation(juce::File::userHomeDirectory), "*"
    );

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamplerSynthComponent)
};

