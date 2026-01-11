//
// state-splash.cpp
//
#include "state-splash.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

namespace snake2
{
    StateSplash::StateSplash()
        : m_text{ util::SfmlDefaults::instance().font() }
        , m_elapsedSec{ 0.0f }
    {}

    void StateSplash::onEnter(const Context & t_context)
    {
        m_text = t_context.font.makeText(FontSize::Huge, "Snake!", sf::Color::Cyan);
        util::centerInside(m_text, t_context.layout.screenRect());
    }

    void StateSplash::onExit(const Context &) {}

    void StateSplash::update(const Context & t_context, const float t_elapsedTimeSec) 
    {
        m_elapsedSec += t_elapsedTimeSec;
        if (m_elapsedSec > 4.0f)
        {
            t_context.state.setPending(State::Play);
        }
    }

    void StateSplash::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr{ t_event.getIf<sf::Event::KeyPressed>() };
        const auto * mousePtr{ t_event.getIf<sf::Event::MouseButtonPressed>() };
        if (keyPtr || mousePtr)
        {
            t_context.state.setPending(State::Play);
            return;
        }
    }

    void StateSplash::draw(
        const Context &, sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        t_target.draw(m_text, t_states);
    }

} // namespace snake2
