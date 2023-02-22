/*
  ==============================================================================

    AppState.h
    Created: 18 Feb 2023 3:00:39pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include "../Render/Factory.h"
#include "Utils.h"

class AppState {
public:
    enum Alert {
        Read,Write,None
    };
    double volunm;
    double step;
    RendererFactory::RendererType renderer_type;
    Alert alert = None;
    AppState();
    ~AppState();
    void read();
    void write();
    void useDefault();
};