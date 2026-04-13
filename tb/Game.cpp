#include "common.h"

#include "tb/Game.h"

namespace tb
{

Game::Game()
{
    //
}

Game::~Game()
{
    //
}

Game::Properties* Game::getProperties()
{
    return &m_properties;
}

bool Game::loadConfig()
{
    g_Log.write("Loading options data\n");
    if (g_OptionsData.load() == false)
    {
        g_Log.write("ERROR: failed to load options data\n");
        return false;
    }

    g_Log.write("Loading hotkeys data\n");
    if (g_HotkeysData.load() == false)
    {
        g_Log.write("ERROR: failed to load hotkeys data\n");
        return false;
    }

    return true;
}

bool Game::loadData()
{
    g_Log.write("Loading map data\n");
    if (g_MapData.load() == false)
    {
        g_Log.write("ERROR: failed to load map data\n");
        return false;
    }

    g_Log.write("Loading texture data\n");
    if (g_TextureData.load() == false)
    {
        g_Log.write("ERROR: failed to load texture data\n");
        return false;
    }

    g_Log.write("Loading sprite data\n");
    if (g_SpriteData.load() == false)
    {
        g_Log.write("ERROR: failed to load sprite data\n");
        return false;
    }

    g_Log.write("Loading font data\n");
    if (g_FontData.load() == false)
    {
        g_Log.write("ERROR: failed to load font data\n");
        return false;
    }

    g_Log.write("Loading bitmap font data\n");
    if (g_BitmapFontData.load() == false)
    {
        g_Log.write("ERROR: failed to load bitmap font data\n");
        return false;
    }

    g_Log.write("Loading pattern data\n");
    if (g_PatternData.load() == false)
    {
        g_Log.write("ERROR: failed to load pattern data\n");
        return false;
    }

    g_Log.write("Loading water animation data\n");
    if (g_WaterAnimationData.load() == false)
    {
        g_Log.write("ERROR: failed to load water animation data\n");
        return false;
    }

    g_Log.write("Loading outfit sprites data\n");
    if (g_OutfitSpritesData.load() == false)
    {
        g_Log.write("ERROR: failed to load outfit sprites data\n");
        return false;
    }

    g_Log.write("Loading message of the day data\n");
    if (g_MessageOfTheDayData.load() == false)
    {
        g_Log.write("ERROR: failed to load message of the day data\n");
        return false;
    }

    g_Log.write("Loading texture rect data\n");
    if (g_TextureRectData.load() == false)
    {
        g_Log.write("ERROR: failed to load texture rect data\n");
        return false;
    }

    g_Log.write("Loading cursor data\n");
    if (g_CursorData.load() == false)
    {
        g_Log.write("ERROR: failed to load cursor data\n");
        return false;
    }

    g_Log.write("Loading animation data\n");
    if (g_AnimationData.load() == false)
    {
        g_Log.write("ERROR: failed to load animation data\n");
        return false;
    }

    g_Log.write("Loading map generator data\n");
    if (g_MapGeneratorData.load() == false)
    {
        g_Log.write("ERROR: failed to load map generator data\n");
        return false;
    }

    g_Log.write("Loading map generator pixel data\n");
    if (g_MapGeneratorPixelData.load() == false)
    {
        g_Log.write("ERROR: failed to load map generator pixel data\n");
        return false;
    }

    return true;
}

bool Game::loadMap(const std::string& fileName)
{
    g_Log.write("Loading map\n");
    if (g_Map.load(fileName) == false)
    {
        g_Log.write("ERROR: failed to load map from file: {}\n", fileName);
        return false;
    }

    g_GameWindow.resetViewPositionOffset();

    g_Log.write("Creating player\n");
    if (createPlayer() == false)
    {
        g_Log.write("ERROR: failed to create player\n");
    }

    return true;
}

void Game::loadMapUsingThread(const std::string& fileName)
{
    m_loadMapThread = std::async(std::launch::async, &Game::loadMap, &g_Game, fileName);
}



void Game::doGameStateTesting()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->clear(sf::Color::White);

/*
    sf::Vector2f drawPosition = sf::Vector2f(100.0f, 100.0f);

    sf::Text testText;
    testText.setFont(tb::Fonts::SystemFixed);
    testText.setCharacterSize(tb::Fonts::CharacterSize::SystemFixed);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 0; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            drawPosition.x = 100.0f;
            drawPosition.y += 16.0f;
        }

        std::string character;
        character = (char)i;

        testText.setString(character);

        testText.setPosition(drawPosition);

        renderWindow->draw(testText);

        drawPosition.x += 16.0f;
    }

    sf::FloatRect rect;
    rect.left = 100.0f;
    rect.top = 100.0f + 3.0f;
    rect.width = 256.0f;
    rect.height = 256.0f;

    drawDebugRect(rect);
*/

/*
    sf::Vector2f drawPosition = sf::Vector2f(10.0f, 40.0f);

    sf::Text testText;
    testText.setFont(tb::Fonts::System);
    testText.setCharacterSize(13);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 32; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 32 && i % 16 == 0)
        {
            drawPosition.x += 100.0f;
            drawPosition.y = 40.0f;
        }

        char character = (char)i;

        std::string text = std::format("{}: {}{}", i, character, character);

        testText.setString(text);

        testText.setPosition(drawPosition);

        renderWindow->draw(testText);

        drawPosition.y += 16.0f;
    }
*/

/*
    sf::Font* font = &tb::Fonts::System;

    sf::Vector2f drawPosition = sf::Vector2f(100.0f, 100.0f);

    sf::Text testText;
    testText.setFont(*font);
    testText.setCharacterSize(13);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 0; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            drawPosition.x = 100.0f;
            drawPosition.y += 16.0f;
        }

        sf::Glyph glyph = font->getGlyph(i, 13, false, 0.0f);

        float characterLeft = glyph.bounds.left;
        float characterWidth = glyph.bounds.width;

        std::string characterText = std::format("{}", characterLeft + characterWidth);

        testText.setString(characterText);

        testText.setPosition(drawPosition);

        renderWindow->draw(testText);

        drawPosition.x += 32.0f;
    }
*/

/*
    sf::Vector2f drawPosition = sf::Vector2f(100.0f, 100.0f);

    sf::Text testText;
    testText.setFont(tb::Fonts::System);
    testText.setCharacterSize(13);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 0; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            drawPosition.x = 100.0f;
            drawPosition.y += 16.0f;
        }

        std::string character;
        character = (char)i;

        std::string text = std::format("x{}x", character);

        testText.setString(text);

        testText.setPosition(drawPosition);

        sf::FloatRect textRect = testText.getLocalBounds();

        float characterWidth = textRect.width - 16.0f;

        text = std::format("{}", characterWidth);

        testText.setString(text);

        renderWindow->draw(testText);

        drawPosition.x += 32.0f;
    }
*/

/*
    tb::BitmapFontText bitmapText;
    bitmapText.setText(&m_systemBitmapFont, "Hello, world!", sf::Color::Black);
    bitmapText.setPosition(sf::Vector2f(100.0f, 100.0f));

    renderWindow->draw(bitmapText);

    sf::Text text;
    text.setString("Hello, world!");
    text.setFont(tb::Fonts::System);
    text.setCharacterSize(tb::Fonts::CharacterSize::System);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(100.0f, 116.0f));

    renderWindow->draw(text);
*/

