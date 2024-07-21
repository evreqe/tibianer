#include "tb/BitmapFontTextBatch.h"

namespace tb
{

BitmapFontTextBatch::BitmapFontTextBatch()
{
    m_vertexList.reserve(m_maxVertices);

    m_numBitmapFontText = 0;
}

BitmapFontTextBatch::~BitmapFontTextBatch()
{
    //
}

bool BitmapFontTextBatch::addBitmapFontText(tb::BitmapFontText* bitmapFontText)
{
    tb::BitmapFont* bitmapFont = bitmapFontText->getBitmapFont();

    if (m_bitmapFont == nullptr)
    {
        m_bitmapFont = bitmapFont;
    }

    if (bitmapFont != m_bitmapFont)
    {
        g_Log.write("ERROR: bitmapFont != m_bitmapFont\n");
        g_Log.write("ERROR: BitmapFont of added text must match one set by batch\n");
        return false;
    }

    std::vector<sf::Vertex>* vertexList = bitmapFontText->getVertexList();

    if (vertexList == nullptr)
    {
        g_Log.write("ERROR: vertexList == nullptr\n");
        return false;
    }

    for (auto& vertex : *vertexList)
    {
        m_vertexList.push_back(vertex);
    }

    m_numBitmapFontText++;

    if (m_numBitmapFontText >= m_maxBitmapFontText)
    {
        m_maxBitmapFontText = m_maxBitmapFontText * 2;
        m_maxVertices = m_maxBitmapFontText * 4;

        m_vertexList.reserve(m_maxVertices);

        printDebugText();
    }

    return true;
}

void BitmapFontTextBatch::clear()
{
    m_vertexList.clear();

    m_numBitmapFontText = 0;
}

void BitmapFontTextBatch::printDebugText()
{
    g_Log.write("BitmapFontTextBatch Debug Text\n");

    g_Log.write("----> Max Bitmap Font Text:  {}\n", m_maxBitmapFontText);
    g_Log.write("----> Max Vertices: {}\n", m_maxVertices);

    g_Log.write("----> Vertex Count: {}\n", m_vertexList.size());

    g_Log.write("----> Num Bitmap Font Text:  {}\n", m_numBitmapFontText);
}

void BitmapFontTextBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_bitmapFont->getTexture();

    target.draw(&m_vertexList[0], m_vertexList.size(), sf::Quads, states);
}

bool BitmapFontTextBatch::setBitmapFont(tb::BitmapFont* bitmapFont)
{
    if (bitmapFont == nullptr)
    {
        g_Log.write("ERROR: bitmapFont == nullptr\n");
        return false;
    }

    m_bitmapFont = bitmapFont;

    return true;
}

tb::BitmapFont* BitmapFontTextBatch::getBitmapFont()
{
    return m_bitmapFont;
}

std::uint32_t BitmapFontTextBatch::getNumBitmapFontText()
{
    return m_numBitmapFontText;
}

}
