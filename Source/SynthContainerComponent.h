#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

#include "DeviceContainerComponent.h"
#include "SynthComponent.h"
#include "Track.h"


class SynthContainerComponent : public DeviceContainerComponent, public juce::ComboBox::Listener {
public:
    SynthContainerComponent(Track &trackToInitialise);

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
    SynthComponent *m_synthComponent;

    Listener *m_listener = nullptr;

    bool m_firstCall = true;
};
