//
// actor.hpp
//
#include "actor.hpp"

#include "cell-anim.hpp"
#include "config.hpp"
#include "context.hpp"
#include "game-info.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "level.hpp"
#include "sfml-util.hpp"
#include "snake.hpp"
#include "sound-player.hpp"
#include "state.hpp"
#include "text-anim.hpp"

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
        // TODO update score, maybe place another food

        // this tracks how many food pieces have been eaten during the whole game
        ++t_context.game.food_pieces_eaten;

        // this tracks how many food pieces have been eaten during just this level
        ++t_context.level.food_eaten;

        const float pitch{ util::map(
            t_context.level.food_eaten,
            1_st,
            t_context.config.food_pieces_per_level,
            0.33f,
            1.0f) };

        t_context.sfx.play("shine", pitch);

        t_context.snake.grow(
            (t_context.layout.cellCount().y / 2u) +
            (2u * static_cast<unsigned>(std::sqrt(t_context.snake.length()))));

        t_context.cell_anim.add(t_context, position(), color());
        t_context.text_anim.add(t_context, position(), "Test!", color());

        if (t_context.config.food_pieces_per_level == t_context.level.food_eaten)
        {
            t_context.state.setPending(State::LevelWon);
        }

        return true;
    }

    //

    Wall::Wall(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Wall, t_position, t_context.config.cell_wall_color)
    {}

    bool Wall::onEat(const Context & t_context)
    {
        t_context.sfx.play("break-block");
        t_context.snake.kill(t_context);
        ++t_context.game.brick_pieces_eaten;
        return false;
    }

    //

    Shrink::Shrink(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Shrink, t_position, t_context.config.cell_shrink_color)
    {}

    bool Shrink::onEat(const Context & t_context)
    {
        t_context.sfx.play("chop");
        t_context.snake.shrink();
        t_context.cell_anim.add(t_context, position(), color());
        t_context.text_anim.add(t_context, position(), "Shrink!", color());
        ++t_context.game.shrink_pieces_eaten;
        return true;
    }

    //

    Slow::Slow(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(Actor::Slow, t_position, t_context.config.cell_slow_color)
    {}

    bool Slow::onEat(const Context & t_context)
    {
        t_context.sfx.play("slow");
        t_context.snake.slower(t_context);
        t_context.cell_anim.add(t_context, position(), color());
        t_context.text_anim.add(t_context, position(), "Slow!", color());
        ++t_context.game.slow_pieces_eaten;
        return true;
    }

} // namespace snake2
