// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state.cpp
//
#include "state.hpp"

#include "state-game-over.hpp"
#include "state-level-lost.hpp"
#include "state-level-won.hpp"
#include "state-play.hpp"
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
            m_pendingStateOpt.reset();
            m_currentStateUPtr->onEnter(t_context);
        }
    }

    IStateUPtr_t StateManager::make(const State t_type) const
    {
        // clang-format off
        switch (t_type)
        {
            case State::Init:      { return std::make_unique<StateInit>();      }
            case State::Play:      { return std::make_unique<StatePlay>();      }
            case State::Quit:      { return std::make_unique<StateQuit>();      }
            case State::Splash:    { return std::make_unique<StateSplash>();    }
            case State::PrePlay:   { return std::make_unique<StatePrePlay>();   }
            case State::LevelWon:  { return std::make_unique<StateLevelWon>();  }
            case State::LevelLost: { return std::make_unique<StateLevelLost>(); }
            case State::GameOver:  { return std::make_unique<StateGameOver>();  }
            default:
            {
                throw std::runtime_error("Error: StateFactory::make() given an unknown type!");
            }
        }
        // clang-format on
    }

} // namespace snake2
