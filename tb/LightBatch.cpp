#include "tb/LightBatch.h"

namespace tb
{

    LightBatch::LightBatch()
    {
        m_vertexArray.setPrimitiveType(sf::Quads);
        m_vertexArray.resize(m_maxVertices);

        m_numLights = 0;
    }

    LightBatch::~LightBatch()
    {
        //
    }

    bool LightBatch::addLight(sf::Vector2f position, sf::Color color)
    {
        sf::Vertex* vertex = &m_vertexArray[m_numLights * 4];

        // top left, top right, bottom right, bottom left
        vertex[0].position = sf::Vector2f(position.x,                                position.y);
        vertex[1].position = sf::Vector2f(position.x + tb::Constants::TileSizeFloat, position.y);
        vertex[2].position = sf::Vector2f(position.x + tb::Constants::TileSizeFloat, position.y + tb::Constants::TileSizeFloat);
        vertex[3].position = sf::Vector2f(position.x,                                position.y + tb::Constants::TileSizeFloat);

        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[3].color = color;

        m_numLights++;

        if (m_numLights >= m_maxLights)
        {
            m_maxLights = m_maxLights * 2;
            m_maxVertices = m_maxLights * 4;

            m_vertexArray.resize(m_maxVertices);

            printDebugText();
        }

        return true;
    }

    void LightBatch::clear()
    {
        m_vertexArray.clear();

        m_numLights = 0;
    }

    void LightBatch::printDebugText()
    {
        g_Log.write("LightBatch Debug Text\n");

        g_Log.write("----> Max Lights:  {}\n", m_maxLights);
        g_Log.write("----> Max Vertices: {}\n", m_maxVertices);

        g_Log.write("----> Vertex Count: {}\n", m_vertexArray.getVertexCount());

        g_Log.write("----> Num Lights:  {}\n", m_numLights);
    }

    void LightBatch::draw(sf::RenderTarget& target, sf::RenderStates states)
    {
        target.draw(m_vertexArray, states);
    }

    uint32_t LightBatch::getNumLights()
    {
        return m_numLights;
    }

}
