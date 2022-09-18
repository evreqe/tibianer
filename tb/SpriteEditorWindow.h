#pragma once

#include "common.h"

#include "tb/Window.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class SpriteEditorWindow : public tb::Window
    {

    public:

        SpriteEditorWindow();
        ~SpriteEditorWindow();
        SpriteEditorWindow(const SpriteEditorWindow&) = delete;
        SpriteEditorWindow(SpriteEditorWindow&&) = delete;
        SpriteEditorWindow& operator=(const SpriteEditorWindow&) = delete;
        SpriteEditorWindow& operator=(SpriteEditorWindow&&) = delete;

        static SpriteEditorWindow& getInstance()
        {
            static SpriteEditorWindow spriteEditorWindow;
            return spriteEditorWindow;
        }

        void resetInputs();
        void updateInputsFromSpriteData(tb::SpriteID_t spriteID);
        void updateSpriteDataFromInputs(tb::SpriteID_t spriteID);

        void draw();

        tb::SpriteID_t getSelectedSpriteID();
        void setSelectedSpriteID(tb::SpriteID_t id);

    private:

        tb::SpriteID_t m_selectedSpriteID = 1;

        uint32_t m_highlightComboSpriteFlag = 0;

        char m_inputName[128 + 1] = {0};
        char m_inputArticle[8 + 1] = {0};
        float m_inputWeight = 0.0f;
        int m_inputTileWidth = 1;
        int m_inputTileHeight = 1;
    };

}

namespace
{
    tb::SpriteEditorWindow& g_SpriteEditorWindow = tb::SpriteEditorWindow::getInstance();
}
