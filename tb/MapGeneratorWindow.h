#pragma once

#include "common.h"

#include "tb/IMGUIWindow.h"

#include "tb/MapGenerator.h"

namespace tb
{

class MapGeneratorWindow : public tb::IMGUIWindow
{

public:

    MapGeneratorWindow();
    ~MapGeneratorWindow();

    static MapGeneratorWindow& getInstance()
    {
        static MapGeneratorWindow instance;
        return instance;
    }

private:

    MapGeneratorWindow(const MapGeneratorWindow&) = delete;
    MapGeneratorWindow(MapGeneratorWindow&&) = delete;
    MapGeneratorWindow& operator=(const MapGeneratorWindow&) = delete;
    MapGeneratorWindow& operator=(MapGeneratorWindow&&) = delete;

public:

    void onLoad();

    void draw();

private:

    bool m_isLoaded = false;

    bool m_isSelectedImageTextureLoaded = false;

    const std::string m_imageFolder = "map_generator/images/";

    const std::string m_imageFileNameExtension = ".png";

    tb::MapGenerator::Map_t m_map;

    std::uint32_t m_selectedListBoxIndex = 0;

    std::string m_selectedImageFileName;

    std::string m_selectedImageFilePath;

    sf::Texture m_selectedImageTexture;

    sf::Vector2f m_selectedImageSize = sf::Vector2f(256.0f, 256.0f);

    const float m_listBoxWidth = 320.0f;

    const float m_inputTextWidth = 320.0f;

    const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

};

}

namespace
{
    inline tb::MapGeneratorWindow& g_MapGeneratorWindow = tb::MapGeneratorWindow::getInstance();
}
