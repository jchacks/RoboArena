#pragma once

#include "RoboArena/window.h"
#include <GLFW/glfw3.h>

class LinuxWindow : public Window
{
public:
    LinuxWindow(const WindowProps &props);
    virtual ~LinuxWindow();

    void on_update() override;

    inline unsigned int get_width() const override { return m_data.width; };
    inline unsigned int get_height() const override { return m_data.height; };

    void set_vsync(bool enabled) override;
    bool is_vsync() const override;

private:
    virtual void init(const WindowProps &props);
    virtual void shutdown();

private:
    GLFWwindow *m_window;

    struct WindowData
    {
        std::string title;
        unsigned int width, height;
        bool vsync;
    };
    WindowData m_data;
};
