#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "SequencerComponent.h"
#include "SynthComponent.h"
#include "Track.h"


class TrackComponent : public juce::Component, public juce::Button::Listener {
public:
    TrackComponent();

    ~TrackComponent() override;

    void resized() override;

    void buttonClicked(juce::Button *) override;

    void setSequencerComponentOwned(SequencerComponent *sequencerComponent);

    void setSynthComponentOwned(SynthComponent *synthComponent);

    [[nodiscard]] Track *track() {
        return &m_track;
    }

private:
    Track m_track;
    SequencerComponent *m_sequencerComponent = nullptr;
    SynthComponent *m_synthComponent = nullptr;

    juce::ToggleButton m_mutedButton;
};
