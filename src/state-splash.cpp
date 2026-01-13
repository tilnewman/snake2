//
// state-splash.cpp
//
#include "state-splash.hpp"

#include "color-range.hpp"
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
        , m_colorElapsedSec{ 0.0f }
        , m_color1{}
        , m_color2{}
    {}

    void StateSplash::onEnter(const Context & t_context)
    {
        m_color1 = sf::Color::Cyan;
        m_color2 = colors::randomVibrant(t_context.random);

        m_text = t_context.font.makeText(FontSize::Colossal, "Snake!", m_color1);
        util::centerInside(m_text, t_context.layout.screenRect());
    }

    void StateSplash::onExit(const Context &) {}

    void StateSplash::update(const Context & t_context, const float t_elapsedSec)
    {
        m_elapsedSec += t_elapsedSec;
        if (m_elapsedSec > 6.0f)
        {
            t_context.state.setPending(State::PrePlay);
        }

        const float timeBetweenColorsSec{ 0.25f };
        m_colorElapsedSec += t_elapsedSec;
        if (m_colorElapsedSec > timeBetweenColorsSec)
        {
            m_colorElapsedSec = 0.0f;
            m_color1          = m_color2;
            m_color2          = colors::randomVibrant(t_context.random);
        }

        const float ratio{ util::map(m_colorElapsedSec, 0.0f, timeBetweenColorsSec, 0.0f, 1.0f) };
        const sf::Color color{ colors::blend(ratio, m_color1, m_color2) };
        m_text.setFillColor(color);
    }

    void StateSplash::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr{ t_event.getIf<sf::Event::KeyPressed>() };
        const auto * mousePtr{ t_event.getIf<sf::Event::MouseButtonPressed>() };
        if (keyPtr || mousePtr)
        {
            t_context.state.setPending(State::PrePlay);
            return;
        }
    }

    void StateSplash::draw(
        const Context &, sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        t_target.draw(m_text, t_states);
    }

} // namespace snake2
