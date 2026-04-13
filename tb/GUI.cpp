#include "common.h"

#include "tb/GUI.h"

namespace tb
{

GUI::GUI()
{
    //
}

GUI::~GUI()
{
    //
}

GUI::Properties* GUI::getProperties()
{
    return &m_properties;
}

bool GUI::initializeIMGUI()
{
    bool initResult = ImGui::SFML::Init(*g_RenderWindow.getWindow());

    if (initResult == false)
    {
        g_Log.write("ERROR: failed to initialize IMGUI\n");
        return false;
    }

    ImGui::StyleColorsLight();

    ImGuiStyle* style = &ImGui::GetStyle();

    style->FrameBorderSize = 1.0f;
    style->TabBorderSize = 1.0f;

    ImGuiIO& imguiIO = ImGui::GetIO();

    imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    imguiIO.ConfigWindowsMoveFromTitleBarOnly = true;
    imguiIO.ConfigDockingWithShift = true;

    return true;
}

void GUI::toggleDemoWindow()
{
    tb::Utility::toggleBool(m_properties.ShowDemoWindow);
}

void GUI::toggleStackToolWindow()
{
    tb::Utility::toggleBool(m_properties.ShowStackToolWindow);
}

void GUI::doErrorLoadingMapPopup()
{
    if (m_properties.ShowErrorLoadingMapPopup == true)
    {
        ImGui::OpenPopup("Error##ErrorLoadingMapPopup");
    }

    ImVec2 viewportCenter = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(viewportCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Error##ErrorLoadingMapPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::TextUnformatted("Failed to load map file!\nSee log for details.");

        ImGui::Separator();

        if (ImGui::Button("OK##ErrorLoadingMapPopupButtonOK", tb::LibIMGUI::PopupButtonSize))
        {
            m_properties.ShowErrorLoadingMapPopup = false;

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void GUI::doEndGamePopup()
{
    if (m_properties.ShowEndGamePopup == true)
    {
        ImGui::OpenPopup("End Game##EndGamePopup");
    }

    ImVec2 viewportCenter = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(viewportCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("End Game##EndGamePopup", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::TextUnformatted("Are you sure you want to end this game?");

        ImGui::Separator();

        if (ImGui::Button("Yes##EndGamePopupButtonYes", tb::LibIMGUI::PopupButtonSize))
        {
            ImGui::CloseCurrentPopup();

            m_properties.ShowEndGamePopup = false;

            g_Game.endGame();
        }

        ImGui::SameLine();

        if (ImGui::Button("No##EndGamePopupButtonNo", tb::LibIMGUI::PopupButtonSize))
        {
            ImGui::CloseCurrentPopup();

            m_properties.ShowEndGamePopup = false;
        }

        ImGui::EndPopup();
    }
}

sf::FloatRect GUI::getFullLayoutRect()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    float paddingRenderWindow = tb::Constants::GUIPaddingRenderWindow;

    sf::FloatRect layoutRect;
    layoutRect.position.x    = paddingRenderWindow;
    layoutRect.position.y    = paddingRenderWindow + menuBarHeight;
    layoutRect.size.x        = renderWindowSize.x - (paddingRenderWindow * 2.0f);
    layoutRect.size.y        = renderWindowSize.y - (paddingRenderWindow * 2.0f) - menuBarHeight - statusBarHeight;

    return layoutRect;
}

sf::FloatRect GUI::getLeftLayoutRect()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    float paddingRenderWindow = tb::Constants::GUIPaddingRenderWindow;

    float rightLayoutWidth = tb::Constants::GUIRightLayoutWidthAsFloat * m_properties.Scale;

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    sf::FloatRect layoutRect;
    layoutRect.position.x    = paddingRenderWindow;
    layoutRect.position.y    = paddingRenderWindow + menuBarHeight;
    layoutRect.size.x        = renderWindowSize.x - (paddingRenderWindow * 2.0f) - rightLayoutWidth - tb::Constants::GUIPaddingBetweenLeftAndRightLayoutRect;
    layoutRect.size.y        = renderWindowSize.y - (paddingRenderWindow * 2.0f) - menuBarHeight - statusBarHeight;

    return layoutRect;
}

sf::FloatRect GUI::getRightLayoutRect()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    float paddingRenderWindow = tb::Constants::GUIPaddingRenderWindow;

    float rightLayoutWidth = tb::Constants::GUIRightLayoutWidthAsFloat * m_properties.Scale;

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    sf::FloatRect layoutRect;
    layoutRect.position.x    = renderWindowSize.x - paddingRenderWindow - rightLayoutWidth;
    layoutRect.position.y    = paddingRenderWindow + menuBarHeight;
    layoutRect.size.x        = rightLayoutWidth;
    layoutRect.size.y        = renderWindowSize.y - (paddingRenderWindow * 2.0f) - menuBarHeight - statusBarHeight;

    return layoutRect;
}

sf::FloatRect GUI::getClickRect(const sf::Texture& texture, const std::string& name)
{
    sf::FloatRect clickRect;

    tb::TextureRectData::Data* textureRectData = g_TextureRectData.getDataByName(name);

    if (textureRectData == nullptr)
    {
        g_Log.write("ERROR: textureRectData == nullptr with name '{}'\n", name);

        clickRect.position.x = 0.0f;
        clickRect.position.y = 0.0f;
        clickRect.size.x = 0.0f;
        clickRect.size.y = 0.0f;

        return clickRect;
    }

    sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture.getSize());

    sf::Vector2f backgroundTextureSize = m_backgroundTextureRectShape.getSize();

    sf::Vector2f backgroundTextureScale;
    backgroundTextureScale.x = backgroundTextureSize.x / textureSize.x;
    backgroundTextureScale.y = backgroundTextureSize.y / textureSize.y;

    sf::Vector2f backgroundTexturePosition = m_backgroundTextureRectShape.getPosition();

    clickRect.position.x = backgroundTexturePosition.x + (static_cast<float>(textureRectData->X) * backgroundTextureScale.x);
    clickRect.position.y = backgroundTexturePosition.y + (static_cast<float>(textureRectData->Y) * backgroundTextureScale.y);

    clickRect.size.x = static_cast<float>(textureRectData->Width)  * backgroundTextureScale.x;
    clickRect.size.y = static_cast<float>(textureRectData->Height) * backgroundTextureScale.y;

    return clickRect;
}

void GUI::drawDockSpaceWindow()
{
    ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags dockSpaceWindowFlags = ImGuiWindowFlags_None;
    dockSpaceWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    dockSpaceWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float menuBarHeight = g_MenuBar.getHeight();
    const float statusBarHeight = g_StatusBar.getHeight();

    ImVec2 windowPosition = viewport->Pos;
    windowPosition.y += menuBarHeight;

    ImVec2 windowSize = viewport->Size;
    windowSize.y = windowSize.y - statusBarHeight + menuBarHeight;

    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowPos(windowPosition);
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    bool isDockSpaceVisible = true;

    ImGui::Begin("DockSpace##DockSpaceWindow", &isDockSpaceVisible, dockSpaceWindowFlags);

    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceID = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);

