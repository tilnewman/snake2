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

    void Food::onEat(const Context &)
    {
        // TODO  update score, speed up snake walk speed, maybe place another food
    }

    //

    Wall::Wall(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Wall, t_position, t_context.config.cell_wall_color)
    {}

    void Wall::onEat(const Context & t_context) { t_context.snake.kill(t_context); }

} // namespace snake2
