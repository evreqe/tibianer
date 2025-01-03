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
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates);

    std::uint32_t getNumLights();

private:

    std::vector<sf::Vertex> m_vertexList;

    std::uint32_t m_numLights = 0;

    std::uint32_t m_maxLights = 4096;

    const uint32_t m_numVertexPerLight = 6;

    std::uint32_t m_maxVertices = m_maxLights * m_numVertexPerLight;
};

}