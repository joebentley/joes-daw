#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>

#include "AudioCallback.h"
#include "AudioDeviceSelectorWindow.h"
#include "TrackComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent final : public juce::Component, public juce::Button::Listener {
public:
    //==============================================================================
    MainComponent();

    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

    void buttonClicked(juce::Button *) override;

private:
    juce::AudioDeviceManager m_audioDeviceManager;
    juce::TextButton m_showAudioDeviceSelectorWindowButton{"Audio settings"};
    AudioDeviceSelectorWindow *m_audioDeviceSelectorWindow = nullptr;
    AudioCallback m_audioCallback;

    TrackComponent m_trackComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
