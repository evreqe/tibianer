#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/SpriteData.h"
#include "tb/OptionsData.h"
#include "tb/Sprite.h"
#include "tb/Game.h"
#include "tb/Creature.h"

namespace tb
{

    class SetOutfitWindow : public tb::ImGuiWindow
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

        void load();
        void save();

        void setOutfitSprites();

        void draw();

    private:

        bool m_isOpen = false;

        tb::Creature::Ptr m_creature = nullptr;

        tb::Creature::Outfit_t* m_creatureOutfit = nullptr;

        const ImVec2 m_buttonSize = ImVec2(123.0f, 29.0f);

    };

}

namespace
{
    inline tb::SetOutfitWindow& g_SetOutfitWindow = tb::SetOutfitWindow::getInstance();
}
