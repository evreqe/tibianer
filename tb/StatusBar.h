#pragma once

#include <string>
#include <string_view>

#include "imgui.h"
#include "imgui-SFML.h"

#include "tb/Constants.h"

#include "tb/Game.h"

namespace tb
{
    class Game;

    class StatusBar
    {

    public:

        StatusBar();

        void draw(tb::Game* game);

        float getHeight();
        void setHeight(float height);

        std::string_view getText();
        void setText(const std::string& text);

        bool getIsVisible();
        void setIsVisible(bool b);
        void toggleIsVisible();

    private:

        tb::Game* m_game;

        bool m_isVisible = true;

        const float m_heightDefault = 19.0f;

        float m_height = m_heightDefault;

        const std::string m_TextDefault = "Welcome to Tibianer!";

        std::string m_text = m_TextDefault;
    };

}
