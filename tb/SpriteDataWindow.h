#pragma once

#include "common.h"

#include "tb/Window.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class SpriteDataWindow : public tb::Window
    {

    public:

        SpriteDataWindow();
        ~SpriteDataWindow();
        SpriteDataWindow(const SpriteDataWindow&) = delete;
        SpriteDataWindow(SpriteDataWindow&&) = delete;
        SpriteDataWindow& operator=(const SpriteDataWindow&) = delete;
        SpriteDataWindow& operator=(SpriteDataWindow&&) = delete;

        static SpriteDataWindow& getInstance()
        {
            static SpriteDataWindow spriteDataWindow;
            return spriteDataWindow;
        }

        void draw();

    private:

        //
    };

}

namespace
{
    tb::SpriteDataWindow& g_SpriteDataWindow = tb::SpriteDataWindow::getInstance();
}
