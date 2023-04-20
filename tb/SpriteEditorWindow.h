#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
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

    const ImVec2 m_buttonSize = ImVec2(105.0f, 29.0f);

    std::string m_inputName;
    std::string m_inputArticle;
    std::string m_inputDescription;

    int m_inputTileWidth = 1;
    int m_inputTileHeight = 1;

    float m_inputWeight = 0.0f;
    float m_inputLightRadius = 0.0f;

};

}

namespace
{
    inline tb::SpriteEditorWindow& g_SpriteEditorWindow = tb::SpriteEditorWindow::getInstance();
}
