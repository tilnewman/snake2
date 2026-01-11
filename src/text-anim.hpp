#ifndef TEXT_ANIM_HPP_INCLUDED
#define TEXT_ANIM_HPP_INCLUDED
//
// text-anim.hpp
//
#include "grid-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <vector>

namespace snake2
{

    struct Context;

    //

    struct TextAnimation
    {
        TextAnimation();

        bool is_alive;
        float elapsed_sec;
        sf::Text text;
        sf::Vector2f orig_pos;
    };

    //

    class TextAnimationManager
    {
      public:
        TextAnimationManager();

        void setup(const Context & t_context);

        void
            add(const Context & t_context,
                const GridPos_t & t_gridPos,
                const std::string & t_text,
                const sf::Color & t_color);

        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const;
        void clear() { m_animations.clear(); }

      private:
        std::vector<TextAnimation> m_animations;
    };

} // namespace snake2

#endif // TEXT_ANIM_HPP_INCLUDED
