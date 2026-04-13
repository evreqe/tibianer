#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Resources.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/TextureRectData.h"

#include "tb/Game.h"
#include "tb/RenderWindow.h"
#include "tb/BitmapFontText.h"
#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

namespace tb
{

class GUI
{

public:

    GUI();
    ~GUI();

    static GUI& getInstance()
    {
        static GUI instance;
        return instance;
    }

private:

    GUI(const GUI&) = delete;
    GUI(GUI&&) = delete;
    GUI& operator=(const GUI&) = delete;
    GUI& operator=(GUI&&) = delete;

public:

    struct Properties
    {
        float Scale = 1.0f;

        bool ShowMenuBar = true;
        bool ShowStatusBar = true;

        bool ShowDemoWindow = false;
        bool ShowStackToolWindow = false;

        bool ShowErrorLoadingMapPopup = false;
        bool ShowEndGamePopup = false;

        bool ShowEquipmentWindow = false;
        bool ShowStatusWindow = false;
        bool ShowMiniMapWindow = true;

        bool TabButtonsWindowInventoryButtonIsPressed = true;
        bool TabButtonsWindowStatusButtonIsPressed = false;
        bool TabButtonsWindowBattleButtonIsPressed = false;
        bool TabButtonsWindowMiniMapButtonIsPressed = false;

        bool ShowInventoryWindow = true;
        bool ShowSkillsWindow = false;
        bool ShowBattleWindow = false;

        bool BattleButtonsWindowFullAttackButtonIsPressed = true;
        bool BattleButtonsWindowHalfAttackHalfDefenseButtonIsPressed = false;
        bool BattleButtonsWindowFullDefenseButtonIsPressed = false;

        bool BattleButtonsWindowFollowButtonIsPressed = false;
        bool BattleButtonsWindowFollowDistanceButtonIsPressed = false;
        bool BattleButtonsWindowDoNotFollowButtonIsPressed = true;
    };

    Properties* getProperties();

    bool initializeIMGUI();

    void toggleDemoWindow();
    void toggleStackToolWindow();

    void doErrorLoadingMapPopup();
    void doEndGamePopup();

    sf::FloatRect getFullLayoutRect();
    sf::FloatRect getLeftLayoutRect();
    sf::FloatRect getRightLayoutRect();

    sf::FloatRect getClickRect(const sf::Texture& texture, const std::string& name);

    void drawDockSpaceWindow();
    void drawFramesPerSecond();
    void drawDebugRect(sf::FloatRect rect);
    void drawToolTip(const std::string& text);
    void drawWoodBackground();
    void drawWoodBorder(sf::FloatRect rect, bool drawBlackBorder);
    void drawBackgroundTextureWithWoodBorder(const sf::Texture& texture);
    bool drawLoadingText();

    void SFMLWindows_draw();
    void SFMLWindows_drawDebugRect();
    void SFMLWindows_drawWoodBorder();
    void SFMLWindows_setSizeInLayout();
    void SFMLWindows_setPositionInLayout();
    void SFMLWindows_setSizeScale(float scale);
    void SFMLWindows_updateLayout();

    void IMGUIWindows_draw();

private:

    Properties m_properties;

    sf::RectangleShape m_backgroundTextureRectShape;

};

}

namespace
{
    inline tb::GUI& g_GUI = tb::GUI::getInstance();
}