    tb::BitmapFontText bitmapText;
    bitmapText.setText(&tb::Resources::BitmapFonts::SystemFixedBitmapFont, "Hello, world! ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqqrstuvwxyz\n1234567890\n!@#$%^&*()-+[]\n", sf::Color::Black);
    bitmapText.setPosition(sf::Vector2f(100.0f, 100.0f));

    renderWindow->draw(bitmapText);
}

void Game::doGameStateEnterGame()
{
    g_GUI.drawBackgroundTextureWithWoodBorder(tb::Resources::Textures::EnterGame);

    if (isDebugModeEnabled() == true)
    {
        if (tb::LibIMGUI::isActive() == false)
        {
            sf::FloatRect enterGameClickRect = g_GUI.getClickRect(tb::Resources::Textures::EnterGame, "EnterGame");

            sf::Vector2f mousePosition = g_RenderWindow.getMousePosition2f();

            if (enterGameClickRect.contains(mousePosition) == true)
            {
                g_GUI.drawDebugRect(enterGameClickRect);
            }
        }
    }
}

void Game::doGameStateLoadingMap()
{
    g_GUI.drawBackgroundTextureWithWoodBorder(tb::Resources::Textures::Loading);

    m_loadMapThreadStatus = m_loadMapThread.wait_for(std::chrono::milliseconds(1));

    if (m_loadMapThreadStatus == std::future_status::ready)
    {
        if (m_loadMapThread.valid() == true)
        {
            bool isMapLoaded = m_loadMapThread.get();

            if (isMapLoaded == true)
            {
                setGameState(tb::GameState::InGame);
            }
            else
            {
                tb::GUI::Properties* guiProperties = g_GUI.getProperties();

                guiProperties->ShowErrorLoadingMapPopup = true;

                setGameState(tb::GameState::MapSelect);

                g_MapSelectWindow.setVisible(true);
            }
        }
    }
}

void Game::doGameStateMapSelect()
{
    g_GUI.drawBackgroundTextureWithWoodBorder(tb::Resources::Textures::MapSelect);

    if (*g_MapSelectWindow.isVisible() == false)
    {
        setGameState(tb::GameState::EnterGame);
    }

    g_GUI.doErrorLoadingMapPopup();
}

void Game::doGameStateInGame()
{
    g_GUI.SFMLWindows_draw();

    g_GUI.doEndGamePopup();
}

sf::Vector2i Game::getMousePositionInDesktop()
{
    // get mouse position in operating system desktop
    return sf::Mouse::getPosition();
}

tb::AxisZVisibility Game::getPlayerAxisZVisibility()
{
    tb::AxisZVisibility axisZVisibility;
    axisZVisibility.Begin = tb::Constants::AxisZMin;
    axisZVisibility.End   = tb::Constants::AxisZMax;

    tb::AxisZ playerAxisZ = m_player->getAxisZ();

    // check if the player is underground
    if (playerAxisZ < tb::Constants::AxisZDefault)
    {
        // get all z-axis that are underground
        axisZVisibility.Begin = tb::Constants::AxisZMin;
        axisZVisibility.End   = tb::Constants::AxisZDefault - 1;
    }
    else
    {
        // get all z-axis that are aboveground
        axisZVisibility.Begin = tb::Constants::AxisZDefault;
        axisZVisibility.End   = tb::Constants::AxisZMax;
    }

    return axisZVisibility;
}

bool Game::createPlayer()
{
    tb::Map::Properties* mapProperties = g_Map.getProperties();

    tb::Creature::Ptr player = std::make_shared<tb::Creature>
    (
        sf::Vector2i(mapProperties->PlayerStartX, mapProperties->PlayerStartY),
        mapProperties->PlayerStartZ
    );

    tb::Creature::Properties* playerProperties = player->getProperties();
    playerProperties->IsPlayer = true;
    playerProperties->HasOutfit = true;

    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    player->setOutfit(optionsData->PlayerOutfitHead, optionsData->PlayerOutfitBody, optionsData->PlayerOutfitLegs, optionsData->PlayerOutfitFeet);

    std::string playerName = optionsData->PlayerName;
    if (playerName.size() == 0)
    {
        playerName = tb::Constants::PlayerNameDefault;
    }

    player->setName(playerName);

    player->setMovementSpeed(0.1f);

    m_player = player;

    tb::Tile::Ptr tile = g_Map.getTileAtThing(m_player);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: tile == nullptr\n");
        return false;
    }

    tile->addCreature(m_player);

    g_Log.write("Tile Index: {}\n", tile->getTileIndex());
    g_Log.write("Tile X: {}\n", tile->getTileX());
    g_Log.write("Tile Y: {}\n", tile->getTileY());
    g_Log.write("Tile Z: {}\n", tile->getAxisZ());
    g_Log.write("Tile Sprite ID: {}\n", tile->getSpriteID());

    tb::TileCoords playerTileCoords = m_player->getTileCoords();

    tb::AxisZ playerAxisZ = m_player->getAxisZ();

    g_Log.write("Player Tile Coords: {},{},{}\n", playerTileCoords.x, playerTileCoords.y, playerAxisZ);

    spawnAnimationByIndex(playerTileCoords, playerAxisZ, tb::Resources::Animations::BlueOrbSpellEffect);

    return true;
}

