#pragma once

namespace tb
{

    class ErrorWindow
    {

    public:

        ErrorWindow()
        {
            //
        }

        void draw()
        {
            ImGui::Begin(m_titleText.c_str(), &m_isVisible, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Text(m_errorText.c_str());

            ImGui::End();
        }

        void setTitleText(const std::string& text)
        {
            m_titleText = text;
        }

        void setErrorText(const std::string& text)
        {
            m_errorText = text;
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

        bool m_isVisible = false;

        std::string m_titleText = "Error##ErrorWindow";

        std::string m_errorText;
    };

}
