#include "PatternComponent.h"

#include "../DSP/AudioCallback.h"

PatternComponent::PatternComponent(Settings::Pattern &settings)
    : m_settings(settings),
      m_trackComponents{
          settings.trackSettings[0],
          settings.trackSettings[1],
          settings.trackSettings[2],
          settings.trackSettings[3]
      } {
    for (int i = 0; i < 4; ++i) {
        addAndMakeVisible(m_trackComponents[i]);
    }
}

void PatternComponent::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::grey);

    for (int i = 0; i < 4; ++i) {
        const float x = static_cast<float>(i * 220 - 5);
        g.drawLine(x, 30, x, static_cast<float>(getHeight() - 40), 2);
    }
}

void PatternComponent::resized() {
    for (int i = 0; i < 4; ++i) {
        m_trackComponents[i].setBounds(i * 220, 0, 200, 500);
    }
}

void PatternComponent::setAudioCallbackTracks(AudioCallback &audioCallback) {
    for (int i = 0; i < 4; ++i) {
        audioCallback.setTrack(m_trackComponents[i].track(), i);
    }
}