bool Game::spawnAnimationByIndex(const tb::TileCoords& tileCoords, tb::AxisZ axisZ, std::uint32_t index)
{
    tb::Animation::Ptr animation = std::make_shared<tb::Animation>(tileCoords, axisZ, index);

    if (animation == nullptr)
    {
        g_Log.write("ERROR: animation == nullptr\n");
        return false;
    }

    tb::Tile::Ptr tile = g_Map.getTile(tileCoords, axisZ);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: tile == nullptr\n");
        return false;
    }

    tile->addAnimation(animation);

    return true;
}

bool Game::spawnAnimationByName(const tb::TileCoords& tileCoords, tb::AxisZ axisZ, const std::string& name)
{
    tb::Animation::Ptr animation = std::make_shared<tb::Animation>(tileCoords, axisZ, name);

    tb::Tile::Ptr tile = g_Map.getTile(tileCoords, axisZ);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: tile == nullptr\n");
        return false;
    }

    tile->addAnimation(animation);

    return true;
}

void Game::handleEventClosed()
{
    g_RenderWindow.handleEventClosed();
}

void Game::handleEventResized(const sf::Event::Resized* eventResized)
{
    g_RenderWindow.handleEventResized(eventResized);

    g_SkillsWindow.handleEventResized(eventResized);
}

void Game::handleEventFocusGained()
{
    g_RenderWindow.handleEventFocusGained();
}

void Game::handleEventFocusLost()
{
    g_RenderWindow.handleEventFocusLost();
}

void Game::handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled)
{
    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        g_GameWindow.handleEventMouseWheelScrolled(eventMouseWheelScrolled);
    }

    if (g_MiniMapWindow.isMouseInsideWindow() == true)
    {
        g_MiniMapWindow.handleEventMouseWheelScrolled(eventMouseWheelScrolled);
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        g_TabButtonsWindow.handleEventMouseWheelScrolled(eventMouseWheelScrolled);
    }

    if (g_SkillsWindow.isMouseInsideWindow() == true)
    {
        g_SkillsWindow.handleEventMouseWheelScrolled(eventMouseWheelScrolled);
    }
}

void Game::handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed)
{
    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        g_GameWindow.handleEventMouseButtonPressed(eventMouseButtonPressed);
    }

    if (g_MiniMapWindow.isMouseInsideWindow() == true)
    {
        g_MiniMapWindow.handleEventMouseButtonPressed(eventMouseButtonPressed);
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        g_TabButtonsWindow.handleEventMouseButtonPressed(eventMouseButtonPressed);
    }

    if (g_SkillsWindow.isMouseInsideWindow() == true)
    {
        g_SkillsWindow.handleEventMouseButtonPressed(eventMouseButtonPressed);
    }

    if (eventMouseButtonPressed->button == sf::Mouse::Button::Left)
    {
        m_properties.IsMouseLeftButtonPressed = true;

        if (m_properties.IsMouseDragging == false)
        {
            m_mouseDragStartPosition.x = eventMouseButtonPressed->position.x;
            m_mouseDragStartPosition.y = eventMouseButtonPressed->position.y;

            m_mouseDragClock.restart();
        }
    }
}

void Game::handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased)
{
    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        g_GameWindow.handleEventMouseButtonReleased(eventMouseButtonReleased);
    }

    if (g_MiniMapWindow.isMouseInsideWindow() == true)
    {
        g_MiniMapWindow.handleEventMouseButtonReleased(eventMouseButtonReleased);
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        g_TabButtonsWindow.handleEventMouseButtonReleased(eventMouseButtonReleased);
    }

    if (g_SkillsWindow.isMouseInsideWindow() == true)
    {
        g_SkillsWindow.handleEventMouseButtonReleased(eventMouseButtonReleased);
    }

    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(eventMouseButtonReleased->position);

    if (eventMouseButtonReleased->button == sf::Mouse::Button::Left)
    {
        m_properties.IsMouseLeftButtonPressed = false;

        if (m_properties.IsMouseDragging == true)
        {
            setMouseCursor(tb::Resources::Cursors::System::Arrow);

            m_properties.IsMouseDragging = false;
        }

        if (m_gameState == tb::GameState::EnterGame)
        {
            sf::FloatRect enterGameClickRect = g_GUI.getClickRect(tb::Resources::Textures::EnterGame, "EnterGame");

            if (enterGameClickRect.contains(mousePosition) == true)
            {
                g_EnterGameWindow.setVisible(true);
            }
        }
    }
}

void Game::handleEventMouseMoved(const sf::Event::MouseMoved* eventMouseMoved)
{
    if (m_properties.IsMouseLeftButtonPressed == true)
    {
        if (m_properties.IsMouseDragging == false)
        {
            sf::Vector2i distance = tb::LibSFML::getDistanceBetweenPositions2i(m_mouseDragStartPosition, eventMouseMoved->position);

            if (distance.x >= m_mouseDragDistanceThreshold || distance.y >= m_mouseDragDistanceThreshold)
            {
                sf::Time mouseDragTime = m_mouseDragClock.getElapsedTime();
                if (mouseDragTime >= m_mouseDragTime)
                {
                    setMouseCursor(tb::Resources::Cursors::Custom::Drag);

                    m_properties.IsMouseDragging = true;

                    m_mouseDragClock.restart();
                }
            }
        }
    }
}

