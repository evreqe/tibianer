#pragma once

#include <cstdint>
#include <cmath>

#include <iostream>
#include <format>
#include <fstream>
#include <random>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"

namespace tb
{
    // temporary function until std::print in C++23 or later
    template<typename... Args>
    constexpr void print(const std::string_view str_fmt, Args&&... args)
    {
        fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
    }

    static void printError(const std::string_view text, const std::source_location sl = std::source_location::current())
    {
        std::cout << "ERROR: " << sl.file_name() << ":" << sl.line() << ":" << sl.function_name() << ": " << text;
    }

    namespace Utility
    {
        static std::random_device randomDevice;
        static std::default_random_engine randomEngine(randomDevice());

        static sf::IntRect GetSpriteRectByID(tb::SpriteID_t id, uint8_t tileWidth, uint8_t tileHeight)
        {
            // index in the spritesheet starts at 1
            id = id - 1;

            int u = (id % (tb::Textures::Sprites.getSize().x / tb::Constants::TileSize)) * tb::Constants::TileSize;
            int v = (id / (tb::Textures::Sprites.getSize().y / tb::Constants::TileSize)) * tb::Constants::TileSize;

            u = u - ((tileWidth - 1) * tb::Constants::TileSize);
            v = v - ((tileHeight - 1) * tb::Constants::TileSize);

            return sf::IntRect(u, v, tb::Constants::TileSize * tileWidth, tb::Constants::TileSize * tileHeight);
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

        static void eraseNullTerminator(std::string& text)
        {
            text.erase(std::remove(text.begin(), text.end(), '\0'), text.end());
        }
    }
}
