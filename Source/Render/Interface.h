/*
  ==============================================================================

    Interface.h
    Created: 18 Feb 2023 2:58:09pm
    Author:  User

  ==============================================================================
  The interface of different render method.
*/

#pragma once
#include <JuceHeader.h>


class IRenderer : public juce::OpenGLAppComponent {
public:
    virtual void setSample(const juce::AudioSampleBuffer &data) = 0;
};