void Game::handleEventKeyPressed(const sf::Event::KeyPressed* eventKeyPressed)
{
    m_properties.IsAnyKeyboardKeyPressed = true;

    if (m_gameState == tb::GameState::InGame)
    {
        if (eventKeyPressed->code == sf::Keyboard::Key::B)
        {
            spawnAnimationByIndex(m_player->getTileCoords(), m_player->getAxisZ(), tb::Resources::Animations::BlueOrbSpellEffect);
        }
    }
}

void Game::handleEventKeyReleased(const sf::Event::KeyReleased* eventKeyReleased)
{
    m_properties.IsAnyKeyboardKeyPressed = false;
}

void Game::handleEventJoystickConnected(const sf::Event::JoystickConnected* eventJoystickConnected)
{
    g_JoystickManager.handleEventJoystickConnected(eventJoystickConnected);
}

void Game::handleEventJoystickDisconnected(const sf::Event::JoystickDisconnected* eventJoystickDisconnected)
{
    g_JoystickManager.handleEventJoystickDisconnected(eventJoystickDisconnected);
}

void Game::handleEventJoystickMoved(const sf::Event::JoystickMoved* eventJoystickMoved)
{
    g_Log.write("Joystick Moved Axis and Position: {} = {}\n", magic_enum::enum_name(eventJoystickMoved->axis), eventJoystickMoved->position);
}

void Game::handleEventJoystickButtonPressed(const sf::Event::JoystickButtonPressed* eventJoystickButtonPressed)
{
    m_properties.IsAnyJoystickButtonPressed = true;
}

void Game::handleEventJoystickButtonReleased(const sf::Event::JoystickButtonReleased* eventJoystickButtonReleased)
{
    m_properties.IsAnyJoystickButtonPressed = false;

    g_Log.write("Joystick Button Released: {}\n", eventJoystickButtonReleased->button);
}

void Game::initializeFramesPerSecond()
{
    m_framesPerSecondClock.restart();
    m_framesPerSecondPreviousTime = m_framesPerSecondClock.getElapsedTime();
}

void Game::calculateFramesPerSecond()
{
    m_framesPerSecondCurrentTime = m_framesPerSecondClock.getElapsedTime();

    m_framesPerSecond = 1.0f / (m_framesPerSecondCurrentTime.asSeconds() - m_framesPerSecondPreviousTime.asSeconds());

    m_framesPerSecondPreviousTime = m_framesPerSecondCurrentTime;
}

float Game::getFramesPerSecond()
{
    return m_framesPerSecond;
}

void Game::processEvents()
{
    bool libIMGUIIsActive = tb::LibIMGUI::isActive();

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    tb::RenderWindow::Properties* renderWindowProperties = g_RenderWindow.getProperties();

    bool renderWindowIsFocused = renderWindowProperties->IsFocused;

    while (const std::optional event = renderWindow->pollEvent())
    {
        ImGui::SFML::ProcessEvent(*renderWindow, *event);

        if (event->is<sf::Event::Closed>())
        {
            handleEventClosed();
        }
        else if (const sf::Event::Resized* eventResized = event->getIf<sf::Event::Resized>())
        {
            handleEventResized(eventResized);
        }
        else if (event->is<sf::Event::FocusLost>())
        {
            handleEventFocusLost();
        }
        else if (event->is<sf::Event::FocusGained>())
        {
            handleEventFocusGained();
        }
        else if (const sf::Event::JoystickConnected* eventJoystickConnected = event->getIf<sf::Event::JoystickConnected>())
        {
            handleEventJoystickConnected(eventJoystickConnected);
        }
        else if (const sf::Event::JoystickDisconnected* eventJoystickDisconnected = event->getIf<sf::Event::JoystickDisconnected>())
        {
            handleEventJoystickDisconnected(eventJoystickDisconnected);
        }

        if (renderWindowIsFocused == true && libIMGUIIsActive == false)
        {
            if (const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                handleEventMouseWheelScrolled(eventMouseWheelScrolled);
            }
            else if (const sf::Event::MouseButtonPressed* eventMouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                handleEventMouseButtonPressed(eventMouseButtonPressed);
            }
            else if (const sf::Event::MouseButtonReleased* eventMouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                handleEventMouseButtonReleased(eventMouseButtonReleased);
            }
            else if (const sf::Event::MouseMoved* eventMouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                handleEventMouseMoved(eventMouseMoved);
            }
            else if (const sf::Event::KeyPressed* eventKeyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                handleEventKeyPressed(eventKeyPressed);
            }
            else if (const sf::Event::KeyReleased* eventKeyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                handleEventKeyReleased(eventKeyReleased);
            }
            else if (const sf::Event::JoystickMoved* eventJoystickMoved = event->getIf<sf::Event::JoystickMoved>())
            {
                handleEventJoystickMoved(eventJoystickMoved);
            }
            else if (const sf::Event::JoystickButtonPressed* eventJoystickButtonPressed = event->getIf<sf::Event::JoystickButtonPressed>())
            {
                handleEventJoystickButtonPressed(eventJoystickButtonPressed);
            }
            else if (const sf::Event::JoystickButtonReleased* eventJoystickButtonReleased = event->getIf<sf::Event::JoystickButtonReleased>())
            {
                handleEventJoystickButtonReleased(eventJoystickButtonReleased);
            }
        }
    }

    if (renderWindowIsFocused == true && libIMGUIIsActive == false)
    {
        handleKeyboardInput();

        g_JoystickManager.updateJoystickStates();
        handleJoystickInput();
    }
}

void Game::handleKeyboardInput()
{
    handlePlayerMovement();
    handleCameraMovement();
}

void Game::handleJoystickInput()
{
    tb::Joystick* joystick = g_JoystickManager.getJoystick();

    if (joystick == nullptr)
    {
        return;
    }

    if (joystick->isConnected() == false)
    {
        return;
    }

    tb::Joystick::State* joystickState = joystick->getState();

    if (m_gameState == tb::GameState::InGame)
    {
        if (joystickState->AxisPOVY >= 50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Up);
        }

        if (joystickState->AxisPOVX >= 50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Right);
        }

        if (joystickState->AxisPOVY <= -50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Down);
        }

        if (joystickState->AxisPOVX <= -50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Left);
        }
    }
}

