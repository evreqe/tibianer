#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/Constants.h"

#include "tb/OverlayWindow.h"
#include "tb/LogWindow.h"
#include "tb/SpriteDataWindow.h"
#include "tb/SpriteEditorWindow.h"
#include "tb/OptionsWindow.h"
#include "tb/HotkeysWindow.h"
#include "tb/EnterGameWindow.h"
#include "tb/SetOutfitWindow.h"
#include "tb/CommentsWindow.h"
#include "tb/MessageOfTheDayWindow.h"
#include "tb/ConnectionWindow.h"
#include "tb/ControlsWindow.h"
#include "tb/TipsAndTricksWindow.h"
#include "tb/AboutTibiaWindow.h"
#include "tb/AboutTibianerWindow.h"

#include "tb/RenderWindow.h"
#include "tb/Game.h"

namespace tb
{

class MenuBar : public tb::ImGuiWindow
{

public:

    MenuBar();
    ~MenuBar();

    static MenuBar& getInstance()
    {
        static MenuBar instance;
        return instance;
    }

private:

    MenuBar(const MenuBar&) = delete;
    MenuBar(MenuBar&&) = delete;
    MenuBar& operator=(const MenuBar&) = delete;
    MenuBar& operator=(MenuBar&&) = delete;

public:

    void draw();

    float getHeight();
    void setHeight(float height);

private:

    const float m_heightDefault = 19.0f;

    float m_height = m_heightDefault;

    const float m_helpMenuAlignmentOffset = 44.0f;
};

}

namespace
{
    inline tb::MenuBar& g_MenuBar = tb::MenuBar::getInstance();
}
