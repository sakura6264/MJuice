/*
  ==============================================================================

    AnalyzeComponent.h
    Created: 18 Feb 2023 2:52:39pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils/Resources.h"

//==============================================================================
/*
*/
class AnalyzeComponent  : public juce::Component
{
public:
    AnalyzeComponent(juce::String text);
    ~AnalyzeComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ImageButton button_ok;
    juce::ImageButton button_copy;
    juce::Label text_info;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyzeComponent)
};
