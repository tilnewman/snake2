//
// actors.cpp
//
#include "actors.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "snake.hpp"

#include <algorithm>

namespace snake2
{

    Actors::Actors()
        : m_actors{}
    {}

    void Actors::setup(const Context & t_context)
    {
        m_actors.reserve(t_context.layout.cellCount().x * t_context.layout.cellCount().y);
    }

    void Actors::add(const Context & t_context, const Actor t_type, const GridPos_t & t_gridPos)
    {
        m_actors.push_back(makeActor(t_context, t_type, t_gridPos));
    }

    void Actors::remove(const GridPos_t & t_gridPos)
    {
        std::erase_if(m_actors, [&](const std::unique_ptr<IActor> & actorUPtr) {
            return (actorUPtr->position() == t_gridPos);
        });
    }

    void Actors::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        for (auto & actorUPtr : m_actors)
        {
            actorUPtr->handleEvent(t_context, t_event);
        }
    }

    void Actors::update(const Context & t_context, const float t_elpasedTimeSec)
    {
        for (auto & actorUPtr : m_actors)
        {
            actorUPtr->update(t_context, t_elpasedTimeSec);
        }
    }

    void Actors::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        for (const auto & actorUPtr : m_actors)
        {
            actorUPtr->draw(t_context, t_target, t_states);
        }
    }

    const GridPosVec_t Actors::findFreePositions(const Context & t_context) const
    {
        GridPosVec_t positions;
        positions.reserve(t_context.layout.cellCount().x * t_context.layout.cellCount().y);

        const sf::Vector2i cellCounts{ t_context.layout.cellCount() };
        for (int y{ 0 }; y < cellCounts.y; ++y)
        {
            for (int x{ 0 }; x < cellCounts.x; ++x)
            {
                positions.emplace_back(x, y);
            }
        }

        for (const auto & actorUPtr : m_actors)
        {
            std::erase(positions, actorUPtr->position());
        }

        const GridPosVec_t snakePositions{ t_context.snake.positions() };
        for (const GridPos_t & gridPos : snakePositions)
        {
            std::erase(positions, gridPos);
        }

        return positions;
    }

    bool Actors::eat(const Context & t_context, const GridPos_t & t_gridPos)
    {
        for (auto & actorUPtr : m_actors)
        {
            if (actorUPtr->position() == t_gridPos)
            {
                return actorUPtr->onEat(t_context);
            }
        }

        return false;
    }

    const std::optional<Actor> Actors::findNonWallAtPosition(const GridPos_t & t_gridPos) const
    {
        for (const auto & actorUPtr : m_actors)
        {
            if ((actorUPtr->position() == t_gridPos) && (actorUPtr->type() != Actor::Wall))
            {
                return actorUPtr->type();
            }
        }

        return {};
    }

    std::size_t Actors::findNonWallCountSurrounding(const GridPos_t & t_gridPos) const
    {
        std::size_t count{ 0 };

        if (findNonWallAtPosition(t_gridPos + GridPos_t{ -1, 0 }).has_value())
        {
            ++count;
        }

        if (findNonWallAtPosition(t_gridPos + GridPos_t{ 1, 0 }).has_value())
        {
            ++count;
        }

        if (findNonWallAtPosition(t_gridPos + GridPos_t{ 0, -1 }).has_value())
        {
            ++count;
        }

        if (findNonWallAtPosition(t_gridPos + GridPos_t{ 0, 1 }).has_value())
        {
            ++count;
        }

        return count;
    }

    std::unique_ptr<IActor> Actors::makeActor(
        const Context & t_context, const Actor t_type, const GridPos_t & t_gridPos)
    {
        // clang-format off
        switch (t_type)
        {
            case Actor::Food:   { return std::make_unique<Food>(t_context, t_gridPos); }
            case Actor::Wall:   { return std::make_unique<Wall>(t_context, t_gridPos); }
            case Actor::Shrink: { return std::make_unique<Shrink>(t_context, t_gridPos); }
            case Actor::Slow:   { return std::make_unique<Slow>(t_context, t_gridPos); }
            case Actor::Fast:   { return std::make_unique<Fast>(t_context, t_gridPos); }
            default:
            {
                throw std::runtime_error("makeActor() failed because given unknown Actor t_type!");
            }
        }
        // clang-format on
    }

} // namespace snake2
