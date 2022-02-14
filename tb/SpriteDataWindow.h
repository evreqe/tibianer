#pragma once

#include "tb/SpriteData.h"
#include "tb/Sprite.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class SpriteDataWindow
    {

    public:

        SpriteDataWindow();

        void draw();

        void setSpriteData(tb::SpriteData& spriteData);

        bool getIsVisible();
        void setIsVisible(bool b);
        void toggleIsVisible();

    private:

        bool m_isVisible = false;

        tb::SpriteData* m_spriteData = nullptr;
    };

}
