/*
  ==============================================================================

    Utils.h
    Created: 18 Feb 2023 2:59:40pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
juce::File getDir();
void stateReadAlert(juce::ModalComponentManager::Callback* callback=nullptr);
void stateWriteAlert(juce::ModalComponentManager::Callback* callback = nullptr);
juce::String jsonFormat(double volume, double step, juce::String render_type);
juce::String timeFormat(double time);
juce::String timeSFormat(double time, double all);