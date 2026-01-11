//
// state-level-won.cpp
//
#include "state-level-won.hpp"

#include "actors.hpp"
#include "cell-anim.hpp"
#include "context.hpp"
#include "game-info.hpp"
#include "grid-display.hpp"
#include "random.hpp"
#include "snake.hpp"
#include "sound-player.hpp"
#include "text-anim.hpp"

namespace snake2
{

    StateLevelWon::StateLevelWon()
        : m_elapsedSec{ 0.0f }
    {}

    void StateLevelWon::onEnter(const Context &) {}

    void StateLevelWon::onExit(const Context &) {}

    void StateLevelWon::update(const Context & t_context, const float t_elapsedSec)
    {
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > 3.0f)
        {
            t_context.state.setPending(State::PrePlay);
        }

        t_context.cell_anim.update(t_context, t_elapsedSec);
        t_context.text_anim.update(t_context, t_elapsedSec);
    }

    void StateLevelWon::draw(
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

    void StateLevelWon::handleEvent(const Context &, const sf::Event &) {}

} // namespace snake2
