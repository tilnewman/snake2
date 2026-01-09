#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED
//
// actor.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/Color.hpp>
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
        Wall
        // SlowTime,
        // TrimLength
    };

    //

    struct IActor
    {
        virtual ~IActor() = default;

        virtual Actor type() const                                                   = 0;
        virtual const GridPos_t position() const                                     = 0;
        virtual const sf::Color color() const                                        = 0;
        virtual void onEat(const Context & t_context)                                = 0;
        virtual void update(const Context & t_context, const float t_elpasedTimeSec) = 0;

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
        ActorBase(const Actor t_type, const GridPos_t & t_position, const sf::Color & t_color)
            : m_type{ t_type }
            , m_position{ t_position }
            , m_color{ t_color }
        {}

        virtual ~ActorBase() = default;

        Actor type() const final { return m_type; }
        const GridPos_t position() const final { return m_position; }
        const sf::Color color() const final { return m_color; }

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const override;

        void handleEvent(const Context & t_context, const sf::Event & t_event) override;

        void update(const Context & t_context, const float t_elpasedTimeSec) override;

      private:
        Actor m_type;
        GridPos_t m_position;
        sf::Color m_color;
    };

    //

    class Food : public ActorBase
    {
      public:
        Food(const Context & t_context, const GridPos_t & t_position);
        virtual ~Food() = default;
        void onEat(const Context & t_context) override;
    };

    //

    class Wall : public ActorBase
    {
      public:
        Wall(const Context & t_context, const GridPos_t & t_position);
        virtual ~Wall() = default;
        void onEat(const Context & t_context) override;
    };

} // namespace snake2

#endif // ACTOR_HPP_INCLUDED
