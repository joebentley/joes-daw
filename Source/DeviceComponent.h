#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class DeviceComponent : public juce::Component {
public:
    DeviceComponent();

    void paint(juce::Graphics &g) override;

    void resized() override;

protected:
    juce::ComboBox m_deviceTypeComboBox;
};
