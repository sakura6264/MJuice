/*
  ==============================================================================

    AnalyzeComponent.cpp
    Created: 18 Feb 2023 2:52:39pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AnalyzeComponent.h"


//==============================================================================
AnalyzeComponent::AnalyzeComponent(juce::String text)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(400, 400);
    auto color = juce::Colours::transparentWhite;
    button_ok.setImages(true, true, true, R.get(OK), 0.8F, color, R.get(OK), 1.0F, color, R.get(OK), 0.6F, color);
    button_copy.setImages(true, true, true, R.get(COPY), 0.8F, color, R.get(COPY), 1.0F, color, R.get(COPY), 0.6F, color);
    text_info.setText(text, juce::dontSendNotification);
    button_ok.onClick = [this] {
        if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
            dw->exitModalState(0);
    };
    button_copy.onClick = [this, text] {
        juce::SystemClipboard::copyTextToClipboard(text);
    };
    addAndMakeVisible(button_copy);
    addAndMakeVisible(button_ok);
    addAndMakeVisible(text_info);
}

AnalyzeComponent::~AnalyzeComponent()
{
}

void AnalyzeComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    auto f = getBounds();
    constexpr int bw = 64;
    constexpr int bh = 64;


    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.drawImageAt(R.get(ICON), 0, f.getHeight() - bh);
}

void AnalyzeComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto f = getBounds();
    // draw components
    constexpr int bw = 40;
    constexpr int bh = 40;
    button_ok.setBounds(f.getWidth() - 2 * bw, f.getHeight() - bh, bw, bh);
    button_copy.setBounds(f.getWidth() - bw, f.getHeight() - bh, bw, bh);
    constexpr int margin = 5;
    text_info.setBounds(margin, margin, f.getWidth() - 2 * margin, f.getHeight() - bh - 2 * margin);
}
