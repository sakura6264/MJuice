/*
  ==============================================================================

    ProjectMRender.h
    Created: 21 Feb 2023 7:47:35pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include "../Interface.h"
#include <libprojectM/projectM.h>
#include <JuceHeader.h>

class ProjectMRender : public IRenderer {
    
public:
    virtual void initialise() override;
    virtual void shutdown() override;
    virtual void render() override;
    virtual void setSample(const juce::AudioSampleBuffer &data) override;
    void paint(juce::Graphics& g) override;
    ~ProjectMRender();
private:
    projectm_handle handle = nullptr;
    juce::AudioSampleBuffer current_data;
    int w = 0;
    int h = 0;
    
};