    ImGui::End();
}

void GUI::drawFramesPerSecond()
{
    float framesPerSecond = g_Game.getFramesPerSecond();

    std::string framesPerSecondText = std::format("FPS: {}", std::floorf(framesPerSecond));

    tb::BitmapFontText framesPerSecondBitmapFontText;
    framesPerSecondBitmapFontText.setText(&tb::Resources::BitmapFonts::TinyBitmapFont, framesPerSecondText, sf::Color::White);
    framesPerSecondBitmapFontText.setPosition(sf::Vector2f(1.0f, 1.0f + g_MenuBar.getHeight()));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(framesPerSecondBitmapFontText);
}

void GUI::drawDebugRect(sf::FloatRect rect)
{
    sf::RectangleShape rectangleShape;
    rectangleShape.setPosition(rect.position);
    rectangleShape.setSize(rect.size);
    rectangleShape.setFillColor(sf::Color::Transparent);
    rectangleShape.setOutlineColor(sf::Color::Magenta);
    rectangleShape.setOutlineThickness(1.0f);

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(rectangleShape);
}

void GUI::drawToolTip(const std::string& text)
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    tb::BitmapFontText bitmapFontText;
    bitmapFontText.setText(&tb::Resources::BitmapFonts::TinyBitmapFont, text, sf::Color::White);

    sf::FloatRect bitmapFontRect = bitmapFontText.getRect();

    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());

    const float toolTipVerticalOffset = 16.0f;

    sf::RectangleShape shape;
    shape.setTexture(&tb::Resources::Textures::Wood);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
    shape.setSize(sf::Vector2f(bitmapFontRect.size.x, bitmapFontRect.size.y));
    shape.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y + toolTipVerticalOffset));

    renderWindow->draw(shape);
}

