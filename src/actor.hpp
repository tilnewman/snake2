#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED
//
// actor.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace snake2
{

    struct Context;

    //

    enum class Actor
    {
        Food,
        Wall,
        Shrink,
        Slow,
        Rainbow
    };

    //

    struct IActor
    {
        virtual ~IActor() = default;

        virtual Actor type() const                                               = 0;
        virtual const GridPos_t position() const                                 = 0;
        virtual const sf::Color color() const                                    = 0;
        virtual void update(const Context & t_context, const float t_elapsedSec) = 0;

        // returns true if the eaten actor needs to be removed by the caller
        virtual bool onEat(const Context & t_context) = 0;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const = 0;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) = 0;
    };

    //

    class ActorBase : public IActor
    {
      public:
        ActorBase(
            const Context & t_context,
            const Actor t_type,
            const GridPos_t & t_position,
            const sf::Color & t_color);

        virtual ~ActorBase() override = default;

        Actor type() const final { return m_type; }
        const GridPos_t position() const final { return m_position; }
        const sf::Color color() const final { return m_rectangle.getFillColor(); }
        void color(const sf::Color & t_color) { m_rectangle.setFillColor(t_color); }

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const override;

        void handleEvent(const Context & t_context, const sf::Event & t_event) override;

        void update(const Context & t_context, const float t_elapsedSec) override;

      private:
        Actor m_type;
        GridPos_t m_position;
        sf::RectangleShape m_rectangle;
    };

    //

    class Food : public ActorBase
    {
      public:
        Food(const Context & t_context, const GridPos_t & t_position);
        virtual ~Food() override = default;
        bool onEat(const Context & t_context) override;
    };

    //

    class Wall : public ActorBase
    {
      public:
        Wall(const Context & t_context, const GridPos_t & t_position);
        virtual ~Wall() override = default;
        bool onEat(const Context & t_context) override;
    };

    //

    class Shrink : public ActorBase
    {
      public:
        Shrink(const Context & t_context, const GridPos_t & t_position);
        virtual ~Shrink() override = default;
        bool onEat(const Context & t_context) override;
    };

    //

    class Slow : public ActorBase
    {
      public:
        Slow(const Context & t_context, const GridPos_t & t_position);
        virtual ~Slow() override = default;
        bool onEat(const Context & t_context) override;
    };

    //

    class Rainbow : public ActorBase
    {
      public:
        Rainbow(const Context & t_context, const GridPos_t & t_position);
        virtual ~Rainbow() override = default;
        bool onEat(const Context & t_context) override;
        void update(const Context & t_context, const float t_elapsedSec) override;

      private:
        sf::Color m_color1;
        sf::Color m_color2;
        float m_elapsedSec;
    };

} // namespace snake2

#endif // ACTOR_HPP_INCLUDED
