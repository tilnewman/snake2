//
// state-play.cpp
//
#include "state-play.hpp"

#include "actors.hpp"
#include "cell-anim.hpp"
#include "context.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "random.hpp"
#include "snake.hpp"

namespace snake2
{

    StatePlay::StatePlay() {}

    void StatePlay::onEnter(const Context & t_context)
    {
        m_framerateDisplay.setup(t_context);

        // TODO remove after testing
        for (int x{ 0 }; x < static_cast<int>(t_context.layout.cellCount().x); ++x)
        {
            t_context.actors.add(t_context, Actor::Wall, { x, 0 });

            t_context.actors.add(
                t_context,
                Actor::Wall,
                { x, static_cast<int>(t_context.layout.cellCount().y - 1u) });
        }
        for (int counter{ 0 }; counter < 6; ++counter)
        {
            const GridPosVec_t freePositions{ t_context.actors.findFreePositions(t_context) };
            t_context.actors.add(t_context, Actor::Food, t_context.random.from(freePositions));
        }
        for (int counter{ 0 }; counter < 6; ++counter)
        {
            const GridPosVec_t freePositions{ t_context.actors.findFreePositions(t_context) };
            t_context.actors.add(t_context, Actor::Shrink, t_context.random.from(freePositions));
        }
        for (int counter{ 0 }; counter < 6; ++counter)
        {
            const GridPosVec_t freePositions{ t_context.actors.findFreePositions(t_context) };
            t_context.actors.add(t_context, Actor::Slow, t_context.random.from(freePositions));
        }
    }

    void StatePlay::onExit(const Context &) {}

    void StatePlay::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        t_context.actors.update(t_context, t_elapsedTimeSec);
        t_context.snake.update(t_context, t_elapsedTimeSec);
        t_context.cell_anim.update(t_context, t_elapsedTimeSec);
        m_framerateDisplay.update(t_context, t_elapsedTimeSec); 
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
