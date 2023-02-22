/*
  ==============================================================================

    SettingsComponent.h
    Created: 18 Feb 2023 2:44:05pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils/AppState.h"
#include "Utils/Resources.h"

//==============================================================================
/*
*/
class SettingsComponent  : public juce::Component
{
public:
    SettingsComponent(AppState *state);
    ~SettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Label label_renderer;
    juce::Label label_step;
    juce::ImageButton button_ok;
    juce::ImageButton button_cancle;
    juce::Slider step_edit;
    juce::ComboBox renderer_combo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};