void Game::handleCameraMovement()
{
    if (isDebugModeEnabled() == false)
    {
        return;
    }

    if (m_gameState != tb::GameState::InGame)
    {
        return;
    }

    sf::Time cameraMovementTimeElapsed = m_cameraMovementClock.getElapsedTime();

    if (cameraMovementTimeElapsed >= m_cameraMovementTime)
    {
        // camera reset
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad0) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0) == true)
        {
            g_GameWindow.resetViewPositionOffset();

            m_cameraMovementClock.restart();
        }

        // camera up
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8) == true)
        {
            sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

            viewPositionOffset.y -= tb::Constants::TileSizeAsFloat;

            g_Log.write("View Position Offset: {},{}\n", viewPositionOffset.x, viewPositionOffset.y);

            g_GameWindow.setViewPositionOffset(viewPositionOffset);

            m_cameraMovementClock.restart();
        }

        // camera right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6) == true)
        {
            sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

            viewPositionOffset.x += tb::Constants::TileSizeAsFloat;

            g_Log.write("View Position Offset: {},{}\n", viewPositionOffset.x, viewPositionOffset.y);

            g_GameWindow.setViewPositionOffset(viewPositionOffset);

            m_cameraMovementClock.restart();
        }

        // camera down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad5) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) == true)
        {
            sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

            viewPositionOffset.y += tb::Constants::TileSizeAsFloat;

            g_Log.write("View Position Offset: {},{}\n", viewPositionOffset.x, viewPositionOffset.y);

            g_GameWindow.setViewPositionOffset(viewPositionOffset);

            m_cameraMovementClock.restart();
        }

        // camera left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) == true)
        {
            sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

            viewPositionOffset.x -= tb::Constants::TileSizeAsFloat;

            g_Log.write("View Position Offset: {},{}\n", viewPositionOffset.x, viewPositionOffset.y);

            g_GameWindow.setViewPositionOffset(viewPositionOffset);

            m_cameraMovementClock.restart();
        }
    }
}

void Game::handlePlayerMovement()
{
    if (m_gameState != tb::GameState::InGame)
    {
        return;
    }

    sf::Time playerMovementTimeElapsed = m_playerMovementClock.getElapsedTime();

    if (playerMovementTimeElapsed >= m_playerMovementTime)
    {
        bool isMovementKeyPressed = false;
        tb::MovementDirection playerMovementDirection = tb::MovementDirection::Null;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            isMovementKeyPressed = true;
            playerMovementDirection = tb::MovementDirection::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            isMovementKeyPressed = true;
            playerMovementDirection = tb::MovementDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            isMovementKeyPressed = true;
            playerMovementDirection = tb::MovementDirection::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            isMovementKeyPressed = true;
            playerMovementDirection = tb::MovementDirection::Left;
        }

        if (isMovementKeyPressed == true && playerMovementDirection != tb::MovementDirection::Null)
        {
            // this resets the camera movement when the player moves, so the camera doesn't stay in the offset position when the player moves
            sf::Vector2f gameWindowViewPositionOffset = g_GameWindow.getViewPositionOffset();
            if (gameWindowViewPositionOffset.x != 0 || gameWindowViewPositionOffset.y != 0)
            {
                g_GameWindow.resetViewPositionOffset();
                m_playerMovementClock.restart();
                return;
            }

            handleCreatureMovement(m_player, playerMovementDirection);

            m_playerMovementClock.restart();
        }
    }
}

void Game::setMouseCursor(const sf::Cursor& cursor)
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->setMouseCursor(cursor);
}

void Game::fixMouseCursorForWindowResize(sf::RenderWindow* renderWindow)
{
    // this function fixes a bug between IMGUI, SFML and imgui-SFML
    // where the mouse cursor doesn't work correctly when resizing the window

    static ImGuiIO& imguiIO = ImGui::GetIO();

    static bool imguiHasCursorPrev = true;

    if (bool imguiHasCursor = imguiIO.WantCaptureMouse || imguiIO.WantCaptureKeyboard; imguiHasCursor != imguiHasCursorPrev)
    {
        if (imguiHasCursor)
        {
            imguiIO.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
        }
        else
        {
            imguiIO.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

            renderWindow->setMouseCursor(tb::Resources::Cursors::System::Arrow);
        }

        imguiHasCursorPrev = imguiHasCursor;
    }
}

