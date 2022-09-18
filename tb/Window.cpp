#include "tb/Window.h"

namespace tb
{

Window::Window()
{
    //
}

Window::~Window()
{
    //
}

bool* Window::getIsVisible()
{
    return &m_isVisible;
}

void Window::setIsVisible(bool b)
{
    m_isVisible = b;
}

void Window::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

}
