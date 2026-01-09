//
// grid-display.cpp
//
#include "grid-display.hpp"

#include "config.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"

namespace snake2
{

    GridDisplay::GridDisplay()
        : m_frameRectangle{}
        , m_backgroundRectangle{}
        , m_cellLineVerts{}
    {}

    void GridDisplay::setup(const Context & t_context)
    {
        m_frameRectangle.setFillColor(sf::Color::Transparent);
        m_frameRectangle.setOutlineColor(sf::Color::White);
        m_frameRectangle.setOutlineThickness(1.0f);
        m_frameRectangle.setPosition(t_context.layout.bottomRect().position);
        m_frameRectangle.setSize(t_context.layout.bottomRect().size);

        m_backgroundRectangle.setFillColor(t_context.config.grid_color_background);
        m_backgroundRectangle.setPosition(t_context.layout.gridRect().position);
        m_backgroundRectangle.setSize(t_context.layout.gridRect().size);

        const sf::Vector2f cellSize{ t_context.layout.cellSize() };
        const sf::Vector2u cellCount{ t_context.layout.cellCount() };
        for (unsigned x{ 0 }; x <= cellCount.x; ++x)
        {
            const float horizPos{ m_backgroundRectangle.getPosition().x +
                                  (static_cast<float>(x) * cellSize.x) };

            m_cellLineVerts.emplace_back(
                sf::Vector2f{ horizPos, m_backgroundRectangle.getPosition().y },
                t_context.config.cell_color_outline);

            m_cellLineVerts.emplace_back(
                sf::Vector2f{ horizPos, util::bottom(m_backgroundRectangle.getGlobalBounds()) },
                t_context.config.cell_color_outline);
        }

        for (unsigned y{ 0 }; y <= cellCount.y; ++y)
        {
            const float vertPos{ m_backgroundRectangle.getPosition().y +
                                 (static_cast<float>(y) * cellSize.y) };

            m_cellLineVerts.emplace_back(
                sf::Vector2f{ m_backgroundRectangle.getPosition().x, vertPos },
                t_context.config.cell_color_outline);

            m_cellLineVerts.emplace_back(
                sf::Vector2f{ util::right(m_backgroundRectangle.getGlobalBounds()), vertPos },
                t_context.config.cell_color_outline);
        }
    }

    void GridDisplay::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_frameRectangle, t_states);
        t_target.draw(m_backgroundRectangle, t_states);

        t_target.draw(
            &m_cellLineVerts[0], m_cellLineVerts.size(), sf::PrimitiveType::Lines, t_states);
    }

} // namespace snake2
