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

    void Walls::full(const Context & t_context)
    {
        for (int x{ 1 }; x < static_cast<int>(t_context.layout.cellCount().x - 1u); ++x)
        {
            t_context.actors.add(t_context, Actor::Wall, { x, 0 });

            t_context.actors.add(
                t_context,
                Actor::Wall,
                { x, static_cast<int>(t_context.layout.cellCount().y - 1u) });
        }

        halfVert(t_context);
    }

    void Walls::fullWithHoles(const Context & t_context)
    {
        full(t_context);

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

} // namespace snake2
