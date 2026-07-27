#pragma once

#include "Clock.h"
#include <juce_audio_devices/juce_audio_devices.h>

#include "Timeline.h"
#include "Track.h"

class AudioCallback : public juce::AudioIODeviceCallback {
public:
    explicit AudioCallback(Timeline &timeline);

    class Listener {
    public:
        virtual ~Listener() {
        }

        virtual void patternChanged(int newPatternIndex) = 0;
    };

    void setListener(Listener *listener);

    void audioDeviceIOCallbackWithContext(const float *const *inputChannelData, int numInputChannels,
                                          float *const *outputChannelData, int numOutputChannels, int numSamples,
                                          const juce::AudioIODeviceCallbackContext &context) override;

    void audioDeviceAboutToStart(juce::AudioIODevice *device) override;

    void audioDeviceStopped() override;

    void setTrack(Track *track, int n);

    void setMasterVolume(double masterVolumeDb);

    [[nodiscard]] double masterVolume() const;

private:
    Clock m_clock;

    Timeline &m_timeline;

    Track *m_tracks[4] = {nullptr, nullptr, nullptr, nullptr};

    Listener *m_listener = nullptr;
    
    double m_masterVolume = -12.0;
};
