#ifndef FRAMERATE_DISPLAY_HPP_INCLUDED
#define FRAMERATE_DISPLAY_HPP_INCLUDED
//
// framerate-display.hpp
//
#include "font.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace snake2
{

    struct Context;

    //

    class FramerateDisplay
    {
      public:
        FramerateDisplay();

        void setup(const Context & t_context);
        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const;

      private:
        float m_elapsedTimeSec;
        std::size_t m_frameCounter;
        sf::Text m_text;
    };

} // namespace snake2

#endif // FRAMERATE_DISPLAY_HPP_INCLUDED