void GUI::drawWoodBackground()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2u renderWindowSize = renderWindow->getSize();

    sf::Sprite wood(tb::Resources::Textures::Wood);
    wood.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(renderWindowSize.x, renderWindowSize.y)));

    renderWindow->draw(wood);
}

void GUI::drawWoodBorder(sf::FloatRect rect, bool drawBlackBorder)
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    if (drawBlackBorder == true)
    {
        sf::RectangleShape blackBorderRectShape;
        blackBorderRectShape.setPosition(rect.position);
        blackBorderRectShape.setSize(rect.size);
        blackBorderRectShape.setFillColor(sf::Color::Transparent);
        blackBorderRectShape.setOutlineColor(sf::Color::Black);
        blackBorderRectShape.setOutlineThickness(1.0f);

        renderWindow->draw(blackBorderRectShape);

        // enlarge the rectangle by 1 pixel to account for the black border
        rect.position.x -= 1.0f;
        rect.position.y -= 1.0f;
        rect.size.x     += 2.0f;
        rect.size.y     += 2.0f;
    }

    sf::Sprite woodHorizontal(tb::Resources::Textures::WoodHorizontal);
    sf::Sprite woodHorizontal2(tb::Resources::Textures::WoodHorizontal2);

    sf::Sprite woodVertical(tb::Resources::Textures::WoodVertical);
    sf::Sprite woodVertical2(tb::Resources::Textures::WoodVertical2);

    sf::Vector2u woodHorizontalSize = tb::Resources::Textures::WoodHorizontal.getSize();
    sf::Vector2u woodHorizontal2Size = tb::Resources::Textures::WoodHorizontal2.getSize();

    sf::Vector2u woodVerticalSize = tb::Resources::Textures::WoodVertical.getSize();
    sf::Vector2u woodVertical2Size = tb::Resources::Textures::WoodVertical2.getSize();

    // top
    woodHorizontal.setPosition(sf::Vector2f(static_cast<float>(rect.position.x - woodVerticalSize.x), static_cast<float>(rect.position.y - woodHorizontalSize.y)));
    woodHorizontal.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(static_cast<int>(rect.size.x + (woodVerticalSize.x * 2)), static_cast<int>(woodHorizontalSize.y))));

    // bottom
    woodHorizontal2.setPosition(sf::Vector2f(static_cast<float>(rect.position.x - woodVertical2Size.x), rect.position.y + rect.size.y));
    woodHorizontal2.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(static_cast<int>(rect.size.x + (woodVertical2Size.x * 2)), static_cast<int>(woodHorizontal2Size.y))));

    // left
    woodVertical.setPosition(sf::Vector2f(static_cast<float>(rect.position.x - woodVerticalSize.x), rect.position.y));
    woodVertical.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(static_cast<int>(woodVerticalSize.x), static_cast<int>(rect.size.y))));

    // right
    woodVertical2.setPosition(sf::Vector2f(rect.position.x + rect.size.x, rect.position.y));
    woodVertical2.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(static_cast<int>(woodHorizontal2Size.y), static_cast<int>(rect.size.y))));

    renderWindow->draw(woodHorizontal);
    renderWindow->draw(woodHorizontal2);
    renderWindow->draw(woodVertical);
    renderWindow->draw(woodVertical2);
}

