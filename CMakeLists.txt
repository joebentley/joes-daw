cmake_minimum_required(VERSION 3.22)

project(DAW VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(JUCE)
add_subdirectory(json)

juce_add_gui_app(daw
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "Joe's Daw"            # The name of the final executable, which can differ from the target name
    NEEDS_WEB_BROWSER FALSE             # Set to TRUE if you need to use webviews
    NEEDS_CURL FALSE)                   # Set to TRUE if you need to use curl

target_sources(daw
    PRIVATE
        Source/Main.cpp
        Source/Settings.cpp
        Source/Settings.h
        Source/SettingsSingleton.cpp
        Source/UI/MainComponent.cpp
        Source/UI/AudioDeviceSelectorWindow.cpp
        Source/DSP/AudioCallback.cpp
        Source/DSP/Clock.cpp
        Source/DSP/Track.cpp
        Source/DSP/Timeline.cpp
        Source/DSP/Synth.cpp
        Source/UI/TimelineComponent.cpp
        Source/UI/PatternComponent.cpp
        Source/UI/TrackComponent.cpp
        Source/UI/DeviceContainerComponent.cpp
        Source/UI/SequencerContainerComponent.cpp
        Source/DSP/Sequencers/RepeatingSequencer.cpp
        Source/UI/Sequencers/RepeatingSequencerComponent.cpp
        Source/DSP/Sequencers/RandomSequencer.cpp
        Source/UI/Sequencers/RandomSequencerComponent.cpp
        Source/DSP/Sequencers/StepSequencer.cpp
        Source/UI/Sequencers/StepSequencerComponent.cpp
        Source/UI/SynthContainerComponent.cpp
        Source/DSP/Synths/PingSynth.cpp
        Source/DSP/Synths/PingVoice.cpp
        Source/UI/Synths/PingSynthComponent.cpp
        Source/DSP/Synths/NoiseSynth.cpp
        Source/UI/Synths/NoiseSynthComponent.cpp
        Source/DSP/Synths/SamplerSynth.cpp
        Source/DSP/Synths/SamplerVoice.cpp
        Source/UI/Synths/SamplerSynthComponent.cpp
        Source/DSP/Synths/DrumSampleSynth.cpp
        Source/UI/Synths/DrumSampleSynthComponent.cpp
        Source/UI/ScrollingLabelComponent.cpp)

target_compile_definitions(daw
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:daw,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:daw,JUCE_VERSION>")

# If your target needs extra binary assets, you can add them here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when your target is built.

# juce_add_binary_data(GuiAppData SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_gui_extra` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically. If we'd generated a binary data target above, we would need to link to it
# here too. This is a standard CMake command.

target_link_libraries(daw
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_devices
        juce::juce_audio_utils
        juce::juce_gui_basics
        nlohmann_json::nlohmann_json
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
