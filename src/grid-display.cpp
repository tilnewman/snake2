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
        , m_blackCellVerts{}
    {}

    void GridDisplay::setup(const Context & t_context)
    {
        m_frameRectangle.setFillColor(t_context.config.grid_frame_color);
        m_frameRectangle.setPosition(t_context.layout.bottomRect().position);
        m_frameRectangle.setSize(t_context.layout.bottomRect().size);

        m_backgroundRectangle.setFillColor(t_context.config.cell_background_color);
        m_backgroundRectangle.setPosition(t_context.layout.gridRect().position);
        m_backgroundRectangle.setSize(t_context.layout.gridRect().size);

        const sf::Vector2u cellCount{ t_context.layout.cellCount() };

        bool isFirstCellBlack{ true };
        for (unsigned y{ 0 }; y < cellCount.y; ++y)
        {
            for (unsigned x{ (isFirstCellBlack) ? 0u : 1u }; x < cellCount.x; x += 2u)
            {
                const sf::FloatRect rect{ gridPosToScreenRect(
                    t_context, { static_cast<int>(x), static_cast<int>(y) }) };

                util::appendTriangleVerts(rect, m_blackCellVerts, sf::Color::Black);
            }

            isFirstCellBlack = !isFirstCellBlack;
        }
    }

    void GridDisplay::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_frameRectangle, t_states);
        t_target.draw(m_backgroundRectangle, t_states);

        t_target.draw(
            &m_blackCellVerts[0], m_blackCellVerts.size(), sf::PrimitiveType::Triangles, t_states);
    }

    const sf::Vector2f GridDisplay::gridPosToScreenPos(
        const Context & t_context, const sf::Vector2i & t_gridPos) const
    {
        return (
            t_context.layout.gridRect().position +
            (sf::Vector2f{ t_gridPos } * t_context.layout.cellSize()));
    }

    const sf::FloatRect GridDisplay::gridPosToScreenRect(
        const Context & t_context, const GridPos_t & t_gridPos) const
    {
        sf::FloatRect rect;
        rect.position = (gridPosToScreenPos(t_context, t_gridPos) + sf::Vector2f{ 1.0f, 1.0f });
        rect.size     = (t_context.layout.cellSize() - sf::Vector2f{ 2.0f, 2.0f });
        return rect;
    }

} // namespace snake2
