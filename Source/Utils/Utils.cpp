/*
  ==============================================================================

    Utils.cpp
    Created: 18 Feb 2023 2:59:40pm
    Author:  User

  ==============================================================================
*/

#include "Utils.h"

juce::File getDir()
{
    return juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory();
}

void stateReadAlert(juce::ModalComponentManager::Callback* callback)
{
    juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
        "ERROR",
        "\"settings.json\" is an invalid setting file. The program will use default settings.",
        juce::String(),
        nullptr,
        callback);
}

void stateWriteAlert(juce::ModalComponentManager::Callback* callback)
{
    juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
        "ERROR",
        "\"settings.json\" cannot be written.",
        juce::String(),
        nullptr,
        callback);
}

juce::String jsonFormat(double volume, double step, juce::String render_type)
{
    juce::String json_str;
    json_str << "{\r\n    \"volume\":" << volume << ",\r\n    \"step\":"<<step << ",\r\n    \"renderer_type\":\"" << render_type << "\"\r\n}";
    return json_str;
}

juce::String timeFormat(double time)
{
    int second = int(time) % 60;
    int minute = int(time) / 60;
    juce::String s;
    s << minute << ":";
    if (second < 10) {
        s << 0 << second;
    }
    else {
        s << second;
    }
    return s;
}

juce::String timeSFormat(double time, double all)
{
    juce::String s;
    s << timeFormat(time) << "/" << timeFormat(all);
    return s;
}