void GUI::drawBackgroundTextureWithWoodBorder(const sf::Texture& texture)
{
    sf::FloatRect fullLayoutRect = getFullLayoutRect();

    m_backgroundTextureRectShape.setTexture(&texture, true);
    m_backgroundTextureRectShape.setPosition(fullLayoutRect.position);
    m_backgroundTextureRectShape.setSize(fullLayoutRect.size);

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(m_backgroundTextureRectShape);

    drawWoodBorder(m_backgroundTextureRectShape.getGlobalBounds(), true);
}

bool GUI::drawLoadingText()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Font loadingTextFont;
    if (loadingTextFont.openFromFile(tb::Constants::SystemFontFilePath) == false)
    {
        g_Log.write("ERROR: failed to load font to draw loading text\n");

        // blue screen of death
        renderWindow->clear(sf::Color::Blue);
        renderWindow->display();

        return false;
    }

    sf::Text loadingText(loadingTextFont);
    loadingText.setCharacterSize(13);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setString("Loading...");

    sf::FloatRect loadingTextRect = loadingText.getLocalBounds();

    loadingText.setOrigin
    (
        sf::Vector2f
        (
            loadingTextRect.position.x + loadingTextRect.size.x / 2.0f,
            loadingTextRect.position.y + loadingTextRect.size.y / 2.0f
        )
    );
    loadingText.setPosition(renderWindow->getView().getCenter());

    renderWindow->clear(sf::Color::Black);
    renderWindow->draw(loadingText);
    renderWindow->display();

    return true;
}

void GUI::SFMLWindows_draw()
{
    g_GameWindow.draw();

    if (m_properties.ShowEquipmentWindow == true)
    {
        g_EquipmentWindow.draw();
    }

    if (m_properties.ShowStatusWindow == true)
    {
        g_StatusWindow.draw();
    }

    if (m_properties.ShowMiniMapWindow == true)
    {
        g_MiniMapWindow.draw();
    }

    g_TabButtonsWindow.draw();

    if (m_properties.ShowSkillsWindow == true)
    {
        g_SkillsWindow.draw();
    }

    SFMLWindows_drawWoodBorder();

    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    if (isDebugModeEnabled == true)
    {
        SFMLWindows_drawDebugRect();
    }
}

void GUI::SFMLWindows_drawDebugRect()
{
    if (tb::LibIMGUI::isActive() == true)
    {
        return;
    }

    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        drawDebugRect(g_GameWindow.getRect());
    }

    if (m_properties.ShowEquipmentWindow == true)
    {
        if (g_EquipmentWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_EquipmentWindow.getRect());
        }
    }

    if (m_properties.ShowStatusWindow == true)
    {
        if (g_StatusWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_StatusWindow.getRect());
        }
    }

    if (m_properties.ShowMiniMapWindow == true)
    {
        if (g_MiniMapWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_MiniMapWindow.getRect());
        }
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        drawDebugRect(g_TabButtonsWindow.getRect());
    }

    if (m_properties.ShowSkillsWindow == true)
    {
        if (g_SkillsWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_SkillsWindow.getRect());
        }
    }
}

void GUI::SFMLWindows_drawWoodBorder()
{
    drawWoodBorder(g_GameWindow.getRect(), true);

    if (m_properties.ShowEquipmentWindow == true)
    {
        drawWoodBorder(g_EquipmentWindow.getRect(), true);
    }

    if (m_properties.ShowStatusWindow == true)
    {
        drawWoodBorder(g_StatusWindow.getRect(), true);
    }

    if (m_properties.ShowMiniMapWindow == true)
    {
        drawWoodBorder(g_MiniMapWindow.getRect(), true);
    }

    if (m_properties.ShowSkillsWindow == true)
    {
        drawWoodBorder(g_SkillsWindow.getRect(), true);
    }
}

