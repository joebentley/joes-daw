#include "Settings.h"

Settings::Settings Settings::Settings::loadFromSettingsFile() {
    const auto settingsDir = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
    const auto settingsFile = settingsDir.getChildFile("JoesDAW/settings.json");

    if (!settingsFile.exists()) {
        auto createResult = settingsFile.create();
        if (createResult.failed()) {
            juce::Logger::writeToLog("Failed to create file: " + createResult.getErrorMessage());
            jassertfalse;
        }

        const auto defaultSettings = standard();
        json j;
        to_json(j, defaultSettings);
        jassert(settingsFile.replaceWithText(j.dump(2)));

        return defaultSettings;
    }

    const auto contents = settingsFile.loadFileAsString();
    json j = json::parse(contents.toRawUTF8());
    Settings settings;
    from_json(j, settings);
    return settings;
}

void Settings::Settings::save() const {
    const auto settingsDir = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
    const auto settingsFile = settingsDir.getChildFile("JoesDAW/settings.json");

    if (!settingsFile.exists()) {
        const auto createResult = settingsFile.create();
        if (createResult.failed()) {
            juce::Logger::writeToLog("Failed to create file: " + createResult.getErrorMessage());
            jassertfalse;
        }
    }

    json j;
    to_json(j, *this);
    jassert(settingsFile.replaceWithText(j.dump(2)));
}
