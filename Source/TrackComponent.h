#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "SequencerContainerComponent.h"
#include "Settings.h"
#include "SynthComponent.h"
#include "SynthContainerComponent.h"
#include "Track.h"


class TrackComponent : public juce::Component, public juce::Button::Listener,
                       SequencerContainerComponent::Listener, SynthContainerComponent::Listener {
public:
    TrackComponent(Settings::Track &settings);

    void resized() override;

    void buttonClicked(juce::Button *) override;

    void sequencerChanged(Sequencer *sequencer) override;

    void synthChanged(Synth *sequencer) override;

    [[nodiscard]] Track *track() {
        return &m_track;
    }

private:
    Settings::Track &m_settings;

    Track m_track;

    SequencerContainerComponent m_sequencerContainerComponent;
    SynthContainerComponent m_synthContainerComponent;

    juce::ToggleButton m_mutedButton;
};
