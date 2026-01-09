#ifndef GRID_DISPLAY_HPP_INLCUDED
#define GRID_DISPLAY_HPP_INLCUDED
//
// grid-display.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <vector>

namespace snake2
{

    struct Context;

    class GridDisplay : public sf::Drawable
    {
      public:
        GridDisplay();

        void setup(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

        [[nodiscard]] const sf::Vector2f
            gridPosToScreenPos(const Context & t_context, const GridPos_t & t_gridPos) const;

      private:
        sf::RectangleShape m_frameRectangle;
        sf::RectangleShape m_backgroundRectangle;
        std::vector<sf::Vertex> m_cellLineVerts;
    };

} // namespace snake2

#endif // GRID_DISPLAY_HPP_INLCUDED
