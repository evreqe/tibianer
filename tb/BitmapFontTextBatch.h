#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Log.h"

#include "tb/BitmapFontText.h"

namespace tb
{

class BitmapFontTextBatch : public sf::Drawable, public sf::Transformable
{

public:

    BitmapFontTextBatch();
    ~BitmapFontTextBatch();

    bool addBitmapFontText(tb::BitmapFontText* bitmapFontText);
    void clear();
    void printDebugText();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool setBitmapFont(tb::BitmapFont* bitmapFont);
    tb::BitmapFont* getBitmapFont();

    uint32_t getNumBitmapFontText();

private:

    tb::BitmapFont* m_bitmapFont = nullptr;

    std::vector<sf::Vertex> m_vertexList;

    uint32_t m_numBitmapFontText = 0;

    uint32_t m_maxVertices = 4096; // 1024 * 4;

    uint32_t m_maxBitmapFontText = 1024;
};

}