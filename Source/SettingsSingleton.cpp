#include "SettingsSingleton.h"

JUCE_IMPLEMENT_SINGLETON(SettingsSingleton)

SettingsSingleton::SettingsSingleton() {
    settings = Settings::Settings::loadFromSettingsFile();
}

SettingsSingleton::~SettingsSingleton() {
    clearSingletonInstance();
}

void SettingsSingleton::save() const {
    settings.save();
}
