#pragma once

#include "tb/Constants.hpp"

namespace tb
{
    // temporary function until std::print in C++23 or later
    template<typename... Args>
    constexpr void print(const std::string_view str_fmt, Args&&... args)
    {
        fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
    }

    void printError(const std::string_view text, const std::source_location sl = std::source_location::current())
    {
        std::cout << "ERROR: " << sl.file_name() << ":" << sl.line() << ":" << sl.function_name() << ": " << text;
    }

    namespace Utility
    {
        sf::IntRect GetSpriteRectByID(tb::SpriteID_t id, uint8_t width, uint8_t height)
        {
            // index in the spritesheet starts at 1
            id = id - 1;

            int u = (id % (tb::Textures::Sprites.getSize().x / tb::Constants::TileSize)) * tb::Constants::TileSize;
            int v = (id / (tb::Textures::Sprites.getSize().y / tb::Constants::TileSize)) * tb::Constants::TileSize;

            u = u - ((width  - 1) * tb::Constants::TileSize);
            v = v - ((height - 1) * tb::Constants::TileSize);

            return sf::IntRect(u, v, tb::Constants::TileSize * width, tb::Constants::TileSize * height);
        }

        template <class T>
        std::optional<std::string> GetValueByKey(std::unordered_map<T, std::string>& map, T key)
        {
            auto it = map.find(key);
            if (it != map.end())
            {
                return it->second;
            }

            return std::nullopt;
        }

        template <class T>
        std::optional<T> GetKeyByValue(std::unordered_map<T, std::string>& map, const std::string& value)
        {
            for (auto it = map.begin(); it != map.end(); ++it)
            {
                if (it->second == value)
                {
                    return it->first;
                }
            }

            return std::nullopt;
        }
    }
}