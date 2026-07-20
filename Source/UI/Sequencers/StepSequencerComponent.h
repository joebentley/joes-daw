#pragma once

#include "../SequencerComponent.h"
#include "../../DSP/Sequencers/StepSequencer.h"
#include "../../Settings.h"

class StepSequencerComponent : public SequencerComponent, juce::Timer, juce::TextButton::Listener {
public:
    explicit StepSequencerComponent(Settings::StepSequencer &settings);

    void paint(juce::Graphics &g) override;

    void resized() override;

    Sequencer *sequencer() override { return &m_stepSequencer; }

    void timerCallback() override;

    void mouseDown(const juce::MouseEvent &event) override;

    bool keyPressed(const juce::KeyPress &key) override;

    void buttonClicked(juce::Button *) override;

private:
    Settings::StepSequencer &m_settings;
    StepSequencer m_stepSequencer;

    int m_lowRange = 60;
    int m_highRange = 80;

    juce::TextButton m_clearButton;

    int cellHeight() const;

    void handleLeftMouseEvent(const juce::MouseEvent &event);
};
