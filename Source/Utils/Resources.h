/*
  ==============================================================================

    Resources.h
    Created: 18 Feb 2023 9:50:47pm
    Author:  User

  ==============================================================================
  Load the Resources
*/

#pragma once
#include <JuceHeader.h>
#include "Utils.h"

enum RIndex {
    BACK,
    CLOSE,
    COPY,
    FORWARD,
    GOTO,
    ICON,
    INFO,
    OK,
    OPEN,
    PAUSE,
    PLAY,
    REJECT,
    REPEAT,
    SETTINGS,
    STOP,
    VOLUME_H,
    VOLUME_OFF,
    VOLUME_S,
};
class Resources {
public:
    Resources();
    ~Resources();
    juce::Image& get(RIndex idx);
    bool isUsable();
private:
    juce::HashMap<RIndex,juce::Image> image_map;// init in the constructor.
    bool usable = false;
    static juce::Image loadFromPng(juce::String name);
};

static Resources R;
