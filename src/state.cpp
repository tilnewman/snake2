//
// state.cpp
//
#include "state.hpp"

#include "state-play.hpp"
#include "state-post-play.hpp"
#include "state-pre-play.hpp"
#include "state-splash.hpp"

#include <stdexcept>

namespace snake2
{

    void StateBase::onEnter(const Context &) {}

    void StateBase::onExit(const Context &) {}

    void StateBase::update(const Context &, const float) {}

    void StateBase::draw(const Context &, sf::RenderTarget &, const sf::RenderStates &) const {}

    void StateBase::handleEvent(const Context &, const sf::Event &) {}

    //

    StateManager::StateManager()
        : m_pendingStateOpt{}
        , m_currentStateUPtr{ make(State::Init) }
    {}

    void StateManager::setPending(const State t_type) { m_pendingStateOpt = t_type; }

    void StateManager::changeIfPending(const Context & t_context)
    {
        if (m_pendingStateOpt.has_value())
        {
            m_currentStateUPtr->onExit(t_context);
            m_currentStateUPtr = make(m_pendingStateOpt.value());
            m_currentStateUPtr->onEnter(t_context);
            m_pendingStateOpt.reset();
        }
    }

    IStateUPtr_t StateManager::make(const State t_type) const
    {
        // clang-format off
        switch (t_type)
        {
            case State::Init:     { return std::make_unique<StateInit>();     }
            case State::Play:     { return std::make_unique<StatePlay>();     }
            case State::Quit:     { return std::make_unique<StateQuit>();     }
            case State::Splash:   { return std::make_unique<StateSplash>();   }
            case State::PrePlay:  { return std::make_unique<StatePrePlay>();  }
            case State::PostPlay: { return std::make_unique<StatePostPlay>(); }
            default:
            {
                throw std::runtime_error("Error: StateFactory::make() given an unknown type!");
            }
        }
        // clang-format on
    }

} // namespace snake2
