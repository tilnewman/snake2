#ifndef TOP_PANEL_HPP_INCLUDED
#define TOP_PANEL_HPP_INCLUDED
//
// top-panel.hpp
//
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace snake2
{

    struct Context;

    //

    class TopPanel
    {
      public:
        TopPanel();

        void setup(const Context & t_context);
        void update(const Context & t_context);
        void draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const;

      private:
        std::unique_ptr<sf::Text> m_scoreTextUPtr;
        std::unique_ptr<sf::Text> m_livesTextUPtr;
        std::unique_ptr<sf::Text> m_levelTextUPtr;
    };

} // namespace snake2

#endif // TOP_PANEL_HPP_INCLUDED
