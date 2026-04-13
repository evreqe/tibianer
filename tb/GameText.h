#pragma once

#include "common.h"

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

    bool setText(tb::BitmapFont* bitmapFont, const tb::TileCoords& tileCoords, tb::AxisZ axisZ, const std::string& text, const sf::Color& textColor, bool isCentered = true);

    tb::TileCoords getTileCoords();

    tb::AxisZ getAxisZ();

    std::string getText();

    sf::Color* getTextColor();

    std::vector<std::string>* getTextList();

    sf::Clock* getClock();

private:

    sf::Texture* m_texture = nullptr;

    tb::TileCoords m_tileCoords;

    tb::AxisZ m_axisZ = tb::Constants::AxisZDefault;

    std::string m_text;

    sf::Color m_textColor;

    int m_type = 0; // TODO: speech type: yelling, whispering, broadcasting, monster, etc

    std::vector<std::string> m_textList;

    std::vector<tb::BitmapFontText> m_bitmapFontTextList;

    sf::Clock m_clock;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

}