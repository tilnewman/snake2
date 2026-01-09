#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED
//
// snake.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

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
        void update(const Context & t_context, const float t_elapsedTimeSec);
        void handleEvent(const Context & t_context, const sf::Event & t_event);
        [[nodiscard]] const GridPosVec_t positions() const noexcept { return m_positions; }
        [[nodiscard]] std::size_t length() const noexcept { return m_positions.size(); } 
        void kill(const Context & t_context);
        void grow(const std::size_t count) noexcept { m_toGrowCount += count; }

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const;

      private:
        void move(const Context & t_context);
        const GridPos_t makeMovedPosition(const Context & t_context) const;

      private:
        GridPosVec_t m_positions;
        sf::Keyboard::Scancode m_direction;
        float m_elapsedTimeSec;
        float m_timeBetweenMovesSec;
        bool m_isAlive;
        std::size_t m_toGrowCount;
    };

} // namespace snake2

#endif // SNAKE_HPP_INCLUDED
