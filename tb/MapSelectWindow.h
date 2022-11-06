#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

#include "tb/Log.h"

#include "tb/MapData.h"

#include "tb/Game.h"

namespace tb
{

    class MapSelectWindow : public Window
    {

    public:

        MapSelectWindow();
        ~MapSelectWindow();

        static MapSelectWindow& getInstance()
        {
            static MapSelectWindow instance;
            return instance;
        }

    private:

        MapSelectWindow(const MapSelectWindow&) = delete;
        MapSelectWindow(MapSelectWindow&&) = delete;
        MapSelectWindow& operator=(const MapSelectWindow&) = delete;
        MapSelectWindow& operator=(MapSelectWindow&&) = delete;

    public:

        void draw();

    private:

        //

        const ImVec2 m_buttonSize = ImVec2(105.0f, 29.0f);

    };

}

namespace
{
    inline tb::MapSelectWindow& g_MapSelectWindow = tb::MapSelectWindow::getInstance();
}
