#include "common.h"

#include "tb/WindowsApi.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

namespace tb
{

namespace WindowsApi
{

void ShowWindow(sf::WindowHandle windowHandle)
{
    ::ShowWindow(windowHandle, SW_SHOW);
}

void HideWindow(sf::WindowHandle windowHandle)
{
    ::ShowWindow(windowHandle, SW_HIDE);
}

void MinimizeWindow(sf::WindowHandle windowHandle)
{
    ::ShowWindow(windowHandle, SW_MINIMIZE);
}

void MaximizeWindow(sf::WindowHandle windowHandle)
{
    ::ShowWindow(windowHandle, SW_MAXIMIZE);
}

void NormalizeWindow(sf::WindowHandle windowHandle)
{
    ::ShowWindow(windowHandle, SW_NORMAL);
}

void RestoreWindow(sf::WindowHandle windowHandle)
{
    ::ShowWindow(windowHandle, SW_RESTORE);
}

bool IsWindowMinimized(sf::WindowHandle windowHandle)
{
    return ::IsIconic(windowHandle) == TRUE;
}

bool IsWindowMaximized(sf::WindowHandle windowHandle)
{
    return ::IsZoomed(windowHandle) == TRUE;
}

}

}
