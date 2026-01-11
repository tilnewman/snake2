#ifndef STATE_LEVEL_WON_HPP_INLCUDED
#define STATE_LEVEL_WON_HPP_INLCUDED
//
// state-level-won.hpp
//
#include "state.hpp"

namespace snake2
{

    class StateLevelWon : public StateBase
    {
      public:
        StateLevelWon();
        virtual ~StateLevelWon() override = default;

        State type() const override { return State::LevelWon; }
        void onEnter(const Context & t_context) override;
        void onExit(const Context & t_context) override;
        void update(const Context & t_context, const float t_elapsedTimeSec) override;
        void handleEvent(const Context & t_context, const sf::Event & t_event) override;

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const override;

      private:
        float m_elapsedSec;
    };

} // namespace snake2

#endif // STATE_LEVEL_WON_HPP_INLCUDED
