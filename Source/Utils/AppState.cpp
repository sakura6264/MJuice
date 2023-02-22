/*
  ==============================================================================

    AppState.cpp
    Created: 18 Feb 2023 3:00:39pm
    Author:  User

  ==============================================================================
*/

#include "AppState.h"

AppState::AppState()
{
    volunm = 50;
    renderer_type = RendererFactory::RendererType::ProjectM;
    step = 5.0;
    read();
}

AppState::~AppState()
{
    write();
}

void AppState::read()
{
    auto json_file = getDir().getChildFile("settings.json");
    if (!json_file.existsAsFile()) {
        write();
        return;
    }
    try
    {
        juce::var json_var;
        if (juce::JSON::parse(json_file.loadFileAsString(), json_var).failed()) {
            throw std::exception();
        }
        if (!json_var.isObject()) {
            throw std::exception();
        }
        if (!(json_var.hasProperty("renderer_type") && json_var.hasProperty("volume") && json_var.hasProperty("step"))) {
            throw std::exception();
        }
        auto rt_var = json_var.getProperty("renderer_type", factory.getV(RendererFactory::RendererType::ProjectM));
        auto v_var = json_var.getProperty("volume", 50.0);
        auto s_var = json_var.getProperty("step", 5.0);
        if (!((v_var.isDouble() || v_var.isInt() || v_var.isInt64()) && (s_var.isDouble() || s_var.isInt() || s_var.isInt64()) && rt_var.isString())) {
            throw std::exception();
        }
        auto v = double(v_var);
        auto rt = factory.getK(rt_var.toString());
        auto s = double(s_var);
        if (!(v > 0 && v < 100 && s > 0 && s<20 &&  rt != RendererFactory::RendererType::NotFound)) {
            throw std::exception();
        }
        volunm = v;
        renderer_type = rt;
        step = s;
    }
    catch (const std::exception&)
    {
        alert = Read;
        useDefault();
    }
}

void AppState::write()
{
    auto json_file = getDir().getChildFile("settings.json");
    try
    {
        if (!json_file.deleteRecursively()) {
            throw std::exception();
        }
        if (!json_file.replaceWithText(jsonFormat(volunm,step,factory.getV(renderer_type)))) {
            throw std::exception();
        }
    }
    catch (const std::exception&)
    {
        alert = Write;
    }
}

void AppState::useDefault()
{
    volunm = 50;
    renderer_type = RendererFactory::RendererType::ProjectM;
    step = 5.0;
}
