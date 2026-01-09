#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED
//
// snake.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>

namespace snake2
{

    struct Context;

    //

    class Snake
    {
      public:
        Snake();

        void setup(const Context & t_context);

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const;

      private:
        std::vector<GridPos_t> m_positions;
    };

} // namespace snake2

#endif // SNAKE_HPP_INCLUDED
