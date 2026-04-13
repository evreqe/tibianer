#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"

#include "tb/LibSFML.h"
#include "imgui-SFML.h"

namespace tb::LibIMGUI
{

inline const std::uint8_t InputScalarU8Step1 = 1;
inline const std::uint16_t InputScalarU16Step1 = 1;
inline const std::uint32_t InputScalarU32Step1 = 1;
inline const std::uint64_t InputScalarU64Step1 = 1;

inline const ::ImVec2 PopupButtonSize = ImVec2(105.0f, 29.0f);

bool isActive();
void drawRectangleAtCurrentItem(const ImColor& color);
void drawTextAtCurrentItem(const std::string& text, const ImColor& color);
void drawTextWithShadowAtCurrentItem(const std::string& text, const ImColor& color);
bool scrollWindowWithMiddleMouseButton();

}

