#pragma once

namespace tb
{
    class Game;

    class StatusBar
    {

    public:

        StatusBar()
        {
            //
        }

/*
        void draw(tb::Game* game)
        {
            if (m_isVisible == false)
            {
                return;
            }

            ImGui::SetNextWindowPos(ImVec2(0.0f, game->getRenderWindow()->getSize().y - m_height));
            ImGui::SetNextWindowSize(ImVec2(game->getRenderWindow()->getSize().x, m_height));

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 2.0f));

            bool isVisible = true;
            ImGui::Begin("##StatusBar", &isVisible, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::PopStyleVar(2);

            ImGui::SetCursorPosX(8.0f);

            ImGui::Text(m_text.c_str());

            if (game->getGameState() == tb::GameState::InGame)
            {
                ImGui::SameLine();

                std::string bottomRightText = "H 0, M 0, C 0, A 0";

                ImVec2 bottomRightTextSize = ImGui::CalcTextSize(bottomRightText.c_str());

                // apply right-justify alignment
                ImGui::SetCursorPosX(game->getRenderWindow()->getSize().x - bottomRightTextSize.x - 8.0f);

                ImGui::Text(bottomRightText.c_str());
            }

            ImGui::End();
        }
*/

        float getHeight()
        {
            if (m_isVisible == false)
            {
                return 0.0f;
            }

            return m_height;
        }

        void setHeight(float height)
        {
            m_height = height;
        }

        std::string_view getText()
        {
            return m_text;
        }

        void setText(const std::string& text)
        {
            m_text = text;
        }

        bool getIsVisible()
        {
            return m_isVisible;
        }

        void setIsVisible(bool b)
        {
            m_isVisible = b;
        }

        void toggleIsVisible()
        {
            m_isVisible = !m_isVisible;
        }

    private:

        bool m_isVisible = true;

        const float m_heightDefault = 19.0f;

        float m_height = m_heightDefault;

        const std::string m_TextDefault = "Welcome to Tibianer!";

        std::string m_text = m_TextDefault;
    };

}
