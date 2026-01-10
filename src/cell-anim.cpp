//
// cell-anim.cpp
//
#include "cell-anim.hpp"

#include "config.hpp"
#include "context.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"

#include <algorithm>

namespace snake2
{
    CellAnimationManager::CellAnimationManager()
        : m_animations{}
    {}

    void CellAnimationManager::setup(const Context &) { m_animations.reserve(64); }

    void CellAnimationManager::add(
        const Context & t_context, const GridPos_t & t_gridPos, const sf::Color & t_color)
    {
        const sf::FloatRect screenRect{ t_context.grid_display.gridPosToScreenRect(
            t_context, t_gridPos) };

        CellAnimation & anim{ m_animations.emplace_back() };
        anim.color = t_color;
        anim.rectangle.setFillColor(t_color);
        anim.rectangle.setPosition(screenRect.position);
        anim.rectangle.setSize(screenRect.size);
        util::setOriginToCenter(anim.rectangle);
        anim.rectangle.move(screenRect.size * 0.5f);
    }

    void CellAnimationManager::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        bool didAnyFinish{ false };

        for (CellAnimation & anim : m_animations)
        {
            anim.elapsed_sec += t_elapsedTimeSec;
            if (anim.elapsed_sec < t_context.config.cell_anim_duration_sec)
            {
                const float scale{ util::map(
                    anim.elapsed_sec,
                    0.0f,
                    t_context.config.cell_anim_duration_sec,
                    1.0f,
                    t_context.config.cell_anim_scale_max) };

                anim.rectangle.setScale({ scale*scale, scale*scale });

                const std::uint8_t alpha{ static_cast<std::uint8_t>(util::map(
                    anim.elapsed_sec, 0.0f, t_context.config.cell_anim_duration_sec, 127, 0)) };

                sf::Color color{ anim.color };
                color.a = alpha;
                anim.rectangle.setFillColor(color);
            }
            else
            {
                didAnyFinish = true;
                anim.is_finished = true;
            }
        }

        if (didAnyFinish)
        {
            std::erase_if(
                m_animations, [](const CellAnimation & anim) { return anim.is_finished; });
        }
    }

    void CellAnimationManager::draw(
        sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        for (const CellAnimation & anim : m_animations)
        {
            t_target.draw(anim.rectangle, t_states);
        }
    }

} // namespace snake2
