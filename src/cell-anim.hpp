#ifndef CELL_ANIM_HPP_INCLUDED
#define CELL_ANIM_HPP_INCLUDED
//
// cell-anim.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace snake2
{

    struct Context;

    //

    struct CellAnimation
    {
        float elapsed_sec{ 0.0f };
        bool is_finished{ false };
        sf::Color color{ sf::Color::Transparent };
        sf::RectangleShape rectangle{};
    };

    //

    class CellAnimationManager
    {
      public:
        CellAnimationManager();

        void setup(const Context & t_context);
        void add(const Context & t_context, const GridPos_t & t_gridPos, const sf::Color & t_color);
        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const;
        void clear() { m_animations.clear(); }

      private:
        std::vector<CellAnimation> m_animations;
    };

} // namespace snake2

#endif // CELL_ANIM_HPP_INCLUDED
