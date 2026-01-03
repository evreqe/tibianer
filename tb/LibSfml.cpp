#include <tb/LibSfml.h>

namespace tb
{

namespace LibSfml
{

float calculateDistance2D(sf::Vector2f position1, sf::Vector2f position2)
{
    return std::sqrtf(std::powf(position1.x - position2.x, 2.0f) + std::powf(position1.y - position2.y, 2.0f));
}

float calculateDistance3D(sf::Vector3f position1, sf::Vector3f position2)
{
    return std::sqrtf(std::powf(position1.x - position2.x, 2.0f) + std::powf(position1.y - position2.y, 2.0f) + std::powf(position1.z - position2.z, 2.0f));
}

bool isPositionInsideCircle(sf::Vector2f position, sf::Vector2f center, float radius, float& distance)
{
    float dx = center.x - position.x;
    float dy = center.y - position.y;

    distance = std::sqrtf(dx * dx + dy * dy);

    return distance <= radius;
}

}

}
