#include "StepSequencerComponent.h"

#include "../../SettingsSingleton.h"

StepSequencerComponent::StepSequencerComponent(Settings::StepSequencer &settings)
    : m_settings(settings) {
    startTimerHz(60);

    setWantsKeyboardFocus(true);

    for (int i = 0; i < 16; ++i) {
        for (const auto note: settings.notes[i]) {
            m_stepSequencer.addNote(i, note);
        }
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
        for (auto note: m_stepSequencer.getStep(i)) {
            const auto cellY = height - (note - m_lowRange + 1) * cellHeight();
            g.setColour(juce::Colours::lightgreen);
            g.fillRect(i * cellWidth, cellY, cellWidth, cellHeight());
        }
    }

    const auto currentStep = m_stepSequencer.current();
    g.setColour(juce::Colours::greenyellow);
    g.fillRect(currentStep * cellWidth, height - ledArea, cellWidth, ledArea);
}

void StepSequencerComponent::timerCallback() {
    repaint();
}

void StepSequencerComponent::mouseDown(const juce::MouseEvent &event) {
    if (event.mods.isLeftButtonDown())
        handleLeftMouseEvent(event);
    else if (event.mods.isRightButtonDown())
        handleRightMouseEvent(event);
}

// void StepSequencerComponent::mouseDrag(const juce::MouseEvent &event) {
//     if (event.mods.isLeftButtonDown())
//         handleLeftMouseEvent(event);
//     else if (event.mods.isRightButtonDown())
//         handleRightMouseEvent(event);
// }

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

void StepSequencerComponent::handleLeftMouseEvent(const juce::MouseEvent &event) {
    const auto mousePos = event.getPosition();
    const int cellNumber = mousePos.x / cellWidth;
    const int cellMidiNote = (height - mousePos.y) / cellHeight() + m_lowRange;
    if (m_stepSequencer.addNote(cellNumber, cellMidiNote)) {
        m_settings.notes[cellNumber].push_back(cellMidiNote);
        SettingsSingleton::getInstance()->save();
    }
}

void StepSequencerComponent::handleRightMouseEvent(const juce::MouseEvent &event) {
    const auto mousePos = event.getPosition();
    const int cellNumber = mousePos.x / cellWidth;
    const int cellMidiNote = (height - mousePos.y) / cellHeight() + m_lowRange;
    if (m_stepSequencer.removeNote(cellNumber, cellMidiNote)) {
        const auto it = std::ranges::find(m_settings.notes[cellNumber], cellMidiNote);
        jassert(it != m_settings.notes[cellNumber].end());
        m_settings.notes[cellNumber].erase(it);
        SettingsSingleton::getInstance()->save();
    }
}

