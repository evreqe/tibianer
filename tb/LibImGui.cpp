#include "tb/LibImGui.h"

namespace tb
{

namespace LibImGui
{

bool isActive()
{
    auto io = ImGui::GetIO();

    if (io.WantCaptureKeyboard == true || io.WantCaptureMouse == true)
    {
        return true;
    }

    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == true)
    {
        return true;
    }

    if (ImGui::IsAnyItemHovered() == true)
    {
        return true;
    }

    return false;
}

void drawRectangleAtCurrentItem(const ImColor& color)
{
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();

    ImGui::GetWindowDrawList()->AddRect(min, max, color);
}

void drawTextAtCurrentItem(const std::string& text, const ImColor& color)
{
    ImVec2 min = ImGui::GetItemRectMin();

    ImGui::GetWindowDrawList()->AddText(min, color, text.c_str());
}

void drawTextWithShadowAtCurrentItem(const std::string& text, const ImColor& color)
{
    ImVec2 min = ImGui::GetItemRectMin();

    const char* textAsCString = text.c_str();

    ImGui::GetWindowDrawList()->AddText(ImVec2(min.x + 1, min.y + 1), ImColor(0, 0, 0), textAsCString);
    ImGui::GetWindowDrawList()->AddText(min, color, textAsCString);
}

bool scrollWindowWithMiddleMouseButton()
{
    ImGuiIO io = ImGui::GetIO();

    ::ImGuiWindow* window = ImGui::GetCurrentWindow();

    if (window->Rect().Contains(io.MousePos) == false)
    {
        return false;
    }

    // check if middle mouse button held down
    if (io.MouseDown[2] == false)
    {
        return false;
    }

    ImVec2 mouseDelta = io.MouseDelta;

    mouseDelta.x = -mouseDelta.x;
    mouseDelta.y = -mouseDelta.y;

    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);

    if (mouseDelta.x != 0.0f)
    {
        ImGui::SetScrollX(window, window->Scroll.x + mouseDelta.x);
    }

    if (mouseDelta.y != 0.0f)
    {
        ImGui::SetScrollY(window, window->Scroll.y + mouseDelta.y);
    }

    return true;
}

}

}
