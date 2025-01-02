#include "tb/SetOutfitWindow.h"

namespace tb
{

SetOutfitWindow::SetOutfitWindow()
{
    //
}

SetOutfitWindow::~SetOutfitWindow()
{
    //
}

void SetOutfitWindow::onOpen()
{
    load();

    m_isOpen = true;
}

void SetOutfitWindow::onClose()
{
    m_creature = nullptr;

    m_creatureOutfit = nullptr;

    m_isOpen = false;
}

void SetOutfitWindow::load()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    m_creature = std::make_shared<tb::Creature>(*player);

    m_creatureOutfit = m_creature->getOutfit();
}

void SetOutfitWindow::save()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    player->setOutfit(m_creatureOutfit->Head, m_creatureOutfit->Body, m_creatureOutfit->Legs, m_creatureOutfit->Feet);

    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    optionsData->PlayerOutfitHead = m_creatureOutfit->Head;
    optionsData->PlayerOutfitBody = m_creatureOutfit->Body;
    optionsData->PlayerOutfitLegs = m_creatureOutfit->Legs;
    optionsData->PlayerOutfitFeet = m_creatureOutfit->Feet;

    g_OptionsData.save();
}

void SetOutfitWindow::setOutfitSprites()
{
    m_creature->setOutfitSprites(m_creatureOutfit->Head, m_creatureOutfit->Body, m_creatureOutfit->Legs, m_creatureOutfit->Feet);
}

void SetOutfitWindow::draw()
{
    if (m_isOpen == false)
    {
        onOpen();
    }

    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Set Your Outfit##SetOutfitWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    if (m_creature == nullptr)
    {
        ImGui::TextUnformatted("ERROR: m_creature == nullptr");
        ImGui::End();
        return;
    }

    if (m_creatureOutfit == nullptr)
    {
        ImGui::TextUnformatted("ERROR: m_creatureOutfit == nullptr");
        ImGui::End();
        return;
    }

    tb::Creature::OutfitSpriteList* creatureOutfitSpriteList = m_creature->getOutfitSpriteList();

    tb::Sprite* spriteHead = &creatureOutfitSpriteList->at(tb::OutfitIndex::Head).at(magic_enum::enum_integer(tb::Direction::Down));
    tb::Sprite* spriteBody = &creatureOutfitSpriteList->at(tb::OutfitIndex::Body).at(magic_enum::enum_integer(tb::Direction::Down));
    tb::Sprite* spriteLegs = &creatureOutfitSpriteList->at(tb::OutfitIndex::Legs).at(magic_enum::enum_integer(tb::Direction::Down));
    tb::Sprite* spriteFeet = &creatureOutfitSpriteList->at(tb::OutfitIndex::Feet).at(magic_enum::enum_integer(tb::Direction::Down));

    if (ImGui::BeginTable("##SetOutfitWindowTable", 2, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddRectFilled(cursorScreenPos, ImVec2(cursorScreenPos.x + 64.0f, cursorScreenPos.y + 64.0f), IM_COL32(204, 204, 204, 255));

        tb::Sprite spriteOutfit(tb::Textures::Sprites);

        spriteOutfit.setID(spriteFeet->getID());
        spriteOutfit.setScale(sf::Vector2f(2.0f, 2.0f));

        ImGui::SetCursorScreenPos(cursorScreenPos);
        ImGui::Image(spriteOutfit);

        spriteOutfit.setID(spriteLegs->getID());
        spriteOutfit.setScale(sf::Vector2f(2.0f, 2.0f));

        ImGui::SetCursorScreenPos(cursorScreenPos);
        ImGui::Image(spriteOutfit);

        spriteOutfit.setID(spriteBody->getID());
        spriteOutfit.setScale(sf::Vector2f(2.0f, 2.0f));

        ImGui::SetCursorScreenPos(cursorScreenPos);
        ImGui::Image(spriteOutfit);

        spriteOutfit.setID(spriteHead->getID());
        spriteOutfit.setScale(sf::Vector2f(2.0f, 2.0f));

        ImGui::SetCursorScreenPos(cursorScreenPos);
        ImGui::Image(spriteOutfit);

        ImGui::TableSetColumnIndex(1);

        if (ImGui::ArrowButton("##SetOutfitWindowButtonHeadLeft", ImGuiDir_Left))
        {
            if (m_creatureOutfit->Head == 0)
            {
                m_creatureOutfit->Head = tb::Constants::NumOutfitSpriteIDListHead - 1;
            }
            else
            {
                m_creatureOutfit->Head -= 1;
            }

            setOutfitSprites();
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Head ");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonHeadRight", ImGuiDir_Right))
        {
            if (m_creatureOutfit->Head == tb::Constants::NumOutfitSpriteIDListHead - 1)
            {
                m_creatureOutfit->Head = 0;
            }
            else
            {
                m_creatureOutfit->Head += 1;
            }

            setOutfitSprites();
        }

        if (ImGui::ArrowButton("##SetOutfitWindowButtonBodyLeft", ImGuiDir_Left))
        {
            if (m_creatureOutfit->Body == 0)
            {
                m_creatureOutfit->Body = tb::Constants::NumOutfitSpriteIDListBody - 1;
            }
            else
            {
                m_creatureOutfit->Body -= 1;
            }

            setOutfitSprites();
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Body ");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonBodyRight", ImGuiDir_Right))
        {
            if (m_creatureOutfit->Body == tb::Constants::NumOutfitSpriteIDListBody - 1)
            {
                m_creatureOutfit->Body = 0;
            }
            else
            {
                m_creatureOutfit->Body += 1;
            }

            setOutfitSprites();
        }

        if (ImGui::ArrowButton("##SetOutfitWindowButtonLegsLeft", ImGuiDir_Left))
        {
            if (m_creatureOutfit->Legs == 0)
            {
                m_creatureOutfit->Legs = tb::Constants::NumOutfitSpriteIDListLegs - 1;
            }
            else
            {
                m_creatureOutfit->Legs -= 1;
            }

            setOutfitSprites();
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Legs ");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonLegsRight", ImGuiDir_Right))
        {
            if (m_creatureOutfit->Legs == tb::Constants::NumOutfitSpriteIDListLegs - 1)
            {
                m_creatureOutfit->Legs = 0;
            }
            else
            {
                m_creatureOutfit->Legs += 1;
            }

            setOutfitSprites();
        }

        if (ImGui::ArrowButton("##SetOutfitWindowButtonFeetLeft", ImGuiDir_Left))
        {
            if (m_creatureOutfit->Feet == 0)
            {
                m_creatureOutfit->Feet = tb::Constants::NumOutfitSpriteIDListFeet - 1;
            }
            else
            {
                m_creatureOutfit->Feet -= 1;
            }

            setOutfitSprites();
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Shoes");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonFeetRight", ImGuiDir_Right))
        {
            if (m_creatureOutfit->Feet == tb::Constants::NumOutfitSpriteIDListFeet - 1)
            {
                m_creatureOutfit->Feet = 0;
            }
            else
            {
                m_creatureOutfit->Feet += 1;
            }

            setOutfitSprites();
        }

        ImGui::EndTable();
    }

    ImGui::Separator();

    if (ImGui::Button("Set Outfit##SetOutfitWindowButtonSetOutfit", m_buttonSize))
    {
        save();

        onClose();

        setIsVisible(false);
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel##SetOutfitWindowButtonCancel", m_buttonSize))
    {
        onClose();

        setIsVisible(false);
    }

    ImGui::End();
}

}
