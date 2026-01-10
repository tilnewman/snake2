//
// framerate-display.cpp
//
#include "framerate-display.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

#include <sstream>

namespace snake2
{

    FramerateDisplay::FramerateDisplay()
        : m_elapsedTimeSec{ 0.0f }
        , m_frameCounter{ 0 }
        , m_text{ util::SfmlDefaults::instance().font() }
    {}

    void FramerateDisplay::setup(const Context & t_context)
    {
        m_text = t_context.font.makeText(FontSize::Small, "");
    }

    void FramerateDisplay::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        ++m_frameCounter;

        m_elapsedTimeSec += t_elapsedTimeSec;
        if (m_elapsedTimeSec > 1.0f)
        {
            const std::size_t framesPerSec{ static_cast<std::size_t>(
                static_cast<float>(m_frameCounter) / m_elapsedTimeSec) };

            m_frameCounter = 0;
            m_elapsedTimeSec -= 1.0f;

            std::string message{ "FPS:" };
            message += std::to_string(framesPerSec);
            m_text.setString(message);
            util::setOriginToPosition(m_text);

            m_text.setPosition(
                { 0.0f,
                  (util::bottom(t_context.layout.topRect()) - m_text.getGlobalBounds().size.y) });
        }
    }

    void
        FramerateDisplay::draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        t_target.draw(m_text, t_states);
    }

} // namespace snake2
