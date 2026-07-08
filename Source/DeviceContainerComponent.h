#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class DeviceContainerComponent : public juce::Component {
public:
    DeviceContainerComponent();

    void paint(juce::Graphics &g) override;

    void resized() override;

protected:
    juce::ComboBox m_deviceTypeComboBox;
};
