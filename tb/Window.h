#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class Window
    {

    public:

        Window();
        ~Window();

        bool* getIsVisible();
        void setIsVisible(bool b);
        void toggleIsVisible();

        void centerAndResizeOnFirstUseEver();

    private:

        bool m_isVisible = false;
    };

}
