// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// splat-image.cpp
//
#include "splat-image.hpp"

#include "config.hpp"
#include "context.hpp"
#include "grid-display.hpp"
#include "layout.hpp"
#include "random.hpp"
#include "sfml-util.hpp"

#include <stdexcept>

namespace snake2
{

    SplatImage::SplatImage()
        : m_texture{}
        , m_sprite1{ m_texture }
        , m_sprite2{ m_texture }
        , m_sprite3{ m_texture }
        , m_sprite4{ m_texture }
        , m_visibleSprite{ m_texture }
        , m_willDisplay{ false }
    {}

    void SplatImage::setup(const Context & t_context)
    {
        if (!m_texture.loadFromFile(t_context.config.media_path / "image" / "splat.png"))
        {
            throw std::runtime_error("Failed to load splat image texture!");
        }

        m_texture.setSmooth(true);

        m_sprite1.setTexture(m_texture, true);
        m_sprite2.setTexture(m_texture, true);
        m_sprite3.setTexture(m_texture, true);
        m_sprite4.setTexture(m_texture, true);

        m_sprite1.setTextureRect({ { 0, 0 }, { 320, 320 } });
        m_sprite2.setTextureRect({ { 320, 0 }, { 320, 320 } });
        m_sprite3.setTextureRect({ { 0, 320 }, { 320, 320 } });
        m_sprite4.setTextureRect({ { 320, 320 }, { 320, 320 } });

        const sf::Color color(255, 0, 0);
        m_sprite1.setColor(color);
        m_sprite2.setColor(color);
        m_sprite3.setColor(color);
        m_sprite4.setColor(color);

        m_sprite1.setOrigin({ 160, 160 });
        m_sprite2.setOrigin({ 160, 160 });
        m_sprite3.setOrigin({ 160, 160 });
        m_sprite4.setOrigin({ 160, 160 });
    }

    void SplatImage::startDisplaying(const Context & t_context, const GridPos_t & t_gridPos)
    {
        const int randomIndex{ t_context.random.fromTo(1, 4) };
        if (randomIndex == 1)
        {
            m_visibleSprite = m_sprite1;
        }
        else if (randomIndex == 2)
        {
            m_visibleSprite = m_sprite2;
        }
        else if (randomIndex == 3)
        {
            m_visibleSprite = m_sprite3;
        }
        else
        {
            m_visibleSprite = m_sprite4;
        }

        const sf::Vector2f scaleVec{ t_context.layout.screenRect().size *
                                      sf::Vector2f{ 0.2f, 0.2f } };

        util::fit(m_visibleSprite, scaleVec);

        const sf::FloatRect positionRect{ t_context.grid_display.gridPosToScreenRect(
            t_context, t_gridPos) };

        m_visibleSprite.setPosition(util::center(positionRect));
        m_visibleSprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));
        m_willDisplay = true;
    }

    void SplatImage::draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        if (m_willDisplay)
        {
            t_target.draw(m_visibleSprite, t_states);
        }
    }

} // namespace snake2