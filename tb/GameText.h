#pragma once

#include "common.h"

#include <boost/algorithm/string.hpp>

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/BitmapFont.h"
#include "tb/BitmapFontText.h"

namespace tb
{

class GameText : public sf::Drawable, public sf::Transformable
{

public:

    GameText();
    ~GameText();

    bool setText(tb::BitmapFont* bitmapFont, const sf::Vector2i& tileCoords, tb::ZAxis_t z, const std::string& text, const sf::Color& textColor, bool isCentered = true);

    sf::Vector2i getTileCoords();

    tb::ZAxis_t getZ();

    std::string getText();

    sf::Color* getTextColor();

    std::vector<std::string>* getTextList();

    sf::Clock* getClock();

private:

    sf::Texture* m_texture = nullptr;

    sf::Vector2i m_tileCoords;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    std::string m_text;

    sf::Color m_textColor;

    int m_type = 0; // TODO: speech type: yelling, whispering, broadcasting, monster, etc

    std::vector<std::string> m_textList;

    std::vector<tb::BitmapFontText> m_bitmapFontTextList;

    sf::Clock m_clock;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

}