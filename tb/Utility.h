#pragma once

#include "common.h"

#include "tb/Constants.h"

#include <SFML/Graphics.hpp>

namespace tb
{
    namespace Utility
    {
        static std::random_device randomDevice;
        static std::default_random_engine randomEngine(randomDevice());

        static sf::IntRect getSpriteRectByID(tb::SpriteID_t id, uint8_t tileWidth, uint8_t tileHeight)
        {
            // index in the spritesheet starts at 1
            id = id - 1;

            int u = (id % (tb::Textures::Sprites.getSize().x / tb::Constants::TileSize)) * tb::Constants::TileSize;
            int v = (id / (tb::Textures::Sprites.getSize().y / tb::Constants::TileSize)) * tb::Constants::TileSize;

            u = u - ((tileWidth - 1) * tb::Constants::TileSize);
            v = v - ((tileHeight - 1) * tb::Constants::TileSize);

            return sf::IntRect(u, v, (tileWidth * tb::Constants::TileSize), (tileHeight * tb::Constants::TileSize));
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

        static bool fileExists(const std::string& fileName)
        {
            std::ifstream file(fileName.c_str());
            return file.good();
        }

        static float calculateDistance(float x1, float y1, float x2, float y2)
        {
            return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
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
