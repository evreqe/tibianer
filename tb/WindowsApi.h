#pragma once

#include <SFML/Window.hpp>

namespace tb::WindowsAPI
{

void ShowWindow(sf::WindowHandle windowHandle);
void HideWindow(sf::WindowHandle windowHandle);
void MinimizeWindow(sf::WindowHandle windowHandle);
void MaximizeWindow(sf::WindowHandle windowHandle);
void NormalizeWindow(sf::WindowHandle windowHandle);
void RestoreWindow(sf::WindowHandle windowHandle);

bool IsWindowMinimized(sf::WindowHandle windowHandle);
bool IsWindowMaximized(sf::WindowHandle windowHandle);

}
