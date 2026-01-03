#pragma once

#include "common.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace tb
{

namespace LibSfml
{

float calculateDistance2D(sf::Vector2f position1, sf::Vector2f position2);
float calculateDistance3D(sf::Vector3f position1, sf::Vector3f position2);

bool isPositionInsideCircle(sf::Vector2f position, sf::Vector2f center, float radius, float& distance);

}

}