void GUI::SFMLWindows_setSizeInLayout()
{
    g_SkillsWindow.setSizeInLayout();
}

void GUI::SFMLWindows_setPositionInLayout()
{
    // order is important

    g_EquipmentWindow.setPositionInLayout();

    g_StatusWindow.setPositionInLayout();

    g_MiniMapWindow.setPositionInLayout();

    g_TabButtonsWindow.setPositionInLayout();

    g_SkillsWindow.setPositionInLayout();

    g_GameWindow.setPositionInLayout();
}

void GUI::SFMLWindows_setSizeScale(float scale)
{
    m_properties.Scale = scale;

    g_EquipmentWindow.setSizeScale(scale);
    g_StatusWindow.setSizeScale(scale);
    g_MiniMapWindow.setSizeScale(scale);
    g_TabButtonsWindow.setSizeScale(scale);
    g_SkillsWindow.setSizeScale(scale);

    SFMLWindows_updateLayout();
}

void GUI::SFMLWindows_updateLayout()
{
    SFMLWindows_setPositionInLayout();
    SFMLWindows_setSizeInLayout();
}

void GUI::IMGUIWindows_draw()
{
    if (*g_MenuBar.isVisible() == true)
    {
        g_MenuBar.draw();
    }

    if (*g_StatusBar.isVisible() == true)
    {
        g_StatusBar.draw();
    }

    drawDockSpaceWindow();

    if (m_properties.ShowDemoWindow == true)
    {
        ImGui::ShowDemoWindow(&m_properties.ShowDemoWindow);
    }

    if (m_properties.ShowStackToolWindow == true)
    {
        ImGui::ShowStackToolWindow(&m_properties.ShowStackToolWindow);
    }

    if (*g_SpriteEditorWindow.isVisible() == true)
    {
        g_SpriteEditorWindow.draw();
    }

    if (*g_SpriteDataWindow.isVisible() == true)
    {
        g_SpriteDataWindow.draw();
    }

    if (*g_LogWindow.isVisible() == true)
    {
        g_LogWindow.draw();
    }

    if (*g_OptionsWindow.isVisible() == true)
    {
        g_OptionsWindow.draw();
    }

    if (*g_HotkeysWindow.isVisible() == true)
    {
        g_HotkeysWindow.draw();
    }

    if (*g_CommentsWindow.isVisible() == true)
    {
        g_CommentsWindow.draw();
    }

    if (*g_MessageOfTheDayWindow.isVisible() == true)
    {
        g_MessageOfTheDayWindow.draw();
    }

    if (*g_ConnectionWindow.isVisible() == true)
    {
        g_ConnectionWindow.draw();
    }

    if (*g_ControlsWindow.isVisible() == true)
    {
        g_ControlsWindow.draw();
    }

    if (*g_TipsAndTricksWindow.isVisible() == true)
    {
        g_TipsAndTricksWindow.draw();
    }

    if (*g_AboutTibiaWindow.isVisible() == true)
    {
        g_AboutTibiaWindow.draw();
    }

    if (*g_AboutTibianerWindow.isVisible() == true)
    {
        g_AboutTibianerWindow.draw();
    }

    if (*g_MapGeneratorWindow.isVisible() == true)
    {
        g_MapGeneratorWindow.draw();
    }

    tb::GameState gameState = g_Game.getGameState();

    if (gameState == tb::GameState::EnterGame)
    {
        if (*g_EnterGameWindow.isVisible() == true)
        {
            g_EnterGameWindow.draw();
        }
    }
    else if (gameState == tb::GameState::InGame)
    {
        if (*g_OverlayWindow.isVisible() == true)
        {
            g_OverlayWindow.draw();
        }

        if (*g_SetOutfitWindow.isVisible() == true)
        {
            g_SetOutfitWindow.draw();
        }
    }
    else if (gameState == tb::GameState::MapSelect)
    {
        if (*g_MapSelectWindow.isVisible() == true)
        {
            g_MapSelectWindow.draw();
        }
    }
}

}
