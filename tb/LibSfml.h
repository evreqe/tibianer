#pragma once

#include "common.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace tb::LibSFML
{

float calculateDistance2f(sf::Vector2f position1, sf::Vector2f position2);
float calculateDistance3f(sf::Vector3f position1, sf::Vector3f position2);

sf::Vector2i getDistanceBetweenPositions2i(const sf::Vector2i& position1, const sf::Vector2i& position2);
sf::Vector2f getDistanceBetweenPositions2f(const sf::Vector2f& position1, const sf::Vector2f& position2);

bool isPositionInsideCircle(sf::Vector2f position, sf::Vector2f circleCenter, float circleRadius, float& outDistance);

}
