/*
  ==============================================================================

    Factory.cpp
    Created: 18 Feb 2023 2:57:58pm
    Author:  User

  ==============================================================================
*/

#include "Factory.h"

juce::Array<RendererFactory::KV> RendererFactory::getList()
{
    return type_list;
}

RendererFactory::RendererFactory()
{
    type_list.add(KV(ProjectM, "ProjectM"));
}

std::unique_ptr<IRenderer> RendererFactory::getRenderer(RendererType type)
{
    switch (type)
    {
    case ProjectM:
        return std::make_unique<ProjectMRender>();
        break;
    case NotFound:
        return std::unique_ptr<IRenderer>(nullptr);
        break;
    }
}

juce::String RendererFactory::getV(RendererType k)
{
    juce::String ret;
    for (int i = 0; i < type_list.size(); i++) {
        if (type_list[i].k == k) {
            ret = type_list[i].v;
            break;
        }
    }
    return ret;
}

RendererFactory::RendererType RendererFactory::getK(juce::String v)
{
    RendererType ret = NotFound;
    for (int i = 0; i < type_list.size(); i++) {
        if (type_list[i].v == v) {
            ret = type_list[i].k;
            break;
        }
    }
    return ret;
}

RendererFactory::KV::KV(RendererType k, juce::String v)
{
    this->k = k;
    this->v = v;
}

RendererFactory::KV::KV()
{
    k = NotFound;
}
