#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "Clock.h"
#include "Event.h"

// Abstract base class for synths
class Voice {
public:
    virtual ~Voice() = default;

    virtual std::tuple<float, float> nextStereoSample(const double time) {
        float sample = nextSample(time);
        return std::make_tuple(sample, sample);
    }

    virtual float nextSample(double /*time*/) { return 0; }

    virtual void handleEvent(Event event) {
        m_currentEvent = event;
        setEnabled(true);
    }

    void setEnabled(const bool enabled) { m_enabled = enabled; }

    [[nodiscard]] bool enabled() const { return m_enabled; }

protected:
    bool m_enabled = false;
    Event m_currentEvent;
};
