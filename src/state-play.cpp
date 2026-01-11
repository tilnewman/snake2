//
// state-play.cpp
//
#include "state-play.hpp"

#include "actors.hpp"
#include "cell-anim.hpp"
#include "context.hpp"
#include "grid-display.hpp"
#include "random.hpp"
#include "snake.hpp"
#include "sound-player.hpp"
#include "text-anim.hpp"

namespace snake2
{

    StatePlay::StatePlay()
        : m_walls{}
        , m_wasSnakeAlive{ true }
        , m_framerateDisplay{}
    {}

    void StatePlay::onEnter(const Context & t_context) { m_framerateDisplay.setup(t_context); }

    void StatePlay::onExit(const Context &) {}

    void StatePlay::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.actors.update(t_context, t_elapsedSec);
        t_context.snake.update(t_context, t_elapsedSec);
        t_context.cell_anim.update(t_context, t_elapsedSec);
        t_context.text_anim.update(t_context, t_elapsedSec);
        m_framerateDisplay.update(t_context, t_elapsedSec);
    }

    void StatePlay::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        t_target.draw(t_context.grid_display, t_states);
        t_context.actors.draw(t_context, t_target, t_states);
        t_context.snake.draw(t_context, t_target, t_states);
        t_context.cell_anim.draw(t_target, t_states);
        t_context.text_anim.draw(t_target, t_states);
        m_framerateDisplay.draw(t_target, t_states);
    }

    void StatePlay::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.setPending(State::Quit);
                return;
            }
        }

        t_context.actors.handleEvent(t_context, t_event);
        t_context.snake.handleEvent(t_context, t_event);
    }

} // namespace snake2
