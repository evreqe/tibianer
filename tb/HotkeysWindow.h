#pragma once

#include "common.h"

#include "tb/Window.h"

#include "tb/HotkeysData.h"

namespace tb
{

class HotkeysWindow : public Window
{

public:

    HotkeysWindow();
    ~HotkeysWindow();

    static HotkeysWindow& getInstance()
    {
        static HotkeysWindow instance;
        return instance;
    }

private:

    HotkeysWindow(const HotkeysWindow&) = delete;
    HotkeysWindow(HotkeysWindow&&) = delete;
    HotkeysWindow& operator=(const HotkeysWindow&) = delete;
    HotkeysWindow& operator=(HotkeysWindow&&) = delete;

public:

    void onOpen();
    void onClose();

    void loadData();
    void saveData();

    void draw();

private:

    bool m_isOpen = false;

    tb::HotkeysData::Data m_hotkeysData;

    const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

};

}

namespace
{
    inline tb::HotkeysWindow& g_HotkeysWindow = tb::HotkeysWindow::getInstance();
}
