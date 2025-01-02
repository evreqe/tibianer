#pragma once

#include "common.h"

#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class BitmapFont
{

public:

    BitmapFont();
    ~BitmapFont();

    bool load(const std::string& fileName, const sf::Vector2u& glyphSize, std::int32_t characterSpace, std::int32_t characterHeight, std::vector<std::int32_t>* characterWidthList);

    sf::VertexArray* getVertexArray();
    sf::Texture* getTexture();
    sf::Vector2u getGlyphSize();
    std::int32_t getCharacterSpace();
    std::int32_t getCharacterHeight();
    std::vector<std::int32_t>* getCharacterWidthList();

private:

    sf::VertexArray m_vertexArray;
    sf::Texture m_texture;
    sf::Vector2u m_glyphSize;
    std::int32_t m_characterSpace = 0;
    std::int32_t m_characterHeight = 1;
    std::vector<std::int32_t> m_characterWidthList;

    static const std::uint32_t m_numVertexPerGlyph = 6;

};

}
