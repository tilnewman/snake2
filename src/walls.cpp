// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// walls.cpp
//
#include "walls.hpp"

#include "actors.hpp"
#include "context.hpp"
#include "layout.hpp"

namespace snake2
{

    void Walls::halfHoriz(const Context & t_context)
    {
        for (int x{ 0 }; x < static_cast<int>(t_context.layout.cellCount().x); ++x)
        {
            t_context.actors.add(t_context, Actor::Wall, { x, 0 });

            t_context.actors.add(
                t_context,
                Actor::Wall,
                { x, static_cast<int>(t_context.layout.cellCount().y - 1u) });
        }
    }

    void Walls::halfVert(const Context & t_context)
    {
        for (int y{ 0 }; y < static_cast<int>(t_context.layout.cellCount().y); ++y)
        {
            t_context.actors.add(t_context, Actor::Wall, { 0, y });

            t_context.actors.add(
                t_context,
                Actor::Wall,
                { static_cast<int>(t_context.layout.cellCount().x - 1u), y });
        }
    }

    void Walls::cutHolesInBorderWalls(const Context & t_context)
    {
        const sf::Vector2i cellCount{ t_context.layout.cellCount() };

        {
            const int length{ cellCount.x / 3 };
            for (int x{ 0 }; x < length; ++x)
            {
                t_context.actors.remove({ (length + x), 0 });
                t_context.actors.remove({ (length + x), (cellCount.y - 1) });
            }
        }

        {
            const int length{ cellCount.y / 3 };
            for (int y{ 0 }; y < length; ++y)
            {
                t_context.actors.remove({ 0, (length + y) });
                t_context.actors.remove({ (cellCount.x - 1), (length + y) });
            }
        }
    }

    void Walls::centerBlock(const Context & t_context)
    {
        const sf::Vector2i cellCount{ t_context.layout.cellCount() };
        const sf::Vector2i blockDimm{ cellCount / 3 };

        for (int y{ 0 }; y < blockDimm.y; ++y)
        {
            for (int x{ 0 }; x < blockDimm.x; ++x)
            {
                t_context.actors.add(t_context, Actor::Wall, { blockDimm + sf::Vector2i{ x, y } });
            }
        }
    }

    void Walls::full(const Context & t_context, const std::size_t t_thickness)
    {
        const int thicknessInt{ static_cast<int>(t_thickness) };

        for (int y{ 0 }; y < thicknessInt; ++y)
        {
            for (int x{ y }; x < static_cast<int>(t_context.layout.cellCount().x - y); ++x)
            {
                t_context.actors.add(t_context, Actor::Wall, { x, y });
                
                t_context.actors.add(
                    t_context,
                    Actor::Wall,
                    { x, static_cast<int>(t_context.layout.cellCount().y - (y + 1)) });
            }
        }

        for (int x{ 0 }; x < thicknessInt; ++x)
        {
            for (int y{ x }; y < static_cast<int>(t_context.layout.cellCount().y - x); ++y)
            {
                t_context.actors.add(t_context, Actor::Wall, { x, y });

                t_context.actors.add(
                    t_context,
                    Actor::Wall,
                    { static_cast<int>(t_context.layout.cellCount().x - (x + 1)), y });
            }
        }
    }

} // namespace snake2
