#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "tb/LogWindow.h"
#include "tb/SpriteDataWindow.h"
#include "tb/SpriteEditorWindow.h"

#include "tb/Game.h"

namespace tb
{
    class Game;

    class MenuBar
    {

    public:

        MenuBar();
        ~MenuBar();
        MenuBar(const MenuBar&) = delete;
        MenuBar(MenuBar&&) = delete;
        MenuBar& operator=(const MenuBar&) = delete;
        MenuBar& operator=(MenuBar&&) = delete;

        static MenuBar& getInstance()
        {
            static MenuBar menuBar;
            return menuBar;
        }

        void draw();

        float getHeight();
        void setHeight(float height);

        bool getIsVisible();
        void setIsVisible(bool b);
        void toggleIsVisible();

    private:

        bool m_isVisible = true;

        const float m_heightDefault = 19.0f;

        const float m_helpMenuAlignmentOffset = 44.0f;

        float m_height = m_heightDefault;
    };
}

namespace
{
    tb::MenuBar& g_MenuBar = tb::MenuBar::getInstance();
}
