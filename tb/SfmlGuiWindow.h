#pragma once

#include "common.h"

#include "tb/Constants.h"

#include "tb/RenderWindow.h"

namespace tb
{

class SfmlGuiWindow
{

public:

    SfmlGuiWindow();
    ~SfmlGuiWindow();

    void initalize();

    void drawToRenderWindow();

    sf::FloatRect getRect();

    sf::Vector2f getMousePixelPosition();

    sf::Vector2f getMousePixelCoords();
    sf::Vector2i getMouseTileCoords();

    bool isMouseInsideWindow();

    sf::Vector2f getPosition();
    void setPosition(const sf::Vector2f& position);

    sf::View* getView();

    sf::Vector2f getViewInitialSize();
    void setViewInitialSize(sf::Vector2f size);

    sf::Vector2f getViewPosition();
    void setViewPosition(sf::Vector2f position);

    sf::Vector2f getViewPositionOffset();
    void setViewPositionOffset(sf::Vector2f offset);

    void resetViewPositionOffset();

    sf::RenderTexture* getWindowRenderTexture();

    sf::Vector2i getWindowRenderTextureInitialSize();
    void setWindowRenderTextureInitialSize(sf::Vector2i size);

    sf::Sprite* getWindowSprite();

    sf::FloatRect getRectOfSprite(const sf::Sprite& sprite);

    float getSizeScale();
    void setSizeScale(float scale);
    void clampSizeScale(float& scale);

    float getSizeScaleStep();
    float getSizeScaleMinimum();
    float getSizeScaleMaximum();

    bool isSized();
    void sizeReset();

    float getZoomScale();
    void setZoomScale(float scale);
    void clampZoomScale(float& scale);

    float getZoomScaleStep();
    float getZoomScaleMinimum();
    float getZoomScaleMaximum();

    bool isZoomed();
    void zoomIn();
    void zoomOut();
    void zoomReset();

private:

    sf::Vector2f m_position;

    sf::View m_view;
    sf::Vector2f m_viewInitialSize;
    sf::Vector2f m_viewPositionOffset;

    sf::RenderTexture m_windowRenderTexture;
    sf::Vector2i m_windowRenderTextureInitialSize;
    sf::Sprite m_windowSprite;

    float m_sizeScale = 1.0f;
    const float m_sizeScaleDefault = 1.0f;
    const float m_sizeScaleStep = 1.0f;
    const float m_sizeScaleMinimum = 1.0f;
    const float m_sizeScaleMaximum = 100.0f;

    float m_zoomScale = 1.0f;
    const float m_zoomScaleDefault = 1.0f;
    const float m_zoomScaleStep = 1.0f;
    const float m_zoomScaleMinimum = 1.0f;
    const float m_zoomScaleMaximum = 10.0f;

};

}
