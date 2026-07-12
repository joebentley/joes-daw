#include "SamplerSynthComponent.h"

#include "../SettingsSingleton.h"

SamplerSynthComponent::SamplerSynthComponent(Settings::SamplerSynth &settings) : m_settings(settings) {
    if (const auto file = juce::File(settings.sample); file.existsAsFile()) {
        m_samplerSynth.setFile(file);
    } else {
        // TODO: rather than wiping user settings, we should display some feedback
        settings.sample = "";
        SettingsSingleton::getInstance()->save();
    }

    addAndMakeVisible(m_sampleFilePathTextEditor);
    m_sampleFilePathTextEditor.setReadOnly(true);
    m_sampleFilePathTextEditor.setText(settings.sample);

    addAndMakeVisible(m_sampleFileChooserButton);
    m_sampleFileChooserButton.addListener(this);
    m_sampleFileChooserButton.setButtonText("Choose");
}

void SamplerSynthComponent::resized() {
    m_sampleFilePathTextEditor.setBounds(5, 40, 120, 30);
    m_sampleFileChooserButton.setBounds(130, 40, 60, 30);

    SynthComponent::resized();
}

void SamplerSynthComponent::buttonClicked(juce::Button *) {
    constexpr auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    m_sampleFileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser &chooser) {
        if (const auto result = chooser.getResult(); result.exists()) {
            m_samplerSynth.setFile(result);
            m_settings.sample = std::string(result.getFullPathName().toRawUTF8());
            m_sampleFilePathTextEditor.setText(result.getFullPathName());
            SettingsSingleton::getInstance()->save();
        }
    });
}
