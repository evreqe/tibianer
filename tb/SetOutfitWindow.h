#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

#include "tb/Game.h"

#include "tb/Creature.h"

namespace tb
{

    class SetOutfitWindow : public Window
    {

    public:

        SetOutfitWindow();
        ~SetOutfitWindow();

        static SetOutfitWindow& getInstance()
        {
            static SetOutfitWindow instance;
            return instance;
        }

    private:

        SetOutfitWindow(const SetOutfitWindow&) = delete;
        SetOutfitWindow(SetOutfitWindow&&) = delete;
        SetOutfitWindow& operator=(const SetOutfitWindow&) = delete;
        SetOutfitWindow& operator=(SetOutfitWindow&&) = delete;

    public:

        void onOpen();
        void onClose();

        void draw();

    private:

        bool m_isOpen = false;

        tb::Creature::Ptr m_creature = nullptr;

        const ImVec2 m_buttonSize = ImVec2(123.0f, 29.0f);

    };

}

namespace
{
    inline tb::SetOutfitWindow& g_SetOutfitWindow = tb::SetOutfitWindow::getInstance();
}
