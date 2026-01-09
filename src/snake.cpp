//
// snake.cpp
//
#include "snake.hpp"

#include "context.hpp"
#include "grid-display.hpp"
#include "layout.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace snake2
{

    Snake::Snake()
        : m_positions{}
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

} // namespace snake2
