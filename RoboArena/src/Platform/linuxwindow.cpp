#include "rapch.h"
#include "linuxwindow.h"

static bool s_GLFWinitialized = false;

Window *Window::create(const WindowProps &props)
{
    return new LinuxWindow(props);
}

LinuxWindow::LinuxWindow(const WindowProps &props)
{
    init(props);
}

LinuxWindow::~LinuxWindow()
{
    shutdown();
}

void LinuxWindow::init(const WindowProps &props)
{
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;

    INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

    if (!s_GLFWinitialized)
    {
        // TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        RA_ASSERT(success, "Could not intialize GLFW!");

        s_GLFWinitialized = true;
    }

    m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);
    set_vsync(true);
}

void LinuxWindow::shutdown()
{
    glfwDestroyWindow(m_window);
}

void LinuxWindow::on_update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void LinuxWindow::set_vsync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_data.vsync = enabled;
}

bool LinuxWindow::is_vsync() const
{
    return m_data.vsync;
}
