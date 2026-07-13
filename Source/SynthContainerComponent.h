#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

#include "DeviceContainerComponent.h"
#include "Settings.h"
#include "SynthComponent.h"
#include "Track.h"


class SynthContainerComponent : public DeviceContainerComponent, public juce::ComboBox::Listener {
public:
    SynthContainerComponent(Track &trackToInitialise, Settings::Synth &settings);

    ~SynthContainerComponent() override;

    void resized() override;

    struct Listener {
        virtual void synthChanged(Synth *synth) = 0;

        virtual ~Listener() {
        }
    };

    void setListener(Listener *listener);

    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

private:
    Settings::Synth &m_settings;

    SynthComponent *m_synthComponent;

    Listener *m_listener = nullptr;

    bool m_firstCall = true;

    SynthComponent *createInitialSynthComponent() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthContainerComponent)
};
