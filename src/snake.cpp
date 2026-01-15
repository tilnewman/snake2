// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// snake.cpp
//
#include "snake.hpp"

#include "actors.hpp"
#include "color-range.hpp"
#include "context.hpp"
#include "game-info.hpp"
#include "grid-display.hpp"
#include "keys.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state.hpp"
#include "text-anim.hpp"
#include "top-panel.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace snake2
{

    Snake::Snake()
        : m_positions{}
        , m_direction{ sf::Keyboard::Scancode::Left }
        , m_elapsedTimeSec{ 0.0f }
        , m_timeBetweenMovesSec{ 0.0f }
        , m_isAlive{ true }
        , m_toGrowCount{ 0 }
    {}

    void Snake::setup(const Context & t_context)
    {
        m_positions.reserve(t_context.layout.cellCount().x * t_context.layout.cellCount().y);
        reset(t_context);
    }

    void Snake::reset(const Context & t_context)
    {
        m_positions.clear();

        m_isAlive             = true;
        m_toGrowCount         = 0;
        m_elapsedTimeSec      = 0.0f;
        m_timeBetweenMovesSec = calcTimeBetweenMoves(t_context);
        m_direction           = sf::Keyboard::Scancode::Left;

        // start the snake in the center of the screen horizontally
        const sf::Vector2i cellCount{ t_context.layout.cellCount() };
        const int vertPos{ cellCount.y / 6 };
        const int leftMostPos{ cellCount.x / 3 };
        const int length{ (cellCount.x / 6) + (static_cast<int>(t_context.game.level) * 2) };
        for (int x{ 0 }; x < length; ++x)
        {
            const GridPos_t position{ leftMostPos + static_cast<int>(x), vertPos };
            if (position.x < (cellCount.x - 1))
            {
                m_positions.emplace_back(position);
            }
            else
            {
                break;
            }
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

    void Snake::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (util::keys::isArrow(keyPtr->scancode))
            {
                // check if the new position would end up eating self
                const auto directionBefore{ m_direction };
                m_direction = keyPtr->scancode;
                if (isPositionOnTheSnake(makeMovedPosition(t_context)))
                {
                    t_context.sfx.play("error-1");
                    m_direction = directionBefore;
                }
            }
        }
    }

    void Snake::slower(const Context & t_context)
    {
        m_timeBetweenMovesSec *= t_context.config.snake_speed_slow_mult;
    }

    void Snake::faster(const Context & t_context)
    {
        m_timeBetweenMovesSec *= t_context.config.snake_speed_fast_mult;
    }

    void Snake::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        sf::RectangleShape rectangle;

        for (std::size_t index{ 0 }; index < m_positions.size(); ++index)
        {
            const float colorRatio{ static_cast<float>(index) /
                                    static_cast<float>(m_positions.size()) };

            const sf::Color color{ colors::blend(
                colorRatio,
                t_context.config.cell_snake_first_color,
                t_context.config.cell_snake_last_color) };

            rectangle.setFillColor(color);

            const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
                t_context, m_positions.at(index)) };

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

        const std::size_t surroundingActorCountBefore{ t_context.actors.findNonWallCountSurrounding(
            m_positions.front()) };

        const GridPos_t newPos{ makeMovedPosition(t_context) };

        // check for eating self
        if (isPositionOnTheSnake(newPos))
        {
            t_context.sfx.play("step-smash");
            ++t_context.game.snake_pieces_eaten;
            m_positions.insert(std::begin(m_positions), newPos);
            kill(t_context);
            return;
        }

        m_positions.insert(std::begin(m_positions), newPos);

        // grow tail if needed
        if (0 == m_toGrowCount)
        {
            m_positions.pop_back();
        }
        else
        {
            --m_toGrowCount;
        }

        // keep track of longest tail length
        if (m_positions.size() > t_context.game.longest_tail_length)
        {
            t_context.game.longest_tail_length = m_positions.size();
        }

        // if not eating self, eat other Actors, if any
        if (t_context.actors.eat(t_context, newPos))
        {
            t_context.actors.remove(newPos);
        }
        else
        {
            // if there was a piece within eating range but we didn't, then miss
            if (surroundingActorCountBefore > 0)
            {
                t_context.sfx.play("miss");
                t_context.text_anim.add(t_context, newPos, "miss", sf::Color::White);
                ++t_context.game.miss_count;
            }
        }
    }

    bool Snake::isPositionOnTheSnake(const GridPos_t & t_gridPos) const
    {
        for (const GridPos_t & position : m_positions)
        {
            if (t_gridPos == position)
            {
                return true;
            }
        }

        return false;
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
        --t_context.game.lives;
        ++t_context.game.death_count;
        t_context.top.update(t_context);
        t_context.state.setPending(State::LevelLost);
    }

    void Snake::shrink()
    {
        if (length() <= 1)
        {
            return;
        }

        std::size_t toShrinkCount{ length() / 3_st };
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

    float Snake::calcTimeBetweenMoves(const Context & t_context) const
    {
        float timeBetweenMoves{ t_context.config.snake_time_between_moves_default };

        timeBetweenMoves -=
            (t_context.config.snake_speed_step * static_cast<float>(t_context.game.level));

        if (timeBetweenMoves < t_context.config.snake_time_between_moves_min)
        {
            timeBetweenMoves = t_context.config.snake_time_between_moves_min;
        }

        return timeBetweenMoves;
    }

} // namespace snake2
