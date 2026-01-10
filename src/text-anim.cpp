//
// text-anim.cpp
//
#include "text-anim.hpp"

#include "config.hpp"
#include "context.hpp"
#include "font.hpp"
#include "grid-display.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

#include <algorithm>

namespace snake2
{

    TextAnimation::TextAnimation()
        : is_alive{ true }
        , elapsed_sec{ 0.0f }
        , text{ util::SfmlDefaults::instance().font() }
        , orig_pos{ 0.0f, 0.0f }
    {}

    TextAnimationManager::TextAnimationManager()
        : m_animations{}
    {}

    void TextAnimationManager::setup(const Context &) { m_animations.reserve(16); }

    void TextAnimationManager::add(
        const Context & t_context,
        const GridPos_t & t_gridPos,
        const std::string & t_text,
        const sf::Color & t_color)
    {
        TextAnimation & anim{ m_animations.emplace_back() };
        anim.text = t_context.font.makeText(FontSize::Medium, t_text, t_color);

        const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
            t_context, t_gridPos) };

        anim.text.setPosition(
            { (util::center(screenRect).x - (anim.text.getGlobalBounds().size.x * 0.5f)),
              (screenRect.position.y - anim.text.getGlobalBounds().size.y) });

        anim.orig_pos = anim.text.getPosition();
    }

    void TextAnimationManager::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        bool didAnyFinish{ false };
        for (TextAnimation & anim : m_animations)
        {
            anim.elapsed_sec += t_elapsedTimeSec;
            if (anim.elapsed_sec > t_context.config.text_anim_duration_sec)
            {
                didAnyFinish  = true;
                anim.is_alive = false;
            }
            else
            {
                const float riseMax{ anim.text.getGlobalBounds().size.y *
                                        t_context.config.text_anim_rise_mult };

                const float rise{ util::map(
                    anim.elapsed_sec, 0.0f, t_context.config.text_anim_duration_sec, 0.0f, riseMax) };

                anim.text.setPosition(anim.orig_pos);
                anim.text.move({0.0f, -rise});

                const std::uint8_t alpha{ static_cast<std::uint8_t>(util::map(
                    anim.elapsed_sec, 0.0f, t_context.config.text_anim_duration_sec, 255, 0)) };

                sf::Color color{ anim.text.getFillColor() };
                color.a = alpha;
                anim.text.setFillColor(color);
            }
        }

        if (didAnyFinish)
        {
            std::erase_if(m_animations, [](const TextAnimation & anim) { return !anim.is_alive; });
        }
    }

    void TextAnimationManager::draw(
        sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        for (const TextAnimation & anim : m_animations)
        {
            t_target.draw(anim.text, t_states);
        }
    }

} // namespace snake2
