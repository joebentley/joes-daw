#pragma once
#include "../SequencerComponent.h"
#include "../../DSP/Sequencers/StepSequencer.h"
#include "../../Settings.h"


class StepSequencerComponent : public SequencerComponent, juce::Timer {
public:
    explicit StepSequencerComponent(Settings::StepSequencer &settings);

    void paint(juce::Graphics &g) override;

    Sequencer *sequencer() override { return &m_stepSequencer; }

    void timerCallback() override;

    void mouseDown(const juce::MouseEvent &event) override;

    // void mouseDrag(const juce::MouseEvent &event) override;

    bool keyPressed(const juce::KeyPress &key) override;

private:
    Settings::StepSequencer &m_settings;
    StepSequencer m_stepSequencer;

    int m_lowRange = 60;
    int m_highRange = 80;

    int cellHeight() const;

    void handleLeftMouseEvent(const juce::MouseEvent &event);

    void handleRightMouseEvent(const juce::MouseEvent &event);
};