void Game::createTileFileFromImageFile(const std::string& fileName)
{
    std::fstream file;
    file.open("tiles.txt", std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        g_Log.write("ERROR: cannot open file: tiles.txt\n");
        return;
    }

    sf::Image image;
    if (image.loadFromFile(fileName) == false)
    {
        g_Log.write("ERROR: cannot open file: {}\n", fileName);
        return;
    }

    // TODO: rotate image 90 degrees clockwise
    // TODO: flip image horizontal

    std::uint32_t imageWidth = image.getSize().x;
    std::uint32_t imageHeight = image.getSize().y;

    tb::SpriteIDList spriteIDList;

    for (std::uint32_t i = 0; i < imageWidth; i++)
    {
        for (std::uint32_t j = 0; j < imageHeight; j++)
        {
            sf::Color pixelColor = image.getPixel(sf::Vector2u(i, j));

            //g_Log.write("pixelColor: {},{},{}\n", pixelColor.r, pixelColor.g, pixelColor.b);

            tb::SpriteID spriteID = tb::Constants::SpriteIDDefault;

            if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0)
            {
                // black = void
                spriteID = 0;
            }
            else if (pixelColor.r == 255 && pixelColor.g == 255 && pixelColor.b == 255)
            {
                // white = text
                spriteID = 17;
            }
            else if (pixelColor.r == 255 && pixelColor.g == 0 && pixelColor.b == 0)
            {
                // red = solid
                spriteID = 463;
            }
            else if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 255)
            {
                // blue = water
                spriteID = 69;
            }
            else if (pixelColor.r == 0 && pixelColor.g == 255 && pixelColor.b == 0)
            {
                // green = grass
                spriteID = 2;
            }
            else if (pixelColor.r == 0 && pixelColor.g == 64 && pixelColor.b == 0)
            {
                // dark green = trees
                spriteID = 25;
            }
            else if (pixelColor.r == 192 && pixelColor.g == 192 && pixelColor.b == 192)
            {
                // gray = cobblestone
                spriteID = 77;
            }
            else if (pixelColor.r == 64 && pixelColor.g == 64 && pixelColor.b == 64)
            {
                // dark gray = unknown
                spriteID = 44;
            }
            else if (pixelColor.r == 128 && pixelColor.g == 64 && pixelColor.b == 0)
            {
                // brown = dirt
                spriteID = 5;
            }
            else if (pixelColor.r == 255 && pixelColor.g == 255 && pixelColor.b == 0)
            {
                // yellow = stairs
                spriteID = 457;
            }

            //g_Log.write("spriteID: {}\n", spriteID);

            spriteIDList.push_back(spriteID);
        }
    }

    std::size_t spriteIDListSize = spriteIDList.size();

    for (std::size_t i = 0; i < spriteIDListSize; i++)
    {
        file << spriteIDList.at(i);

        if (i < spriteIDListSize - 1)
        {
            file << ",";
        }

        if (i != 0 && i % imageWidth == 0)
        {
            file << "\n";
        }
    }

    file.close();
}

void Game::updateOverlayWindowText()
{
    g_OverlayWindow.clearTextList();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    tb::Creature::Outfit* playerOutfit = m_player->getOutfit();

    std::string playerText = std::format
    (
"\
Player X,Y,Z: {},{},{}\n\
Player Outfit: {},{},{},{}\n\
",
        m_player->getTileX(), m_player->getTileY(), m_player->getAxisZ(),
        playerOutfit->Head, playerOutfit->Body, playerOutfit->Legs, playerOutfit->Feet
    );

    g_OverlayWindow.addTextToList(playerText);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2i mousePositionInDesktop = getMousePositionInDesktop();
    sf::Vector2i mousePositionInRenderWindow = g_RenderWindow.getMousePosition2i();
    sf::Vector2f mousePixelPositionInGameWindow = g_GameWindow.getMousePixelPosition();
    tb::PixelCoords mousePixelCoordsInGameWindow = g_GameWindow.getMousePixelCoords();
    tb::TileCoords mouseTileCoordsInGameWindow = g_GameWindow.getMouseTileCoords();
    bool mouseIsLeftButtonPressed = m_properties.IsMouseLeftButtonPressed;
    bool mouseIsDragging = m_properties.IsMouseDragging;

    std::string mouseText = std::format
    (
"\
Desktop Mouse Position: {},{}\n\
Render Window Mouse Position: {},{}\n\
Game Window Mouse Pixel Position: {},{}\n\
Game Window Mouse Pixel Coords: {},{}\n\
Game Window Mouse Tile Coords: {},{}\n\
Mouse Left Button Pressed: {}\n\
Mouse Dragging: {}\n\
",
        mousePositionInDesktop.x, mousePositionInDesktop.y,
        mousePositionInRenderWindow.x, mousePositionInRenderWindow.y,
        mousePixelPositionInGameWindow.x, mousePixelPositionInGameWindow.y,
        mousePixelCoordsInGameWindow.x, mousePixelCoordsInGameWindow.y,
        mouseTileCoordsInGameWindow.x, mouseTileCoordsInGameWindow.y,
        mouseIsLeftButtonPressed,
        mouseIsDragging
    );

    g_OverlayWindow.addTextToList(mouseText);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    tb::Joystick* joystick = g_JoystickManager.getJoystick();

    if (joystick->isConnected() == false)
    {
        std::string joystickDisconnectedText = std::format("Joystick Index {} is disconnected!\n", joystick->getIndex());

        g_OverlayWindow.addTextToList(joystickDisconnectedText);
    }
    else
    {
        tb::Joystick::State* joystickState = joystick->getState();

        std::string joystickButtonText;
        joystickButtonText.reserve(1024);

        for (unsigned int i = 0; i < sf::Joystick::ButtonCount; i++)
        {
            bool buttonState = joystickState->Button[i];

            if (buttonState == true)
            {
                joystickButtonText.append(std::format("Joystick Button {}: Pressed\n", i));
            }
        }

        if (joystickButtonText.empty() == false)
        {
            g_OverlayWindow.addTextToList(joystickButtonText);
        }

        std::string joystickAxisText = std::format
        (
"\
Joystick Axis X: {}\n\
Joystick Axis Y: {}\n\
Joystick Axis Z: {}\n\
Joystick Axis R: {}\n\
Joystick Axis U: {}\n\
Joystick Axis V: {}\n\
Joystick Axis POVX: {}\n\
Joystick Axis POVY: {}\n\
",
            joystickState->AxisX,
            joystickState->AxisY,
            joystickState->AxisZ,
            joystickState->AxisR,
            joystickState->AxisU,
            joystickState->AxisV,
            joystickState->AxisPOVX,
            joystickState->AxisPOVY
        );

        g_OverlayWindow.addTextToList(joystickAxisText);
    }
}

void Game::waitForKeyPress()
{
    g_Log.write("Press any key to continue...\n");

    std::cin.get();
}

void Game::exit()
{
    g_Log.write("Exiting...\n");

    ImGui::SFML::Shutdown();

    g_Log.close();

    waitForKeyPress();
}

