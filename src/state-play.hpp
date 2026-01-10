#ifndef STATE_PLAY_HPP_INLCUDED
#define STATE_PLAY_HPP_INLCUDED
//
// state-play.hpp
//
#include "framerate-display.hpp"
#include "state.hpp"

namespace snake2
{

    class StatePlay : public StateBase
    {
      public:
        StatePlay();
        virtual ~StatePlay() override = default;

        State type() const override { return State::Play; }
        void onEnter(const Context & t_context) override;
        void onExit(const Context & t_context) override;
        void update(const Context & t_context, const float t_elapsedTimeSec) override;
        void handleEvent(const Context & t_context, const sf::Event & t_event) override;

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const override;

      private:
        FramerateDisplay m_framerateDisplay;
    };

} // namespace snake2

#endif // STATE_PLAY_HPP_INLCUDED
