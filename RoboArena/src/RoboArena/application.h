#pragma once

#include "core.h"
// #include "Events/Event.h"
#include "window.h"

class  Application
{
public:
    Application();
    virtual ~Application();

    void run();
private:
    std::unique_ptr<Window> m_window;
    bool m_running = true;
};

// To be defined in CLIENT
Application* create_application();
