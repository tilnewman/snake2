#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED
//
// state.hpp
//
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <optional>

namespace snake2
{

    struct Context;

    //

    enum class State
    {
        Init,
        Play,
        Quit
    };

    //

    struct IState
    {
        virtual ~IState() = default;

        virtual State type() const                                                     = 0;
        virtual void onEnter(const Context & t_context)                                = 0;
        virtual void onExit(const Context & t_context)                                 = 0;
        virtual void update(const Context & t_context, const float t_elapsedTimeSec)   = 0;
        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) = 0;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const = 0;
    };

    using IStateUPtr_t = std::unique_ptr<IState>;

    //

    class StateBase : public IState
    {
      public:
        StateBase()                   = default;
        virtual ~StateBase() override = default;

        // by default these functions do nothing in the base class
        void onEnter(const Context & t_context) override;
        void onExit(const Context & t_context) override;
        void update(const Context & t_context, const float t_elapsedTimeSec) override;
        void handleEvent(const Context & t_context, const sf::Event & t_event) override;

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            const sf::RenderStates & t_states) const override;
    };

    //

    class StateInit : public StateBase
    {
      public:
        StateInit()                   = default;
        virtual ~StateInit() override = default;
        State type() const override { return State::Init; }
    };

    //

    class StateQuit : public StateBase
    {
      public:
        StateQuit()                   = default;
        virtual ~StateQuit() override = default;
        State type() const override { return State::Quit; }
    };

    //

    class StateManager
    {
      public:
        StateManager();

        void setPending(const State t_type);
        void changeIfPending(const Context & t_context);
        IState & current() { return *m_currentStateUPtr; }

      private:
        IStateUPtr_t make(const State t_type) const;

      private:
        std::optional<State> m_pendingStateOpt;
        IStateUPtr_t m_currentStateUPtr;
    };

} // namespace snake2

#endif // STATE_HPP_INCLUDED
