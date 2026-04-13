#include <tb/LibSFML.h>

namespace tb::LibSFML
{

float calculateDistance2f(sf::Vector2f position1, sf::Vector2f position2)
{
    return std::sqrtf(std::powf(position1.x - position2.x, 2.0f) + std::powf(position1.y - position2.y, 2.0f));
}

float calculateDistance3f(sf::Vector3f position1, sf::Vector3f position2)
{
    return std::sqrtf(std::powf(position1.x - position2.x, 2.0f) + std::powf(position1.y - position2.y, 2.0f) + std::powf(position1.z - position2.z, 2.0f));
}

sf::Vector2i getDistanceBetweenPositions2i(const sf::Vector2i& position1, const sf::Vector2i& position2)
{
    sf::Vector2i distance;

    distance.x = std::abs(position1.x - position2.x);
    distance.y = std::abs(position1.y - position2.y);

    return distance;
}

sf::Vector2f getDistanceBetweenPositions2f(const sf::Vector2f& position1, const sf::Vector2f& position2)
{
    sf::Vector2f distance;

    distance.x = std::fabs(position1.x - position2.x);
    distance.y = std::fabs(position1.y - position2.y);

    return distance;
}

bool isPositionInsideCircle(sf::Vector2f position, sf::Vector2f circleCenter, float circleRadius, float& outDistance)
{
    outDistance = calculateDistance2f(position, circleCenter);

    return outDistance <= circleRadius;
}

}
