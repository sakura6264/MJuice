/*
  ==============================================================================

    SettingsComponent.cpp
    Created: 18 Feb 2023 2:44:05pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsComponent.h"

//==============================================================================
SettingsComponent::SettingsComponent(AppState * s)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(400, 400);
    auto color = juce::Colours::transparentWhite;
    button_ok.setImages(true, true, true, R.get(OK), 0.8F, color, R.get(OK), 1.0F, color, R.get(OK), 0.6F, color);
    button_cancle.setImages(true, true, true, R.get(REJECT), 0.8F, color, R.get(REJECT), 1.0F, color, R.get(REJECT), 0.6F, color);
    for (auto i : factory.getList()) {
        renderer_combo.addItem(i.v, int(i.k) + 10);
    }
    renderer_combo.setSelectedId(int(s->renderer_type) + 10);
    step_edit.setSliderStyle(juce::Slider::LinearBar);
    step_edit.setNormalisableRange(juce::NormalisableRange<double>(0, 20, 0.1));
    step_edit.setColour(juce::Slider::trackColourId, juce::Colours::grey);
    step_edit.setValue(s->step);
    button_ok.onClick = [this,s] {
        s->step = step_edit.getValue();
        s->renderer_type = RendererFactory::RendererType(renderer_combo.getSelectedId() - 10);
        if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
            dw->exitModalState(0);
    };
    button_cancle.onClick = [this] {
        if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
            dw->exitModalState(0);
    };
    label_renderer.setText("Renderer : ", juce::dontSendNotification);
    label_step.setText("Step : ", juce::dontSendNotification);
    addAndMakeVisible(label_renderer);
    addAndMakeVisible(label_step);
    addAndMakeVisible(step_edit);
    addAndMakeVisible(renderer_combo);
    addAndMakeVisible(button_cancle);
    addAndMakeVisible(button_ok);
}

SettingsComponent::~SettingsComponent()
{
}

void SettingsComponent::paint (juce::Graphics& g)
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

void SettingsComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto f = getBounds();
    // draw components
    constexpr int bw = 40;
    constexpr int bh = 40;
    button_ok.setBounds(f.getWidth() - 2 * bw, f.getHeight() - bh, bw, bh);
    button_cancle.setBounds(f.getWidth() - bw, f.getHeight() - bh, bw, bh);
    constexpr int margin = 5;
    constexpr int h = 30;
    renderer_combo.setBounds(f.getWidth() / 2 + margin,   margin, f.getWidth() / 2 - 2* margin, h);
    step_edit.setBounds(f.getWidth() / 2 + margin,  h + 2 * margin, f.getWidth() / 2 - 2 * margin, h);
    label_renderer.setBounds(margin, margin, f.getWidth() / 2 - 2 * margin, h);
    label_step.setBounds(margin,  h + 2 * margin, f.getWidth() / 2 - 2 * margin, h);
}
