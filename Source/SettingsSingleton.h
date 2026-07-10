#pragma once

#include <juce_core/juce_core.h>

#include "Settings.h"


class SettingsSingleton {
public:
    SettingsSingleton();

    ~SettingsSingleton();

    void save() const;

    Settings::Settings settings;

    JUCE_DECLARE_SINGLETON(SettingsSingleton, false)
};
