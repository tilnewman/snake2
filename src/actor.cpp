//
// actor.hpp
//
#include "actor.hpp"

#include "config.hpp"
#include "context.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "snake.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace snake2
{

    void ActorBase::draw(
        const Context & t_context,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
            t_context, m_position) };

        sf::RectangleShape rectangle;
        rectangle.setFillColor(m_color);
        rectangle.setPosition(screenRect.position);
        rectangle.setSize(screenRect.size);

        t_target.draw(rectangle, t_states);
    }

    void ActorBase::handleEvent(const Context &, const sf::Event &)
    {
        // the default behavior is to never respond to events
    }

    void ActorBase::update(const Context &, const float)
    {
        // the default behavior is to never need updating based on time
    }

    //

    Food::Food(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Food, t_position, t_context.config.cell_food_color)
    {}

    bool Food::onEat(const Context & t_context)
    {
        // TODO update score, start animation, maybe place another food
        t_context.snake.grow(t_context.layout.cellCount().y / 2u);
        return true;
    }

    //

    Wall::Wall(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Wall, t_position, t_context.config.cell_wall_color)
    {}

    bool Wall::onEat(const Context & t_context)
    {
        t_context.snake.kill(t_context);
        return false;
    }

    //

    Shrink::Shrink(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Shrink, t_position, t_context.config.cell_shrink_color)
    {}

    bool Shrink::onEat(const Context & t_context)
    {
        t_context.snake.shrink();
        return true;
    }

    //

    Slow::Slow(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Slow, t_position, t_context.config.cell_slow_color)
    {}

    bool Slow::onEat(const Context & t_context)
    {
        t_context.snake.slower(t_context);
        return true;
    }

    //

    Fast::Fast(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Fast, t_position, t_context.config.cell_fast_color)
    {}

    bool Fast::onEat(const Context & t_context)
    {
        t_context.snake.faster(t_context);
        return true;
    }

} // namespace snake2
