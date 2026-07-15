#include "StepSequencerComponent.h"

#include "../../SettingsSingleton.h"

StepSequencerComponent::StepSequencerComponent(Settings::StepSequencer &settings)
    : m_settings(settings) {
    startTimerHz(60);

    setWantsKeyboardFocus(true);

    for (int i = 0; i < 16; ++i) {
        m_stepSequencer.setStep(i, settings.notes[i]);
    }
}

constexpr int numCells = 16;
constexpr int width = 200;
constexpr int cellWidth = width / numCells;
constexpr int height = 190;
constexpr int ledArea = 10;

void StepSequencerComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::grey);
    g.fillRect(0, 0, width, height);

    for (int i = 0; i < numCells; i++) {
        const auto cellY = height - (m_stepSequencer.getStep(i) - m_lowRange) * cellHeight();
        g.setColour(juce::Colours::lightgreen);
        g.fillRect(i * cellWidth, cellY, cellWidth, cellHeight());
    }

    const auto currentStep = m_stepSequencer.current();
    g.setColour(juce::Colours::greenyellow);
    g.fillRect(currentStep * cellWidth, height - ledArea, cellWidth, ledArea);
}

void StepSequencerComponent::timerCallback() {
    repaint();
}

void StepSequencerComponent::mouseDrag(const juce::MouseEvent &event) {
    const auto mousePos = event.getPosition();
    const int cellNumber = mousePos.x / cellWidth;
    const int cellMidiNote = (height - mousePos.y) / cellHeight() + m_lowRange;
    if (m_stepSequencer.setStep(cellNumber, cellMidiNote)) {
        m_settings.notes[cellNumber] = cellMidiNote;
        SettingsSingleton::getInstance()->save();
    }
}

bool StepSequencerComponent::keyPressed(const juce::KeyPress &key) {
    if (key.getKeyCode() == key.upKey) {
        m_highRange++;
        m_lowRange++;
        return true;
    }
    if (key.getKeyCode() == key.downKey) {
        m_highRange--;
        m_lowRange--;
        return true;
    }
    return false;
}

int StepSequencerComponent::cellHeight() const {
    return (height - ledArea) / (m_highRange - m_lowRange);
}

