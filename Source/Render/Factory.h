/*
  ==============================================================================

    Factory.h
    Created: 18 Feb 2023 2:57:58pm
    Author:  User

  ==============================================================================
  Renderer factory.
*/

#pragma once
#include "Interface.h"
#include <JuceHeader.h>
#include "Impl/ProjectMRender.h"

class RendererFactory {
public:
    enum RendererType {
        // Register renderer
        ProjectM,
        NotFound
    };
    class KV
    {
    public:
        RendererType k;
        juce::String v;
        KV(RendererType k, juce::String v);
        KV();
    };
    juce::Array<KV> getList();
    RendererFactory();
    std::unique_ptr<IRenderer> getRenderer(RendererType type);// return nullptr if not found. use new to malloc, remember to delete.
    juce::String getV(RendererType k);
    RendererType getK(juce::String v);
private:
    juce::Array<KV> type_list;// init in constructor.
};

static RendererFactory factory;