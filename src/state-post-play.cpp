//
// state-post-play.cpp
//
#include "state-post-play.hpp"

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

    StatePostPlay::StatePostPlay()
        : m_elapsedSec{ 0.0f }
    {}

    void StatePostPlay::onEnter(const Context & t_context) { t_context.sfx.play("death"); }

    void StatePostPlay::onExit(const Context &) {}

    void StatePostPlay::update(const Context & t_context, const float t_elapsedSec)
    {
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > 5.0f)
        {
            // TODO if lives are spent then transition to State::GameOver
            t_context.state.setPending(State::PrePlay);
        }
    }

    void StatePostPlay::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        t_target.draw(t_context.grid_display, t_states);
        t_context.actors.draw(t_context, t_target, t_states);
        t_context.snake.draw(t_context, t_target, t_states);
        t_context.cell_anim.draw(t_target, t_states);
        t_context.text_anim.draw(t_target, t_states);
    }

    void StatePostPlay::handleEvent(const Context &, const sf::Event &) {}

} // namespace snake2
