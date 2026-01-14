// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-pre-play.cpp
//
#include "state-pre-play.hpp"

#include "actors.hpp"
#include "cell-anim.hpp"
#include "config.hpp"
#include "context.hpp"
#include "game-info.hpp"
#include "grid-display.hpp"
#include "level.hpp"
#include "random.hpp"
#include "snake.hpp"
#include "sound-player.hpp"
#include "text-anim.hpp"
#include "top-panel.hpp"

namespace snake2
{

    StatePrePlay::StatePrePlay()
        : m_elapsedSec{ 0.0f }
        , m_walls{}
    {}

    void StatePrePlay::onEnter(const Context & t_context)
    {
        t_context.cell_anim.clear();
        t_context.text_anim.clear();
        t_context.snake.reset(t_context);
        t_context.actors.clear();

        t_context.level.setup(t_context);

        for (int counter{ 0 }; counter < static_cast<int>(t_context.level.food_to_spawn_on_start);
             ++counter)
        {
            const GridPosVec_t freePositions{ t_context.actors.findFreePositions(t_context) };
            t_context.actors.add(t_context, Actor::Food, t_context.random.from(freePositions));
        }

        t_context.sfx.play("level-intro");
    }

    void StatePrePlay::onExit(const Context &) {}

    void StatePrePlay::update(const Context & t_context, const float t_elapsedSec)
    {
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > 3.0f)
        {
            t_context.state.setPending(State::Play);
        }
    }

    void StatePrePlay::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        t_target.draw(t_context.grid_display, t_states);
        t_context.actors.draw(t_context, t_target, t_states);
        t_context.snake.draw(t_context, t_target, t_states);
        t_context.top.draw(t_target, t_states);
    }

    void StatePrePlay::handleEvent(const Context &, const sf::Event &) {}

} // namespace snake2
