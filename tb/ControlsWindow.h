#pragma once

#include "common.h"

#include "tb/Window.h"

namespace tb
{

    class ControlsWindow : public Window
    {

    public:

        ControlsWindow();
        ~ControlsWindow();

        static ControlsWindow& getInstance()
        {
            static ControlsWindow instance;
            return instance;
        }

    private:

        ControlsWindow(const ControlsWindow&) = delete;
        ControlsWindow(ControlsWindow&&) = delete;
        ControlsWindow& operator=(const ControlsWindow&) = delete;
        ControlsWindow& operator=(ControlsWindow&&) = delete;

    public:

        void draw();

    private:

        const char* m_displayText =
"- Move your player by clicking with the left button on\n\
  the map or use the cursor keys.\n\
- Move objects by \"Drag & Drop\".\n\
- Look at objects by clicking on them with both buttons.\n\
- Use objects by clicking with the right button on them.\n\
  If a crosshair appears, click left on the destination object.\n\
- Say something by typing in the text ending with ENTER.\n\
- To attack monsters click at the button with the swords.\n\
  A list of opponents will appear where you can choose\n\
  your target. Your character will attack automatically\n\
  as soon as the monster is in range.\n\
\n\
For more information refer to our homepage.";

        const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

    };

}

namespace
{
    inline tb::ControlsWindow& g_ControlsWindow = tb::ControlsWindow::getInstance();
}
