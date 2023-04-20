#pragma once

#include "common.h"

#include "tb/Constants.h"

namespace tb
{
    namespace Utility
    {
        static std::random_device randomDevice;
        static std::default_random_engine randomEngine(randomDevice());

        template <typename P, typename R>
        static bool isPositionInsideRectangle(const sf::Vector2<P>& position, const sf::Rect<R>& rect)
        {
            if (position.x < rect.left)                   return false;
            if (position.y < rect.top)                    return false;
            if (position.x > (rect.left + rect.width))    return false;
            if (position.y > (rect.top + rect.height))    return false;

            return true;
        }

        static bool isPositionInsideCircle(sf::Vector2f center, sf::Vector2f position, float radius, float& distance)
        {
            float dx = center.x - position.x;
            float dy = center.y - position.y;

            distance = std::sqrtf(dx * dx + dy * dy);

            return distance <= radius;

            //float distanceSquared = dx * dx + dy * dy;

            //distance = ?

            //return distanceSquared <= radius * radius;
        }

        template <typename E>
        constexpr auto toUnderlying(E e) noexcept
        {
            return static_cast<std::underlying_type_t<E>>(e);
        }

        static void toggleBool(bool& b)
        {
            b = !b;
        }

        static float calculateDistance(float x1, float y1, float x2, float y2)
        {
            return std::sqrtf(std::powf(x1 - x2, 2) + std::powf(y1 - y2, 2));
        }

        static uint32_t getRandomNumber(uint32_t min, uint32_t max)
        {
            std::uniform_int_distribution<uint32_t> uniformDistribution(min, max);

            return uniformDistribution(randomEngine);
        }

        static float getRandomNumberFloat(float min, float max)
        {
            std::uniform_real_distribution<float> uniformDistribution(min, max);

            return uniformDistribution(randomEngine);
        }

        namespace String
        {
            static void removeNullTerminator(std::string& text)
            {
                text.erase(std::remove(text.begin(), text.end(), '\0'), text.end());
            }

            static void removeWhiteSpace(std::string& text)
            {
                text.erase
                (
                    std::remove_if
                    (
                        text.begin(), text.end(),
                        [](char c)
                        {
                            return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f');
                        }
                    ),
                    text.end()
                );
            }
        }
    }
}
