//
// snake.cpp
//
#include "snake.hpp"

#include "actors.hpp"
#include "context.hpp"
#include "grid-display.hpp"
#include "keys.hpp"
#include "layout.hpp"
#include "sound-player.hpp"
#include "util.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace snake2
{

    Snake::Snake()
        : m_positions{}
        , m_direction{ sf::Keyboard::Scancode::Left }
        , m_elapsedTimeSec{ 0.0f }
        , m_timeBetweenMovesSec{ 0.125f }
        , m_isAlive{ true }
        , m_toGrowCount{ 0 }
    {}

    void Snake::setup(const Context & t_context)
    {
        m_positions.reserve(t_context.layout.cellCount().x * t_context.layout.cellCount().y);

        // start the snake in the center of the screen horizontally
        const int vertPos{ static_cast<int>(t_context.layout.cellCount().y / 2u) };
        const int leftMostPos{ static_cast<int>(t_context.layout.cellCount().x / 3u) };
        for (unsigned x{ 0 }; x < (t_context.layout.cellCount().x / 4); ++x)
        {
            m_positions.emplace_back(leftMostPos + static_cast<int>(x), vertPos);
        }
    }

    void Snake::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        m_elapsedTimeSec += t_elapsedTimeSec;
        if (m_elapsedTimeSec > m_timeBetweenMovesSec)
        {
            m_elapsedTimeSec -= m_timeBetweenMovesSec;
            move(t_context);
        }
    }

    void Snake::handleEvent(const Context &, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (util::keys::isArrow(keyPtr->scancode))
            {
                m_direction = keyPtr->scancode;
            }
        }
    }

    void Snake::slower(const Context & t_context)
    {
        m_timeBetweenMovesSec *= (1.0f + t_context.config.snake_speed_change_ratio);
    }

    void Snake::faster(const Context & t_context)
    {
        m_timeBetweenMovesSec *= (1.0f - t_context.config.snake_speed_change_ratio);
    }

    void Snake::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        sf::RectangleShape rectangle;
        rectangle.setFillColor(t_context.config.cell_snake_first_color);

        for (const GridPos_t & position : m_positions)
        {
            const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
                t_context, position) };

            rectangle.setPosition(screenRect.position);
            rectangle.setSize(screenRect.size);

            t_target.draw(rectangle, t_states);
        }

        if (!m_isAlive && !m_positions.empty())
        {
            const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
                t_context, m_positions.front()) };

            rectangle.setPosition(screenRect.position);
            rectangle.setSize(screenRect.size);
            rectangle.setFillColor(t_context.config.cell_snake_death_color);

            t_target.draw(rectangle, t_states);
        }
    }

    void Snake::move(const Context & t_context)
    {
        if (m_positions.empty() || !m_isAlive)
        {
            return;
        }

        const GridPos_t newPos{ makeMovedPosition(t_context) };

        m_positions.insert(std::begin(m_positions), newPos);

        if (0 == m_toGrowCount)
        {
            m_positions.pop_back();
        }
        else
        {
            --m_toGrowCount;
        }

        // check for eating self
        if (m_positions.size() > 1)
        {
            for (std::size_t index{ 1 }; index < m_positions.size(); ++index)
            {
                if (newPos == m_positions.at(index))
                {
                    kill(t_context);
                    return;
                }
            }
        }

        // if not eating self, eat other Actors
        if (t_context.actors.eat(t_context, newPos))
        {
            t_context.actors.remove(newPos);
        }
    }

    const GridPos_t Snake::makeMovedPosition(const Context & t_context) const
    {
        const GridPos_t oldPos{ m_positions.front() };

        if (sf::Keyboard::Scancode::Left == m_direction)
        {
            GridPos_t newPos{ oldPos.x - 1, oldPos.y };
            if (newPos.x < 0)
            {
                newPos.x = static_cast<int>(t_context.layout.cellCount().x - 1);
            }
            return newPos;
        }
        else if (sf::Keyboard::Scancode::Right == m_direction)
        {
            GridPos_t newPos{ oldPos.x + 1, oldPos.y };
            if (newPos.x >= static_cast<int>(t_context.layout.cellCount().x))
            {
                newPos.x = 0;
            }
            return newPos;
        }
        else if (sf::Keyboard::Scancode::Up == m_direction)
        {
            GridPos_t newPos{ oldPos.x, oldPos.y - 1 };
            if (newPos.y < 0)
            {
                newPos.y = static_cast<int>(t_context.layout.cellCount().y - 1);
            }
            return newPos;
        }
        else
        {
            GridPos_t newPos{ oldPos.x, oldPos.y + 1 };
            if (newPos.y >= static_cast<int>(t_context.layout.cellCount().y))
            {
                newPos.y = 0;
            }
            return newPos;
        }
    }

    void Snake::kill(const Context & t_context)
    {
        m_isAlive = false;
        t_context.sfx.play("step-smash");
    }

    void Snake::shrink()
    {
        if (length() <= 1)
        {
            return;
        }

        std::size_t toShrinkCount{ length() / 2_st };
        if (m_toGrowCount >= toShrinkCount)
        {
            m_toGrowCount -= toShrinkCount;
            return;
        }
        else
        {
            toShrinkCount -= m_toGrowCount;
            while ((toShrinkCount-- > 0) && (length() > 1))
            {
                m_positions.pop_back();
            }
        }
    }

} // namespace snake2
