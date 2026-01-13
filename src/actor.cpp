//
// actor.hpp
//
#include "actor.hpp"

#include "actors.hpp"
#include "cell-anim.hpp"
#include "color-range.hpp"
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
#include "top-panel.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace snake2
{

    ActorBase::ActorBase(
        const Context & t_context,
        const Actor t_type,
        const GridPos_t & t_position,
        const sf::Color & t_color)
        : m_type{ t_type }
        , m_position{ t_position }
        , m_rectangle{}
    {
        const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
            t_context, m_position) };

        m_rectangle.setPosition(screenRect.position);
        m_rectangle.setSize(screenRect.size);
        m_rectangle.setFillColor(t_color);
    }

    void ActorBase::draw(
        const Context &,
        sf::RenderTarget & t_target,
        const sf::RenderStates & t_states) const
    {
        t_target.draw(m_rectangle, t_states);
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
        : ActorBase(t_context, Actor::Food, t_position, t_context.config.cell_food_color)
    {}

    bool Food::onEat(const Context & t_context)
    {
        // this tracks how many food pieces have been eaten during the whole game
        ++t_context.game.food_pieces_eaten;

        // this tracks how many food pieces have been eaten during just this level
        ++t_context.level.food_eaten;

        // make the snake longer
        t_context.snake.grow(
            (t_context.game.level * 2u) + (t_context.layout.cellCount().y / 2u) +
            (2u * static_cast<unsigned>(std::sqrt(t_context.snake.length()))));

        // calculate the score for eating this food
        const std::size_t score{ t_context.game.food_pieces_eaten + t_context.level.food_eaten +
                                 t_context.game.level };

        // find out if this increase in score means a bonus life will be awarded
        static std::size_t scoreDiv{ 500_st };
        const std::size_t scoreDivBefore{ t_context.game.score / scoreDiv };
        const std::size_t scoreDivAfter{ (t_context.game.score + score) / scoreDiv };
        if (scoreDivBefore < scoreDivAfter)
        {
            t_context.sfx.play("bonus-life");
            ++t_context.game.lives;
            scoreDiv *= 2;
        }
        else
        {
            const float pitch{ util::map(
                t_context.level.food_eaten,
                1_st,
                t_context.config.food_pieces_per_level,
                0.33f,
                1.0f) };

            t_context.sfx.play("shine", pitch);
        }

        // actually increase the score
        t_context.game.score += score;

        // spawn animations
        std::string scoreStr{ "+" };
        scoreStr += std::to_string(score);
        t_context.text_anim.add(t_context, position(), scoreStr, color());
        t_context.cell_anim.add(t_context, position(), color());

        // speed up snake
        t_context.snake.faster(t_context);

        // update top panel numbers
        t_context.top.update(t_context);

        // respawn if needed
        if (t_context.level.food_eaten >= t_context.level.food_to_spawn_on_start)
        {
            if (t_context.level.food_to_spawn_after_start > 0)
            {
                --t_context.level.food_to_spawn_after_start;

                t_context.actors.add(
                    t_context,
                    Actor::Food,
                    t_context.random.from(t_context.actors.findFreePositions(t_context)));
            }
        }

        // win the level if all the food is eaten
        if (t_context.config.food_pieces_per_level == t_context.level.food_eaten)
        {
            t_context.state.setPending(State::LevelWon);
        }

        return true;
    }

    //

    Wall::Wall(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(t_context, Actor::Wall, t_position, t_context.config.cell_wall_color)
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
        : ActorBase(t_context, Actor::Shrink, t_position, t_context.config.cell_shrink_color)
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
        : ActorBase(t_context, Actor::Slow, t_position, t_context.config.cell_slow_color)
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

    //

    Rainbow::Rainbow(const Context & t_context, const GridPos_t & t_position)
        : ActorBase(t_context, Actor::Rainbow, t_position, t_context.config.cell_slow_color)
        , m_color1{ colors::randomVibrant(t_context.random) }
        , m_color2{ colors::randomVibrant(t_context.random) }
        , m_elapsedSec{ 0.0f }
    {}

    bool Rainbow::onEat(const Context & t_context)
    {
        t_context.sfx.play("bonus-life");

        t_context.snake.slower(t_context);
        t_context.snake.shrink();
        ++t_context.game.lives;

        t_context.cell_anim.add(t_context, position(), color());
        t_context.text_anim.add(t_context, position(), "Rainbow!", color());

        ++t_context.game.rainbow_pieces_eaten;

        t_context.top.update(t_context);
        return true;
    }

    void Rainbow::update(const Context & t_context, const float t_elapsedSec)
    {
        const float timeBetweenColorsSec{ 0.2f };
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > timeBetweenColorsSec)
        {
            m_elapsedSec = 0.0f;
            m_color1     = m_color2;
            m_color2     = colors::randomVibrant(t_context.random);
        }

        const float ratio{ util::map(m_elapsedSec, 0.0f, timeBetweenColorsSec, 0.0f, 1.0f) };
        const sf::Color color{ colors::blend(ratio, m_color1, m_color2) };
        ActorBase::color(color);
    }

} // namespace snake2