void Game::run()
{
    g_Log.deleteFileContents();
    g_Log.open();
    g_Log.write("{} (Build: {} {})\n", tb::Constants::GameTitle, __DATE__, __TIME__);

    g_Log.write("Loading config\n");
    if (loadConfig() == false)
    {
        g_Log.write("ERROR: failed to load config\n");
        exit();
        return;
    }

    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    tb::Log::Properties* logProperties = g_Log.getProperties();
    logProperties->IsEnabled = optionsData->LogIsEnabled;
    logProperties->PrintToConsole = optionsData->LogPrintToConsole;
    logProperties->WriteToFile = optionsData->LogWriteToFile;

    g_Log.write("Creating render window\n");
    if (g_RenderWindow.create() == false)
    {
        g_Log.write("ERROR: failed to create render window\n");
        exit();
        return;
    }

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();
    if (renderWindow == nullptr)
    {
        g_Log.write("ERROR: renderWindow == nullptr\n");
        exit();
        return;
    }

    g_Log.write("Drawing loading text\n");
    g_GUI.drawLoadingText();

    g_Log.write("Initializing IMGUI\n");
    if (g_GUI.initializeIMGUI() == false)
    {
        g_Log.write("ERROR: failed to initialize IMGUI\n");
        exit();
        return;
    }

    g_Log.write("Loading data\n");
    if (loadData() == false)
    {
        g_Log.write("ERROR: failed to load data\n");
        exit();
        return;
    }

    g_Log.write("Loading resources\n");
    if (g_ResourceLoader.loadAll() == false)
    {
        g_Log.write("ERROR: failed to load resources\n");
        exit();
        return;
    }

    g_Log.write("Updating layout for SFML windows\n");
    g_GUI.SFMLWindows_updateLayout();

    g_Log.write("Updating joystick\n");

    sf::Joystick::update();
    g_JoystickManager.updateJoystickIndices();
    g_JoystickManager.updateJoystickProperties();

    g_Log.write("Initializing frames per second\n");
    initializeFramesPerSecond();

    g_Log.write("Starting rendering loop\n");

    while (renderWindow->isOpen() == true)
    {
        processEvents();

        // fixed in imgui-sfml 2.6
        //fixMouseCursorForWindowResize(renderWindow);

        ImGui::SFML::Update(*renderWindow, m_deltaClock.restart());

        renderWindow->clear(sf::Color::Black);

        g_GUI.drawWoodBackground();

        g_GUI.SFMLWindows_setPositionInLayout();

        if (m_gameState == tb::GameState::Testing)
        {
            doGameStateTesting();
        }
        else if (m_gameState == tb::GameState::EnterGame)
        {
            doGameStateEnterGame();
        }
        else if (m_gameState == tb::GameState::MapSelect)
        {
            doGameStateMapSelect();
        }
        else if (m_gameState == tb::GameState::LoadingMap)
        {
            doGameStateLoadingMap();
        }
        else if (m_gameState == tb::GameState::InGame)
        {
            doGameStateInGame();

            updateOverlayWindowText();
        }

        g_GUI.IMGUIWindows_draw();

        calculateFramesPerSecond();

        g_GUI.drawFramesPerSecond();

        ImGui::SFML::Render(*renderWindow);

        renderWindow->display();
    }

    exit();
}

void Game::endGame()
{
    setGameState(tb::GameState::EnterGame);
}

bool Game::isDeveloperModeEnabled()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    return optionsData->GameDeveloperMode;
}

void Game::toggleDeveloperMode()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    tb::Utility::toggleBool(optionsData->GameDeveloperMode);

    g_OptionsData.save();
}

bool Game::isDebugModeEnabled()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    return optionsData->GameDebugMode;
}

void Game::toggleDebugMode()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    tb::Utility::toggleBool(optionsData->GameDebugMode);

    g_OptionsData.save();
}

tb::GameState Game::getGameState()
{
    return m_gameState;
}

void Game::setGameState(tb::GameState gameState)
{
    m_gameState = gameState;
}

tb::Creature::Ptr Game::getPlayer()
{
    return m_player;
}

sf::Vector2i Game::getVectorByMovementDirection(tb::MovementDirection movementDirection)
{
    sf::Vector2i vector(0, 0);

    switch (movementDirection)
    {
        case tb::MovementDirection::Up:
            vector.y = -1;
            break;

        case tb::MovementDirection::Right:
            vector.x = 1;
            break;

        case tb::MovementDirection::Down:
            vector.y = 1;
            break;

        case tb::MovementDirection::Left:
            vector.x = -1;
            break;

        case tb::MovementDirection::UpLeft:
            vector.x = -1;
            vector.y = -1;
            break;

        case tb::MovementDirection::UpRight:
            vector.x++;
            vector.y = -1;
            break;

        case tb::MovementDirection::DownLeft:
            vector.x = -1;
            vector.y = 1;
            break;

        case tb::MovementDirection::DownRight:
            vector.x = 1;
            vector.y = 1;
            break;
    }

    return vector;
}

tb::MovementDirection Game::getMovementDirectionByVector(sf::Vector2i vector)
{
    tb::MovementDirection movementDirection = tb::MovementDirection::Null;

    if (vector.x == 0 && vector.y < 0)
    {
        movementDirection = tb::MovementDirection::Up;
    }
    else if (vector.x > 0 && vector.y == 0)
    {
        movementDirection = tb::MovementDirection::Right;
    }
    else if (vector.x == 0 && vector.y > 0)
    {
        movementDirection = tb::MovementDirection::Down;
    }
    else if (vector.x < 0 && vector.y == 0)
    {
        movementDirection = tb::MovementDirection::Left;
    }
    else if (vector.x < 0 && vector.y < 0)
    {
        movementDirection = tb::MovementDirection::UpLeft;
    }
    else if (vector.x > 0 && vector.y < 0)
    {
        movementDirection = tb::MovementDirection::UpRight;
    }
    else if (vector.x < 0 && vector.y > 0)
    {
        movementDirection = tb::MovementDirection::DownLeft;
    }
    else if (vector.x > 0 && vector.y > 0)
    {
        movementDirection = tb::MovementDirection::DownRight;
    }

    return movementDirection;
}

