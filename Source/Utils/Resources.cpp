/*
  ==============================================================================

    Resources.cpp
    Created: 18 Feb 2023 9:50:47pm
    Author:  User

  ==============================================================================
*/

#include "Resources.h"

Resources::Resources()
{
    try {
        image_map.set(BACK, loadFromPng("BACK.png"));
        image_map.set(CLOSE, loadFromPng("CLOSE.png"));
        image_map.set(COPY, loadFromPng("COPY.png"));
        image_map.set(FORWARD, loadFromPng("FORWARD.png"));
        image_map.set(GOTO, loadFromPng("GOTO.png"));
        image_map.set(ICON, loadFromPng("ICON.png"));
        image_map.set(INFO, loadFromPng("INFO.png"));
        image_map.set(OK, loadFromPng("OK.png"));
        image_map.set(OPEN, loadFromPng("OPEN.png"));
        image_map.set(PAUSE, loadFromPng("PAUSE.png"));
        image_map.set(PLAY, loadFromPng("PLAY.png"));
        image_map.set(REJECT, loadFromPng("REJECT.png"));
        image_map.set(REPEAT, loadFromPng("REPEAT.png"));
        image_map.set(SETTINGS, loadFromPng("SETTINGS.png"));
        image_map.set(STOP, loadFromPng("STOP.png"));
        image_map.set(VOLUME_H, loadFromPng("VOLUME_H.png"));
        image_map.set(VOLUME_OFF, loadFromPng("VOLUME_OFF.png"));
        image_map.set(VOLUME_S, loadFromPng("VOLUME_S.png"));
    }
    catch (const std::exception&) {
        return;
    };
    usable = true;
    return;
}

Resources::~Resources()
{
}

juce::Image& Resources::get(RIndex idx)
{
    return image_map.getReference(idx);
}

bool Resources::isUsable()
{
    return usable;
}

juce::Image Resources::loadFromPng(juce::String name)
{
    auto exedir = getDir();
    auto imagepath = exedir.getChildFile("Resources/" + name);
    auto input = juce::FileInputStream(imagepath);
    if (input.failedToOpen()) {
        throw std::exception();
    }
    auto fmt = juce::PNGImageFormat();
    auto img = fmt.decodeImage(input);
    return img;
}
