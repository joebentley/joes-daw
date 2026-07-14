#include "SamplerSynthComponent.h"

#include "../../SettingsSingleton.h"

SamplerSynthComponent::SamplerSynthComponent(Settings::SamplerSynth &settings) : m_settings(settings) {
    if (const auto file = juce::File(settings.sample); file.existsAsFile()) {
        m_samplerSynth.setFile(file);
    } else {
        // TODO: rather than wiping user settings, we should display some feedback
        settings.sample = "";
        SettingsSingleton::getInstance()->save();
    }

    addAndMakeVisible(m_sampleFilePathScrollingLabel);
    m_sampleFilePathScrollingLabel.setText(settings.sample);

    addAndMakeVisible(m_sampleFileChooserButton);
    m_sampleFileChooserButton.addListener(this);
    m_sampleFileChooserButton.setButtonText("Choose");
}

void SamplerSynthComponent::resized() {
    m_sampleFilePathScrollingLabel.setBounds(5, 40, 120, 30);
    m_sampleFileChooserButton.setBounds(130, 40, 60, 30);

    SynthComponent::resized();
}

void SamplerSynthComponent::buttonClicked(juce::Button *) {
    constexpr auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    const auto settingsInstance = SettingsSingleton::getInstance();
    m_sampleFileChooser = std::make_unique<juce::FileChooser>(
        "Select sample...", settingsInstance->settings.lastSampleDirectory, "*"
    );

    m_sampleFileChooser->launchAsync(fileChooserFlags, [this, settingsInstance](const juce::FileChooser &chooser) {
        if (const auto result = chooser.getResult(); result.exists()) {
            m_samplerSynth.setFile(result);
            m_settings.sample = result.getFullPathName();
            m_sampleFilePathScrollingLabel.setText(result.getFullPathName());

            settingsInstance->settings.lastSampleDirectory = result.getParentDirectory().getFullPathName();

            SettingsSingleton::getInstance()->save();
        }
    });
}
