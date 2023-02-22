/*
  ==============================================================================

    ProjectMRender.cpp
    Created: 21 Feb 2023 7:47:35pm
    Author:  User

  ==============================================================================
*/

#include "ProjectMRender.h"

void ProjectMRender::initialise()
{
    handle = projectm_create();
    if (handle == nullptr) {
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
            "Cannot init renderer.", "ERROR");
    }
    projectm_set_fps(handle, 60);
    projectm_set_mesh_size(handle, 220, 125);
    projectm_set_aspect_correction(handle,true);
    // Preset display settings
    projectm_set_preset_duration(handle, 10);
    projectm_set_soft_cut_duration(handle, 3);
    projectm_set_hard_cut_enabled(handle, true);
    projectm_set_hard_cut_duration(handle, 20);
    projectm_set_hard_cut_sensitivity(handle, static_cast<float>(10.0));
    projectm_set_beat_sensitivity(handle, static_cast<float>(10.0));
}

void ProjectMRender::shutdown()
{
    if (handle != nullptr) {
        projectm_destroy(handle);
        handle = nullptr;
    }
    
}

void ProjectMRender::render()
{
    auto scale = openGLContext.getRenderingScale();
    juce::OpenGLHelpers::clear(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    auto width = juce::roundToInt(scale * getWidth());
    auto height = juce::roundToInt(scale * getHeight());
    if (w != width || h != height) {
        w = width;
        h = height;
        projectm_set_window_size(handle, width, height);
    }
    juce::gl::glViewport(0, 0, width, height);
    juce::gl::glClearColor(0.0, 0.0, 0.0, 0.0);
    juce::gl::glClear(juce::gl::GL_COLOR_BUFFER_BIT | juce::gl::GL_DEPTH_BUFFER_BIT);
    int channel = current_data.getNumChannels();
    auto mode = channel < 2 ? PROJECTM_MONO : PROJECTM_STEREO;
    projectm_pcm_add_float(handle, (const float*)(current_data.getArrayOfReadPointers()), current_data.getNumSamples(), mode);

    projectm_opengl_render_frame(handle);

}

void ProjectMRender::setSample(const juce::AudioSampleBuffer &data)
{
    current_data = data;
}

void ProjectMRender::paint(juce::Graphics& g)
{
}

ProjectMRender::~ProjectMRender()
{
    shutdownOpenGL();
}


