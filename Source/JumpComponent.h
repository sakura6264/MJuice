/*
  ==============================================================================

    JumpComponent.h
    Created: 18 Feb 2023 7:49:51pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils/Resources.h"

//==============================================================================
/*
*/
class JumpComponent  : public juce::Component
{
public:
    JumpComponent(std::function<void(double,bool)> callback);
    ~JumpComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ImageButton button_ok;
    juce::ImageButton button_cancle;
    juce::TextEditor editor_minute;
    juce::TextEditor editor_second;
    juce::Label label_a;
    juce::Label label_b;
    juce::Label label_c;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JumpComponent)
};
