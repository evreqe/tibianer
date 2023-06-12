#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Log.h"

namespace tb
{

class LightBatch
{

public:

    LightBatch();
    ~LightBatch();

    bool addLight(sf::Vector2f position, sf::Color color);
    void clear();
    void printDebugText();
    void draw(sf::RenderTarget& target, sf::RenderStates states);

    uint32_t getNumLights();

private:

    sf::VertexArray m_vertexArray;

    uint32_t m_numLights = 0;

    uint32_t m_maxVertices = 4096; // 1024 * 4;

    uint32_t m_maxLights = 1024;
};

}