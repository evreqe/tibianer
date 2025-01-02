#include "tb/LightBatch.h"

namespace tb
{

LightBatch::LightBatch()
{
    m_vertexList.resize(m_maxVertices);

    m_numLights = 0;
}

LightBatch::~LightBatch()
{
    //
}

bool LightBatch::addLight(sf::Vector2f position, sf::Color color)
{
    const float tileSize = tb::Constants::TileSizeAsFloat;

    const std::uint32_t numVertices = m_numLights * m_numVertexPerLight;

    sf::Vertex* vertex = &m_vertexList[numVertices];

    vertex[0].position = sf::Vector2f(position.x,            position.y);
    vertex[1].position = sf::Vector2f(position.x + tileSize, position.y);
    vertex[2].position = sf::Vector2f(position.x,            position.y + tileSize);
    vertex[3].position = sf::Vector2f(position.x,            position.y + tileSize);
    vertex[4].position = sf::Vector2f(position.x + tileSize, position.y);
    vertex[5].position = sf::Vector2f(position.x + tileSize, position.y + tileSize);

    vertex[0].color = color;
    vertex[1].color = color;
    vertex[2].color = color;
    vertex[3].color = color;
    vertex[4].color = color;
    vertex[5].color = color;

    m_numLights++;

    if (m_numLights >= m_maxLights)
    {
        m_maxLights = m_maxLights * 2;
        m_maxVertices = m_maxLights * m_numVertexPerLight;

        m_vertexList.resize(m_maxVertices);

        printDebugText();
    }

    return true;
}

void LightBatch::clear()
{
    m_vertexList.clear();

    m_numLights = 0;
}

void LightBatch::printDebugText()
{
    g_Log.write("LightBatch Debug Text\n");

    g_Log.write("----> Max Lights:  {}\n", m_maxLights);
    g_Log.write("----> Max Vertices: {}\n", m_maxVertices);

    g_Log.write("----> Vertex List Size: {}\n", m_vertexList.size());

    g_Log.write("----> Num Lights:  {}\n", m_numLights);
}

void LightBatch::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
{
    renderTarget.draw(&m_vertexList[0], m_vertexList.size(), sf::PrimitiveType::Triangles, renderStates);
}

std::uint32_t LightBatch::getNumLights()
{
    return m_numLights;
}

}
