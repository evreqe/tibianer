#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

namespace tb
{

    class ConnectionWindow : public tb::ImGuiWindow
    {

    public:

        ConnectionWindow();
        ~ConnectionWindow();

        static ConnectionWindow& getInstance()
        {
            static ConnectionWindow instance;
            return instance;
        }

    private:

        ConnectionWindow(const ConnectionWindow&) = delete;
        ConnectionWindow(ConnectionWindow&&) = delete;
        ConnectionWindow& operator=(const ConnectionWindow&) = delete;
        ConnectionWindow& operator=(ConnectionWindow&&) = delete;

    public:

        void draw();

    private:

        const char* m_displayText =
"- Verify the address of our server in \"File | Preferences\".\n\
  You can get the right data from our homepage\n\
  \"http://www.tibia.org\".\n\
- After creating a character at the homepage\n\
  select \"Enter Game\" to join the game.\n\
- The message in the status line will give you further\n\
  information.\n\
- If you can establish the connection you will either\n\
  enter the game or the server will refuse the entrance\n\
  for the reason given in a message box.";

        const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

    };

}

namespace
{
    inline tb::ConnectionWindow& g_ConnectionWindow = tb::ConnectionWindow::getInstance();
}
