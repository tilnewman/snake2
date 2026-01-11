#ifndef STATE_SPLASH_HPP_INCLUDED
#define STATE_SPLASH_HPP_INCLUDED
//
// state-splash.hpp
//
#include "state.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace snake2
{

    class StateSplash : public StateBase
    {
      public:
        StateSplash();

        State type() const override { return State::Splash; }
        void onEnter(const Context & t_context) override;
        void onExit(const Context & t_context) override;
        void update(const Context & t_context, const float t_elapsedTimeSec) override;
        void handleEvent(const Context & t_context, const sf::Event & t_event) override;

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const override;

      private:
        sf::Text m_text;
        float m_elapsedSec;
    };

} // namespace snake2

#endif // STATE_SPLASH_HPP_INCLUDED
