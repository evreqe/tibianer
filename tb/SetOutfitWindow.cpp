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
    tb::Creature::Ptr player = g_Game.getPlayer();

    m_creature = std::make_shared<tb::Creature>(*player);

    m_isOpen = true;
}

void SetOutfitWindow::onClose()
{
    m_creature = nullptr;

    m_isOpen = false;
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

    if (ImGui::BeginTable("##SetOutfitWindowTable", 2, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        tb::Creature::Outfit_t* creatureOutfit = m_creature->getOutfit();

        tb::Creature::OutfitSpriteList* creatureOutfitSpriteList = m_creature->getOutfitSpriteList();

        tb::Sprite* spriteHead = &creatureOutfitSpriteList->at(tb::OutfitIndex::Head).at(magic_enum::enum_integer(tb::Direction::Down));
        tb::Sprite* spriteBody = &creatureOutfitSpriteList->at(tb::OutfitIndex::Body).at(magic_enum::enum_integer(tb::Direction::Down));
        tb::Sprite* spriteLegs = &creatureOutfitSpriteList->at(tb::OutfitIndex::Legs).at(magic_enum::enum_integer(tb::Direction::Down));
        tb::Sprite* spriteFeet = &creatureOutfitSpriteList->at(tb::OutfitIndex::Feet).at(magic_enum::enum_integer(tb::Direction::Down));

        ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddRectFilled(cursorScreenPos, ImVec2(cursorScreenPos.x + 64.0f, cursorScreenPos.y + 64.0f), IM_COL32(204, 204, 204, 255));

        tb::Sprite spriteOutfit;

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
            if (creatureOutfit->Head == 0)
            {
                creatureOutfit->Head = tb::Constants::NumOutfitSpriteIDListHead - 1;
            }
            else
            {
                creatureOutfit->Head -= 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Head ");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonHeadRight", ImGuiDir_Right))
        {
            if (creatureOutfit->Head == tb::Constants::NumOutfitSpriteIDListHead - 1)
            {
                creatureOutfit->Head = 0;
            }
            else
            {
                creatureOutfit->Head += 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }

        if (ImGui::ArrowButton("##SetOutfitWindowButtonBodyLeft", ImGuiDir_Left))
        {
            if (creatureOutfit->Body == 0)
            {
                creatureOutfit->Body = tb::Constants::NumOutfitSpriteIDListBody - 1;
            }
            else
            {
                creatureOutfit->Body -= 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Body ");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonBodyRight", ImGuiDir_Right))
        {
            if (creatureOutfit->Body == tb::Constants::NumOutfitSpriteIDListBody - 1)
            {
                creatureOutfit->Body = 0;
            }
            else
            {
                creatureOutfit->Body += 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }

        if (ImGui::ArrowButton("##SetOutfitWindowButtonLegsLeft", ImGuiDir_Left))
        {
            if (creatureOutfit->Legs == 0)
            {
                creatureOutfit->Legs = tb::Constants::NumOutfitSpriteIDListLegs - 1;
            }
            else
            {
                creatureOutfit->Legs -= 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Legs ");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonLegsRight", ImGuiDir_Right))
        {
            if (creatureOutfit->Legs == tb::Constants::NumOutfitSpriteIDListLegs - 1)
            {
                creatureOutfit->Legs = 0;
            }
            else
            {
                creatureOutfit->Legs += 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }

        if (ImGui::ArrowButton("##SetOutfitWindowButtonFeetLeft", ImGuiDir_Left))
        {
            if (creatureOutfit->Feet == 0)
            {
                creatureOutfit->Feet = tb::Constants::NumOutfitSpriteIDListFeet - 1;
            }
            else
            {
                creatureOutfit->Feet -= 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }
        ImGui::SameLine();
        ImGui::TextUnformatted("Shoes");
        ImGui::SameLine();
        if (ImGui::ArrowButton("##SetOutfitWindowButtonFeetRight", ImGuiDir_Right))
        {
            if (creatureOutfit->Feet == tb::Constants::NumOutfitSpriteIDListFeet - 1)
            {
                creatureOutfit->Feet = 0;
            }
            else
            {
                creatureOutfit->Feet += 1;
            }

            m_creature->setOutfitSprites(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);
        }

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Set Outfit##SetOutfitWindowButtonSetOutfit", m_buttonSize))
        {
            tb::Creature::Ptr player = g_Game.getPlayer();

            player->setOutfit(creatureOutfit->Head, creatureOutfit->Body, creatureOutfit->Legs, creatureOutfit->Feet);

            onClose();

            setIsVisible(false);
        }

        ImGui::TableSetColumnIndex(1);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Cancel##SetOutfitWindowButtonCancel", m_buttonSize))
        {
            onClose();

            setIsVisible(false);
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

}
