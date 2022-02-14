#pragma once

#include <string>

#include "imgui.h"
#include "imgui-SFML.h"

#include "tb/Game.h"

namespace tb
{
    class Game;

    class MenuBar
    {

    public:

        MenuBar();

        void draw(tb::Game* game);

        float getHeight();
        void setHeight(float height);

        bool getIsVisible();
        void setIsVisible(bool b);
        void toggleIsVisible();

    private:

        tb::Game* m_game;

        bool m_isVisible = true;

        const float m_heightDefault = 19.0f;

        const float m_helpMenuAlignmentOffset = 44.0f;

        float m_height = m_heightDefault;
    };

}