tb::Tile::Ptr Game::getTileByThingMovementDirection(tb::Thing::Ptr thing, tb::MovementDirection movementDirection)
{
    sf::Vector2i vectorByMovementDirection = getVectorByMovementDirection(movementDirection);

    tb::TileMap::Ptr tileMap = g_Map.getTileMapOfTilesAtAxisZ(thing->getAxisZ());

    if (tileMap == nullptr)
    {
        return nullptr;
    }

    tb::Tile::List* tileList = tileMap->getTileList();

    if (tileList == nullptr)
    {
        return nullptr;
    }

    tb::TileCoords tileCoords = tb::TileCoords(thing->getTileX() + vectorByMovementDirection.x, thing->getTileY() + vectorByMovementDirection.y);

    if (g_Map.isTileCoordsOutOfBounds(tileCoords) == true)
    {
        return nullptr;
    }

    tb::TileIndex tileIndex = g_Map.getTileIndexByTileCoords(tileCoords);

    if (g_Map.isTileIndexOutOfBounds(tileIndex) == true)
    {
        return nullptr;
    }

    return tileList->at(tileIndex);
}

bool Game::doesCeilingExistAbovePlayerAtAxisZ(tb::AxisZ axisZ)
{
    tb::TileMap::Ptr tileMap = g_Map.getTileMapOfTilesAtAxisZ(axisZ);

    if (tileMap == nullptr)
    {
        return false;
    }

    tb::Tile::List* tileList = tileMap->getTileList();

    if (tileList == nullptr)
    {
        return false;
    }

    if (tileList->size() == 0)
    {
        return false;
    }

    tb::TileCoord playerTileX = m_player->getTileX();
    tb::TileCoord playerTileY = m_player->getTileY();

    tb::AxisZ playerAxisZ = m_player->getAxisZ();

    std::vector<tb::TileIndex> tileIndexList;
    tileIndexList.reserve(16);

    for (int i = -2; i < 2; i++)
    {
        tb::TileCoords tileCoords1 = tb::TileCoords(playerTileX - 2, playerTileY + i);
        tb::TileCoords tileCoords2 = tb::TileCoords(playerTileX - 1, playerTileY + i);
        tb::TileCoords tileCoords3 = tb::TileCoords(playerTileX,     playerTileY + i);
        tb::TileCoords tileCoords4 = tb::TileCoords(playerTileX + 1, playerTileY + i);

        if (g_Map.isTileCoordsOutOfBounds(tileCoords1) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords1));
        }

        if (g_Map.isTileCoordsOutOfBounds(tileCoords2) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords2));
        }

        if (g_Map.isTileCoordsOutOfBounds(tileCoords3) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords3));
        }

        if (g_Map.isTileCoordsOutOfBounds(tileCoords4) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords4));
        }
    }

    for (tb::TileIndex tileIndex : tileIndexList)
    {
        if (g_Map.isTileIndexOutOfBounds(tileIndex) == true)
        {
            continue;
        }

        tb::Tile::Ptr tile = tileList->at(tileIndex);

        if (tile->getSpriteID() == tb::Constants::SpriteIDNull)
        {
            continue;
        }

        if (tile->getAxisZ() > playerAxisZ)
        {
            return true;
        }
    }

    return false;
}

void Game::handleCreatureMovement(tb::Creature::Ptr creature, tb::MovementDirection movementDirection)
{
    if (movementDirection == tb::MovementDirection::Null)
    {
        return;
    }

    tb::Creature::Properties* creatureProperties = creature->getProperties();

    if (creatureProperties->IsDead == true || creatureProperties->IsSleeping == true)
    {
        return;
    }

    sf::Time timeMovement = creature->getMovementClock()->getElapsedTime();

    if (timeMovement.asSeconds() < creature->getMovementSpeed())
    {
        return;
    }

    creature->setDirectionByMovementDirection(movementDirection);

    tb::Tile::Ptr toTile = getTileByThingMovementDirection(creature, movementDirection);

    if (toTile == nullptr)
    {
        return;
    }

    doMoveThingFromTileToTile(creature, toTile);

    creature->getMovementClock()->restart();

    creature->update();
}

bool Game::doMoveThingFromTileToTile(tb::Thing::Ptr thing, tb::Tile::Ptr toTile)
{
    tb::Tile::Ptr fromTile = g_Map.getTileAtThing(thing);

    if (fromTile == nullptr || toTile == nullptr)
    {
        return false;
    }

    tb::SpriteID toTileSpriteID = toTile->getSpriteID();

    if (toTileSpriteID == tb::Constants::SpriteIDNull)
    {
        return false;
    }

    tb::ThingType thingType = thing->getThingType();

    tb::AxisZ fromTileAxisZ = fromTile->getAxisZ();
    tb::AxisZ toTileAxisZ = toTile->getAxisZ();

    tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();

    tb::Object::List* toTileObjectList = toTile->getObjectList();

    for (auto& toTileObject : *toTileObjectList)
    {
        tb::SpriteID toTileObjectSpriteID = toTileObject->getSpriteID();

        tb::SpriteData::Data* toTileObjectSpriteData = &spriteDataList->at(toTileObjectSpriteID);

        tb::SpriteFlags* toTileObjectSpriteFlags = &toTileObjectSpriteData->SpriteFlags;

        // TODO: account for throwing items in water or dustbin, etc

        if (toTileObjectSpriteFlags->hasFlag(tb::SpriteFlag::Solid) == true)
        {
            return false;
        }
    }

    if (thingType == tb::ThingType::Creature)
    {
        tb::Creature::Ptr creature = std::static_pointer_cast<tb::Creature>(thing);

        tb::Creature::List* fromTileCreatureList = fromTile->getCreatureList();

        if (fromTileCreatureList->size() == 0)
        {
            return false;
        }

        auto fromTileCreatureIt = std::find(fromTileCreatureList->begin(), fromTileCreatureList->end(), creature);

        if (fromTileCreatureIt == fromTileCreatureList->end())
        {
            return false;
        }

        toTile->addCreature(creature);

        fromTileCreatureList->erase(fromTileCreatureIt);

        thing->setTileCoords(toTile->getTileCoords());
        thing->setAxisZ(toTileAxisZ);
    }

    // Object

    return true;
}

}
