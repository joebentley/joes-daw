#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>

#include "../DSP/AudioCallback.h"
#include "AudioDeviceSelectorWindow.h"
#include "PatternComponent.h"
#include "../DSP/Timeline.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent final : public juce::Component, public juce::Button::Listener, public juce::Slider::Listener {
public:
    //==============================================================================
    explicit MainComponent(Settings::Settings &settings);

    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics &) override;

    void resized() override;

    void buttonClicked(juce::Button *) override;

    void sliderValueChanged(juce::Slider *) override;

private:
    Settings::Settings &m_settings;

    juce::AudioDeviceManager m_audioDeviceManager;
    juce::TextButton m_showAudioDeviceSelectorWindowButton{"Audio settings"};
    AudioDeviceSelectorWindow *m_audioDeviceSelectorWindow = nullptr;
    AudioCallback m_audioCallback;

    juce::Slider m_volumeSlider;

    juce::Slider m_chosenPatternSlider;
    juce::TextButton m_newPatternButton;
    juce::TextButton m_clearPatternButton;

    Timeline m_timeline;
    std::unique_ptr<PatternComponent> m_patternComponent;

    void switchPattern(int i);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
