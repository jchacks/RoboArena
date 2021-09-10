#include "rapch.h"
#include "application.h"

// #include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

Application::Application()
{
    m_window = std::unique_ptr<Window>(Window::create());
}

Application::~Application()
{
}

void Application::run()
{
    while (m_running)
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        m_window->on_update();
    }
}
