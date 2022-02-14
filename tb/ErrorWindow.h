#pragma once

#include <string>

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class ErrorWindow
    {

    public:

        ErrorWindow();

        void draw();

        void setTitleText(const std::string& text);
        void setErrorText(const std::string& text);

        bool getIsVisible();
        void setIsVisible(bool b);
        void toggleIsVisible();

    private:

        bool m_isVisible = false;

        std::string m_titleText = "Error##ErrorWindow";

        std::string m_errorText;
    };

}
