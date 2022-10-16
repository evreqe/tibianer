#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

namespace tb
{

class SpriteDataWindow : public tb::Window
{

public:

    SpriteDataWindow();
    ~SpriteDataWindow();

    static SpriteDataWindow& getInstance()
    {
        static SpriteDataWindow instance;
        return instance;
    }

private:

    SpriteDataWindow(const SpriteDataWindow&) = delete;
    SpriteDataWindow(SpriteDataWindow&&) = delete;
    SpriteDataWindow& operator=(const SpriteDataWindow&) = delete;
    SpriteDataWindow& operator=(SpriteDataWindow&&) = delete;

public:

    void draw();

private:

    //
};

}

namespace
{
    inline tb::SpriteDataWindow& g_SpriteDataWindow = tb::SpriteDataWindow::getInstance();
}
