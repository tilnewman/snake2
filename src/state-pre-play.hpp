#ifndef STATE_PRE_PLAY_HPP_INLCUDED
#define STATE_PRE_PLAY_HPP_INLCUDED
//
// state-pre-play.hpp
//
#include "state.hpp"
#include "walls.hpp"

namespace snake2
{

    class StatePrePlay : public StateBase
    {
      public:
        StatePrePlay();
        virtual ~StatePrePlay() override = default;

        State type() const override { return State::PrePlay; }
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
        Walls m_walls;
    };

} // namespace snake2

#endif // STATE_PRE_PLAY_HPP_INLCUDED
