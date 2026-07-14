#pragma once

#include <exception>
#include <juce_core/juce_core.h>
#include <nlohmann/json.hpp>

#include "Settings.h"

using nlohmann::json;

struct SettingsLoadException : std::exception {
    juce::String message;

    [[nodiscard]] const char *what() const noexcept override {
        return (juce::String("Failed to load settings: ") + message).toRawUTF8();
    }
};

namespace juce {
    inline void to_json(json &j, const juce::String &string) {
        j = string.toRawUTF8();
    }

    inline void from_json(const json &j, juce::String &string) {
        string = j.get<std::string>().c_str();
    }
}

namespace Settings {
    enum class SequencerType {
        RANDOM_SEQUENCER, REPEATING_SEQUENCER
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(SequencerType, {
                                 {SequencerType::RANDOM_SEQUENCER, "RANDOM_SEQUENCER"},
                                 {SequencerType::REPEATING_SEQUENCER, "REPEATING_SEQUENCER"}
                                 })

    struct RandomSequencer {
        double lowRate;
        double highRate;
        int lowNote;
        int highNote;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RandomSequencer, lowRate, highRate, lowNote, highNote)

    struct RepeatingSequencer {
        double rate;
        double note;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RepeatingSequencer, rate, note)

    struct Sequencer {
        SequencerType type;

        std::variant<RandomSequencer, RepeatingSequencer> settings;

        static Sequencer standard() {
            return {
                .type = SequencerType::REPEATING_SEQUENCER,
                .settings = RepeatingSequencer{
                    .rate = 1.0,
                    .note = 60.0
                }
            };
        }
    };

    inline void to_json(json &j, const Sequencer &sequencer) {
        json jsonSequencerType;
        to_json(jsonSequencerType, sequencer.type);

        json jsonSequencerSettings;
        switch (sequencer.type) {
            case SequencerType::RANDOM_SEQUENCER:
                to_json(jsonSequencerSettings, std::get<RandomSequencer>(sequencer.settings));
                break;
            case SequencerType::REPEATING_SEQUENCER:
                to_json(jsonSequencerSettings, std::get<RepeatingSequencer>(sequencer.settings));
                break;
        }

        j = json({{"type", jsonSequencerType}, {"settings", jsonSequencerSettings}});
    }

    inline void from_json(const json &j, Sequencer &sequencer) {
        from_json(j.at("type"), sequencer.type);

        switch (sequencer.type) {
            case SequencerType::RANDOM_SEQUENCER:
                RandomSequencer randomSequencer;
                j.at("settings").get_to(randomSequencer);
                sequencer.settings = randomSequencer;
                break;
            case SequencerType::REPEATING_SEQUENCER:
                RepeatingSequencer repeatingSequencer;
                j.at("settings").get_to(repeatingSequencer);
                sequencer.settings = repeatingSequencer;
                break;
        }
    }

    enum class SynthType {
        PING_SYNTH, NOISE_SYNTH, SAMPLER_SYNTH, DRUM_SAMPLE_SYNTH
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(SynthType, {
                                 {SynthType::PING_SYNTH, "PING_SYNTH"},
                                 {SynthType::NOISE_SYNTH, "NOISE_SYNTH"},
                                 {SynthType::SAMPLER_SYNTH, "SAMPLER_SYNTH"},
                                 {SynthType::DRUM_SAMPLE_SYNTH, "DRUM_SAMPLE_SYNTH"}
                                 })

    struct PingSynth {
        double decayRate;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PingSynth, decayRate)

    struct NoiseSynth {
        double decayRate;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NoiseSynth, decayRate)

    struct SamplerSynth {
        juce::String sample;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SamplerSynth, sample)

    struct DrumSampleSynth {
        juce::String drumSample[4];
    };


    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DrumSampleSynth, drumSample)

    struct Synth {
        SynthType type;

        std::variant<PingSynth, NoiseSynth, SamplerSynth, DrumSampleSynth> settings;

        static Synth standard() {
            return {
                .type = SynthType::PING_SYNTH,
                .settings = PingSynth{
                    .decayRate = 10.0
                }
            };
        }
    };

    inline void to_json(json &j, const Synth &synth) {
        json jsonSynthType;
        to_json(jsonSynthType, synth.type);

        json jsonSynthSettings;
        switch (synth.type) {
            case SynthType::PING_SYNTH:
                to_json(jsonSynthSettings, std::get<PingSynth>(synth.settings));
                break;
            case SynthType::NOISE_SYNTH:
                to_json(jsonSynthSettings, std::get<NoiseSynth>(synth.settings));
                break;
            case SynthType::SAMPLER_SYNTH:
                to_json(jsonSynthSettings, std::get<SamplerSynth>(synth.settings));
                break;
            case SynthType::DRUM_SAMPLE_SYNTH:
                to_json(jsonSynthSettings, std::get<DrumSampleSynth>(synth.settings));
                break;
        }

        j = json({{"type", jsonSynthType}, {"settings", jsonSynthSettings}});
    }

    inline void from_json(const json &j, Synth &synth) {
        from_json(j.at("type"), synth.type);

        switch (synth.type) {
            case SynthType::PING_SYNTH: {
                PingSynth pingSynth;
                j.at("settings").get_to(pingSynth);
                synth.settings = pingSynth;
                break;
            }
            case SynthType::NOISE_SYNTH: {
                NoiseSynth noiseSynth;
                j.at("settings").get_to(noiseSynth);
                synth.settings = noiseSynth;
                break;
            }
            case SynthType::SAMPLER_SYNTH: {
                SamplerSynth samplerSynth;
                j.at("settings").get_to(samplerSynth);
                synth.settings = samplerSynth;
                break;
            }
            case SynthType::DRUM_SAMPLE_SYNTH: {
                DrumSampleSynth drumSampleSynth;
                j.at("settings").get_to(drumSampleSynth);
                synth.settings = drumSampleSynth;
                break;
            }
        }
    }

    struct Track {
        bool enabled{};
        Sequencer sequencer;
        Synth synth;

        static Track standard() {
            return {
                .enabled = false,
                .sequencer = Sequencer::standard(),
                .synth = Synth::standard()
            };
        }
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Track, enabled, sequencer, synth)

    struct Settings {
        double masterVolume{};
        juce::String lastSampleDirectory{};
        Track trackSettings[4];

        static Settings standard() {
            return {
                .masterVolume = -12.0,
                .lastSampleDirectory = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).
                getFullPathName(),
                .trackSettings = {Track::standard(), Track::standard(), Track::standard(), Track::standard()}
            };
        }

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Settings, masterVolume, lastSampleDirectory, trackSettings)

        static Settings loadFromSettingsFile();

        void save() const;
    };
}
