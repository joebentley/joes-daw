#pragma once
#include "DeviceContainerComponent.h"
#include "SequencerComponent.h"
#include "Track.h"


class SequencerContainerComponent : public DeviceContainerComponent, public juce::ComboBox::Listener {
public:
    SequencerContainerComponent(Track &trackToInitialise);

    ~SequencerContainerComponent() override;

    void resized() override;

    struct Listener {
        virtual void sequencerChanged(Sequencer *sequencer) = 0;

        virtual ~Listener() {
        }
    };

    void setListener(Listener *listener);

    void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

private:
    SequencerComponent *m_sequencerComponent;

    Listener *m_listener = nullptr;

    bool m_firstCall = true;
};
