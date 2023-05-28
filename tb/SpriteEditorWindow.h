#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

namespace tb
{

class SpriteEditorWindow : public tb::ImGuiWindow
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

    void onOpen();
    void onClose();

    void loadData();
    void saveData();

    void draw();

    tb::SpriteID_t getSelectedSpriteID();
    void setSelectedSpriteID(tb::SpriteID_t spriteID);

private:

    bool m_isOpen = false;

    tb::SpriteData::DataList* m_spriteDataList = nullptr;

    tb::SpriteData::Data* m_spriteData = nullptr;

    tb::SpriteData::Data m_spriteDataClipboard;

    tb::SpriteData::Data m_spriteDataBackup;

    tb::SpriteID_t m_selectedSpriteID = 1;

    tb::SpriteFlag m_highlightSpriteFlag = tb::SpriteFlag::Null;

    const ImVec2 m_buttonSize = ImVec2(105.0f, 29.0f);

};

}

namespace
{
    inline tb::SpriteEditorWindow& g_SpriteEditorWindow = tb::SpriteEditorWindow::getInstance();
}
