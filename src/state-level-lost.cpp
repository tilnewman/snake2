//
// state-level-lost.cpp
//
#include "state-level-lost.hpp"

#include "actors.hpp"
#include "cell-anim.hpp"
#include "context.hpp"
#include "font.hpp"
#include "game-info.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "random.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "snake.hpp"
#include "sound-player.hpp"
#include "text-anim.hpp"

namespace snake2
{

    StateLevelLost::StateLevelLost()
        : m_elapsedSec{ 0.0f }
        , m_text{ util::SfmlDefaults::instance().font() }
    {}

    void StateLevelLost::onEnter(const Context & t_context)
    {
        t_context.sfx.play("death");

        m_text = t_context.font.makeText(FontSize::Huge, "You Died!", sf::Color::Red);
        util::centerInside(m_text, t_context.layout.screenRect());
    }

    void StateLevelLost::onExit(const Context &) {}

    void StateLevelLost::update(const Context & t_context, const float t_elapsedSec)
    {
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > 5.0f)
        {
            if (t_context.game.lives == 0)
            {
                t_context.state.setPending(State::Quit);
            }
            else
            {
                t_context.state.setPending(State::PrePlay);
            }
        }
    }

    void StateLevelLost::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        t_target.draw(t_context.grid_display, t_states);
        t_context.actors.draw(t_context, t_target, t_states);
        t_context.snake.draw(t_context, t_target, t_states);
        t_context.cell_anim.draw(t_target, t_states);
        t_context.text_anim.draw(t_target, t_states);
        t_target.draw(m_text, t_states);
    }

    void StateLevelLost::handleEvent(const Context &, const sf::Event &) {}

} // namespace snake2
