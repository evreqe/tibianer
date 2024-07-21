#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

namespace tb
{

class TipsAndTricksWindow : public tb::ImGuiWindow
{

public:

    TipsAndTricksWindow();
    ~TipsAndTricksWindow();

    static TipsAndTricksWindow& getInstance()
    {
        static TipsAndTricksWindow instance;
        return instance;
    }

private:

    TipsAndTricksWindow(const TipsAndTricksWindow&) = delete;
    TipsAndTricksWindow(TipsAndTricksWindow&&) = delete;
    TipsAndTricksWindow& operator=(const TipsAndTricksWindow&) = delete;
    TipsAndTricksWindow& operator=(TipsAndTricksWindow&&) = delete;

public:

    void draw();

private:

    const char* m_displayText =
"- When fighting against several monsters try to keep your\n\
  back free, so that only one of them can hit you.\n\
- A day in Tibia lasts 60 minutes. Make sure that you have\n\
  a light on you when night falls.\n\
- To read a scroll you must stand directly beside it.\n\
- If you want to talk to a person, say Obi, you should\n\
  address him with \"Hello, Obi.\".\n\
  Some sentences Obi will react to:\n\
  \"What is your name?\"\n\
  \"What is your job?\"\n\
  \"What do you sell?\"\n\
  \"I want to buy a short sword.\"\n\
  \"What time is it?\"";

    const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

};

}

namespace
{
    inline tb::TipsAndTricksWindow& g_TipsAndTricksWindow = tb::TipsAndTricksWindow::getInstance();
}
