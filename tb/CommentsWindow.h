#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

namespace tb
{

    class CommentsWindow : public Window
    {

    public:

        CommentsWindow();
        ~CommentsWindow();

        static CommentsWindow& getInstance()
        {
            static CommentsWindow instance;
            return instance;
        }

    private:

        CommentsWindow(const CommentsWindow&) = delete;
        CommentsWindow(CommentsWindow&&) = delete;
        CommentsWindow& operator=(const CommentsWindow&) = delete;
        CommentsWindow& operator=(CommentsWindow&&) = delete;

    public:

        void draw();

    private:

        const char* m_displayText =
"Feel free to tell us, what you think of this game.\n\
Please report any bugs you detect.\n\
You are also welcome to make suggestions or to tell\n\
any problems you have.";

        std::string m_inputText;

        const ImVec2 m_inputTextSize = ImVec2(306.0f, 81.0f);

        const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

    };

}

namespace
{
    inline tb::CommentsWindow& g_CommentsWindow = tb::CommentsWindow::getInstance();
}
