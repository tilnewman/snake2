#ifndef STATE_GAME_OVER_HPP_INCLUDED
#define STATE_GAME_OVER_HPP_INCLUDED
//
// state-game-over.hpp
//
#include "state.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <vector>

namespace snake2
{

    struct Context;

    //

    enum class StatAnimPhase
    {
        Label,
        Stat,
        Hold
    };

    //

    struct StatAnimation
    {
        StatAnimation(
            const Context & t_context, const std::string & t_labelStr, const std::size_t t_stat);

        StatAnimPhase phase;
        sf::Text label_text;
        sf::Text stat_text;
        float elapsed_sec;
    };

    //

    class StateGameOver : public StateBase
    {
      public:
        StateGameOver();

        State type() const override { return State::GameOver; }
        void onEnter(const Context & t_context) override;
        void onExit(const Context & t_context) override;
        void update(const Context & t_context, const float t_elapsedSec) override;
        void handleEvent(const Context & t_context, const sf::Event & t_event) override;

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const override;

      private:
        void updateSnakeTextColor(const Context & t_context, const float t_elapsedSec);
        void updateAnimations(const Context & t_context, const float t_elapsedSec);

      private:
        float m_colorElapsedSec;
        sf::Text m_text;
        sf::Color m_color1;
        sf::Color m_color2;
        std::vector<StatAnimation> m_animations;
        std::size_t m_animIndex;
    };

} // namespace snake2

#endif // STATE_GAME_OVER_HPP_INCLUDED
