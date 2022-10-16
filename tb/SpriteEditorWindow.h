#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

namespace tb
{

class SpriteEditorWindow : public tb::Window
{

public:

    SpriteEditorWindow();
    ~SpriteEditorWindow();

    static SpriteEditorWindow& getInstance()
    {
        static SpriteEditorWindow instance;
        return instance;
    }

private:

    SpriteEditorWindow(const SpriteEditorWindow&) = delete;
    SpriteEditorWindow(SpriteEditorWindow&&) = delete;
    SpriteEditorWindow& operator=(const SpriteEditorWindow&) = delete;
    SpriteEditorWindow& operator=(SpriteEditorWindow&&) = delete;

public:

    void resetInputs();
    void updateInputsFromSpriteData(tb::SpriteID_t spriteID);
    void updateSpriteDataFromInputs(tb::SpriteID_t spriteID);

    void draw();

    tb::SpriteID_t getSelectedSpriteID();
    void setSelectedSpriteID(tb::SpriteID_t spriteID);

private:

    tb::SpriteID_t m_selectedSpriteID = 1;

    tb::SpriteFlag m_highlightComboSpriteFlag = tb::SpriteFlag::Null;

    char m_inputName[128 + 1] = {0};
    char m_inputArticle[8 + 1] = {0};
    float m_inputWeight = 0.0f;
    int m_inputTileWidth = 1;
    int m_inputTileHeight = 1;
};

}

namespace
{
    inline tb::SpriteEditorWindow& g_SpriteEditorWindow = tb::SpriteEditorWindow::getInstance();
}
