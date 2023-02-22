/*
  ==============================================================================

    JumpComponent.cpp
    Created: 18 Feb 2023 7:49:51pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "JumpComponent.h"

//==============================================================================
JumpComponent::JumpComponent(std::function<void(double,bool)> callback)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(200, 200);
    auto color = juce::Colours::transparentWhite;
    button_ok.setImages(true, true, true, R.get(OK), 0.8F, color, R.get(OK), 1.0F, color, R.get(OK), 0.6F, color);
    button_cancle.setImages(true, true, true, R.get(REJECT), 0.8F, color, R.get(REJECT), 1.0F, color, R.get(REJECT), 0.6F, color);
    editor_minute.setInputFilter(new juce::TextEditor::LengthAndCharacterRestriction(-1, "1234567890"), true);
    editor_second.setInputFilter(new juce::TextEditor::LengthAndCharacterRestriction(2, "1234567890"), true);
    label_a.setText("Goto:",juce::dontSendNotification);
    label_b.setText("min",juce::dontSendNotification);
    label_c.setText("s", juce::dontSendNotification);
    button_ok.onClick = [this,callback] {
        int m = 0;
        if (!editor_minute.getText().isEmpty()) {
            m = editor_minute.getText().getIntValue();
        }
        int s = 0;
        if (!editor_second.getText().isEmpty()) {
            s = editor_second.getText().getIntValue();
        }
        auto time_jmp = m * 60.0 + s;
        callback(time_jmp,true);
        if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
            dw->exitModalState(0);
    };
    button_cancle.onClick = [this,callback] {
        callback(0,false);
        if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
            dw->exitModalState(0);
    };
    addAndMakeVisible(button_ok);
    addAndMakeVisible(button_cancle);
    addAndMakeVisible(label_a);
    addAndMakeVisible(label_b);
    addAndMakeVisible(label_c);
    addAndMakeVisible(editor_minute);
    addAndMakeVisible(editor_second);

}

JumpComponent::~JumpComponent()
{
}

void JumpComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    auto f = getBounds();
    constexpr int bw = 64;
    constexpr int bh = 64;


    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
    g.drawImageAt(R.get(ICON), 0, f.getHeight() - bh);
}

void JumpComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto f = getBounds();
    // draw components
    constexpr int bw = 40;
    constexpr int bh = 40;
    button_ok.setBounds(f.getWidth() - 2 * bw, f.getHeight() - bh, bw, bh);
    button_cancle.setBounds(f.getWidth() -  bw, f.getHeight() - bh, bw, bh);
    constexpr int margin = 5;
    constexpr int h = 20;
    label_a.setBounds(margin, margin, f.getWidth() - 2 * margin, h);
    label_b.setBounds(f.getWidth() / 2+margin, h+2*margin, f.getWidth()/2 - 2* margin, h);
    label_c.setBounds(f.getWidth() / 2+margin, 2*h+3*margin, f.getWidth()/2 - 2 * margin, h);
    editor_minute.setBounds(margin, h + 2 * margin, f.getWidth() / 2 - 2 * margin, h);
    editor_second.setBounds(margin, 2 * h + 3 * margin, f.getWidth() / 2 - 2 * margin, h);
}
