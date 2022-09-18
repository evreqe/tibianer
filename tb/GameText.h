#pragma once

#include "common.h"

#include <boost/algorithm/string.hpp>

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"
#include "tb/Utility.h"

#include "tb/BitmapFont.h"
#include "tb/BitmapFontText.h"

namespace tb
{

class GameText : public sf::Drawable, public sf::Transformable
{

public:

    GameText();
    ~GameText();

    void setText(tb::BitmapFont& bitmapFont, sf::Vector2u tileCoords, tb::ZAxis_t z, const std::string& text, sf::Color textColor, bool isCentered = true);

    tb::ZAxis_t getZ();

    sf::Vector2u getTilePosition();

    std::string getText();

    sf::Color* getTextColor();

    unsigned int getNumTextLines();

    std::vector<std::string>* getTextList();

    sf::Clock* getClock();

private:

    sf::Texture* m_texture = nullptr;

    sf::Vector2u m_tilePosition;

    std::string m_text;

    sf::Color m_textColor;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    int m_type = 0; // ? speech type, yelling, etc

    unsigned int m_numTextLines = 0;

    std::vector<std::string> m_textList;

    std::vector<tb::BitmapFontText> m_bitmapFontTextList;

    sf::Clock m_clock;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

}