#pragma once

#include <format>
#include <string>

#include "tb/SpriteData.h"
#include "tb/Sprite.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class SpriteEditorWindow
    {

    public:

        SpriteEditorWindow();

        void draw();

        void setSpriteData(tb::SpriteData& spriteData);

        tb::SpriteID_t getSelectedSpriteID();
        void setSelectedSpriteID(tb::SpriteID_t id);

        bool getIsVisible();

        void setIsVisible(bool b);

        void toggleIsVisible();

    private:

        bool m_isVisible = false;

        tb::SpriteData* m_spriteData = nullptr;

        tb::SpriteID_t m_selectedSpriteID = 1;

        uint32_t m_highlightComboSpriteFlag = 0;
    };

}
