//
// snake.cpp
//
#include "snake.hpp"

#include "context.hpp"
#include "grid-display.hpp"
#include "keys.hpp"
#include "layout.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace snake2
{

    Snake::Snake()
        : m_positions{}
        , m_direction{ sf::Keyboard::Scancode::Left }
        , m_elapsedTimeSec{ 0.0f }
        , m_timeBetweenMovesSec{ 0.5f }
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

    void Snake::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        sf::RectangleShape rectangle;
        rectangle.setFillColor(t_context.config.cell_snake_first_color);
        rectangle.setSize(t_context.layout.cellSize() - sf::Vector2f{ 2.0f, 2.0f });

        for (const GridPos_t & position : m_positions)
        {
            const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
                t_context, position) };

            rectangle.setPosition(screenRect.position);
            rectangle.setSize(screenRect.size);

            t_target.draw(rectangle, t_states);
        }
    }

    void Snake::move(const Context &)
    {
        if (m_positions.empty())
        {
            return;
        }

        const GridPos_t newPos = [&]() {
            const GridPos_t oldPos{ m_positions.front() };

            if (sf::Keyboard::Scancode::Left == m_direction)
            {
                return GridPos_t{ oldPos.x - 1, oldPos.y };
            }
            else if (sf::Keyboard::Scancode::Right == m_direction)
            {
                return GridPos_t{ oldPos.x + 1, oldPos.y };
            }
            else if (sf::Keyboard::Scancode::Up == m_direction)
            {
                return GridPos_t{ oldPos.x, oldPos.y - 1 };
            }
            else
            {
                return GridPos_t{ oldPos.x, oldPos.y + 1 };
            }
        }();

        m_positions.insert(std::begin(m_positions), newPos);
        m_positions.pop_back();
    }

} // namespace snake2
