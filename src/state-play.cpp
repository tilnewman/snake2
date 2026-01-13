//
// state-play.cpp
//
#include "state-play.hpp"

#include "actors.hpp"
#include "cell-anim.hpp"
#include "context.hpp"
#include "font.hpp"
#include "game-info.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "level.hpp"
#include "random.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "snake.hpp"
#include "sound-player.hpp"
#include "text-anim.hpp"
#include "top-panel.hpp"

namespace snake2
{

    StatePlay::StatePlay()
        : m_framerateDisplay{}
        , m_spawnElapsedSec{ 0.0f }
        , m_spawnSec{ 0.0f }
        , m_isPaused{ false }
        , m_pauseText{ util::SfmlDefaults::instance().font() }
    {}

    void StatePlay::onEnter(const Context & t_context)
    {
        m_framerateDisplay.setup(t_context);
        m_spawnSec  = randomTimeUntilSpawn(t_context);
        m_pauseText = t_context.font.makeText(FontSize::Huge, "PAUSED", sf::Color::White);
        util::centerInside(m_pauseText, t_context.layout.screenRect());
    }

    void StatePlay::onExit(const Context &) {}

    void StatePlay::update(const Context & t_context, const float t_elapsedSec)
    {
        m_framerateDisplay.update(t_context, t_elapsedSec);

        updateSpawn(t_context, t_elapsedSec);

        if (!m_isPaused)
        {
            t_context.snake.update(t_context, t_elapsedSec);
            t_context.actors.update(t_context, t_elapsedSec);
            t_context.cell_anim.update(t_context, t_elapsedSec);
            t_context.text_anim.update(t_context, t_elapsedSec);
        }
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
        t_context.top.draw(t_target, t_states);
        // m_framerateDisplay.draw(t_target, t_states);

        if (m_isPaused)
        {
            t_target.draw(m_pauseText, t_states);
        }
    }

    void StatePlay::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.setPending(State::GameOver);
                return;
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::Space)
            {
                m_isPaused = !m_isPaused;
                t_context.sfx.play("pause");
            }
        }

        if (!m_isPaused)
        {
            t_context.actors.handleEvent(t_context, t_event);
            t_context.snake.handleEvent(t_context, t_event);
        }
    }

    void StatePlay::updateSpawn(const Context & t_context, const float t_elapsedSec)
    {
        if (m_isPaused)
        {
            return;
        }

        m_spawnElapsedSec += t_elapsedSec;
        if (m_spawnElapsedSec > m_spawnSec)
        {
            m_spawnElapsedSec = 0.0f;
            m_spawnSec        = randomTimeUntilSpawn(t_context);

            if (t_context.random.boolean())
            {
                t_context.actors.add(
                    t_context,
                    Actor::Slow,
                    t_context.random.from(t_context.actors.findFreePositions(t_context)));
            }
            else
            {
                t_context.actors.add(
                    t_context,
                    Actor::Shrink,
                    t_context.random.from(t_context.actors.findFreePositions(t_context)));
            }
        }
    }

    float StatePlay::randomTimeUntilSpawn(const Context & t_context) const
    {
        const float levelNumber{ static_cast<float>(t_context.game.level) };
        return t_context.random.fromTo((5.0f + levelNumber), (10.0f + levelNumber));
    }

} // namespace snake2
