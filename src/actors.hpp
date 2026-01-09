#ifndef ACTORS_HPP_INCLUDED
#define ACTORS_HPP_INCLUDED
//
// actors.hpp
//
#include "actor.hpp"
#include "grid-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <vector>

namespace snake2
{

    struct Context;

    //

    class Actors
    {
      public:
        Actors();

        void setup(const Context & t_context);
        void add(const Context & t_context, const Actor t_type, const GridPos_t & t_gridPos);
        void remove(const GridPos_t & t_gridPos);
        void handleEvent(const Context & t_context, const sf::Event & t_event);
        void update(const Context & t_context, const float t_elpasedTimeSec);
        [[nodiscard]] bool eat(const Context & t_context, const GridPos_t & t_gridPos);

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const;

        [[nodiscard]] const GridPosVec_t findFreePositions(const Context & t_context) const;

      private:
        [[nodiscard]] std::unique_ptr<IActor>
            makeActor(const Context & t_context, const Actor t_type, const GridPos_t & t_gridPos);

      private:
        std::vector<std::unique_ptr<IActor>> m_actors;
    };

} // namespace snake2

#endif // ACTORS_HPP_INCLUDED
