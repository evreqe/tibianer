#include "tb/HotkeysWindow.h"

namespace tb
{

HotkeysWindow::HotkeysWindow()
{
    //
}

HotkeysWindow::~HotkeysWindow()
{
    //
}

void HotkeysWindow::onOpen()
{
    loadData();

    m_isOpen = true;
}

void HotkeysWindow::onClose()
{
    m_isOpen = false;
}

void HotkeysWindow::loadData()
{
    m_hotkeysData = *g_HotkeysData.getData();
}

void HotkeysWindow::saveData()
{
    g_HotkeysData.setData(m_hotkeysData);

    g_HotkeysData.save();
}

void HotkeysWindow::draw()
{
    if (m_isOpen == false)
    {
        onOpen();
    }

    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Hotkeys##HotkeysWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted("F1: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF1", &m_hotkeysData.F1);

    ImGui::TextUnformatted("F2: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF2", &m_hotkeysData.F2);

    ImGui::TextUnformatted("F3: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF3", &m_hotkeysData.F3);

    ImGui::TextUnformatted("F4: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF4", &m_hotkeysData.F4);

    ImGui::TextUnformatted("F5: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF5", &m_hotkeysData.F5);

    ImGui::TextUnformatted("F6: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF6", &m_hotkeysData.F6);

    ImGui::TextUnformatted("F7: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF7", &m_hotkeysData.F7);

    ImGui::TextUnformatted("F8: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF8", &m_hotkeysData.F8);

    ImGui::TextUnformatted("F9: ");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF9", &m_hotkeysData.F9);

    ImGui::TextUnformatted("F10:");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF10", &m_hotkeysData.F10);

    ImGui::TextUnformatted("F11:");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF11", &m_hotkeysData.F11);

    ImGui::TextUnformatted("F12:");
    ImGui::SameLine();
    ImGui::InputText("##HotkeysWindowInputTextF12", &m_hotkeysData.F12);

    ImGui::Separator();

    if (ImGui::Button("OK##HotkeysWindowButtonOK", m_buttonSize))
    {
        saveData();

        onClose();

        setIsVisible(false);
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel##HotkeysWindowButtonCancel", m_buttonSize))
    {
        onClose();

        setIsVisible(false);
    }

    ImGui::End();
}

}
