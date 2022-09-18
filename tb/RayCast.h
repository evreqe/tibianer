#ifndef TIBIA_RAYCAST_HPP
#define TIBIA_RAYCAST_HPP

#include <set>

#include <SFML/System.hpp>

#include "tibia/Tibia.hpp"
#include "tibia/Utility.hpp"

namespace tibia
{

class RayCast
{

public:

    // Bresenham's line algorithm
    void doLine(int x1, int y1, const int x2, const int y2)
    {
        m_points.clear();

        int delta_x(x2 - x1);

        signed char const ix((delta_x > 0) - (delta_x < 0));
        delta_x = std::abs(delta_x) << 1;
 
        int delta_y(y2 - y1);

        signed char const iy((delta_y > 0) - (delta_y < 0));
        delta_y = std::abs(delta_y) << 1;
 
        addPoint(x1, y1);
 
        if (delta_x >= delta_y)
        {
            int error(delta_y - (delta_x >> 1));
 
            while (x1 != x2)
            {
                if ((error >= 0) && (error || (ix > 0)))
                {
                    error -= delta_x;
                    y1 += iy;
                }
 
                error += delta_y;
                x1 += ix;
 
                addPoint(x1, y1);
            }
        }
        else
        {
            int error(delta_x - (delta_y >> 1));
 
            while (y1 != y2)
            {
                if ((error >= 0) && (error || (iy > 0)))
                {
                    error -= delta_y;
                    x1 += ix;
                }

                error += delta_x;
                y1 += iy;
 
                addPoint(x1, y1);
            }
        }
    }

    void addPoint(int x, int y)
    {
        int tileX = x;
        int tileY = y;

        tileX = tileX - (tileX % tibia::TILE_SIZE);
        tileY = tileY - (tileY % tibia::TILE_SIZE);

        auto pointIt = std::find_if
        (
            m_points.begin(),
            m_points.end(),
            [tileX, tileY](sf::Vector2u const& p)
            { 
                return p.x == tileX && p.y == tileY;
            }
        );

        if (pointIt != m_points.end())
        {
            return;
        }

        m_points.push_back(sf::Vector2u(tileX, tileY));
    }

    std::vector<sf::Vector2u>* getPoints()
    {
        return &m_points;
    }

private:

    std::vector<sf::Vector2u> m_points;

};

} // namespace Tibia

#endif // TIBIA_RAYCAST_HPP
