#ifndef SPLAT_IMAGE_HPP_INCLUDED
#define SPLAT_IMAGE_HPP_INCLUDED
//
// splat-image.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace snake2
{

    struct Context;

    //

    class SplatImage
    {
      public:
        SplatImage();

        void setup(const Context & t_context);
        void startDisplaying(const Context & t_context, const GridPos_t & t_gridPos);
        void stopDisplaying() { m_willDisplay = false; }
        void draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const;

      private:
        sf::Texture m_texture;
        sf::Sprite m_sprite1;
        sf::Sprite m_sprite2;
        sf::Sprite m_sprite3;
        sf::Sprite m_sprite4;
        sf::Sprite m_visibleSprite;
        bool m_willDisplay;
    };

} // namespace snake2

#endif // SPLAT_IMAGE_HPP_INCLUDED
