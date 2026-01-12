//
// top-panel.cpp
//
#include "top-panel.hpp"

#include "context.hpp"
#include "font.hpp"
#include "game-info.hpp"
#include "layout.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

#include <string>

namespace snake2
{

    TopPanel::TopPanel()
        : m_scoreTextUPtr{}
        , m_livesTextUPtr{}
        , m_levelTextUPtr{}
    {}

    void TopPanel::setup(const Context & t_context)
    {
        m_livesTextUPtr = std::make_unique<sf::Text>(t_context.font.font());
        m_scoreTextUPtr = std::make_unique<sf::Text>(t_context.font.font());
        m_levelTextUPtr = std::make_unique<sf::Text>(t_context.font.font());

        const sf::Color yellow(230, 190, 50);
        const sf::Color orange(255, 170, 60);
        const sf::Color creamCool(230, 190, 180, 192);

        *m_livesTextUPtr = t_context.font.makeText(FontSize::Large, "Lives:", yellow);
        *m_scoreTextUPtr = t_context.font.makeText(FontSize::Large, "Score:", orange);
        *m_levelTextUPtr = t_context.font.makeText(FontSize::Large, "Level:", creamCool);

        update(t_context);
    }

    void TopPanel::update(const Context & t_context)
    {
        const sf::FloatRect topRect{ t_context.layout.topRect() };

        std::string str{ "Lives: " };
        str += std::to_string(t_context.game.lives);
        m_livesTextUPtr->setString(str);
        util::setOriginToPosition(*m_livesTextUPtr);

        m_livesTextUPtr->setPosition(
            { ((topRect.size.x * 0.875f) - (m_livesTextUPtr->getGlobalBounds().size.x * 0.5f)),
              ((topRect.size.y - m_livesTextUPtr->getGlobalBounds().size.y) - 10.0f) });

        str = "Score: ";
        str += std::to_string(t_context.game.score);
        m_scoreTextUPtr->setString(str);
        util::setOriginToPosition(*m_scoreTextUPtr);

        m_scoreTextUPtr->setPosition(
            { ((topRect.size.x * 0.125f) - (m_livesTextUPtr->getGlobalBounds().size.x * 0.5f)),
              (topRect.size.y - m_livesTextUPtr->getGlobalBounds().size.y) });

        str = "Level: ";
        str += std::to_string(t_context.game.level);
        m_levelTextUPtr->setString(str);
        util::setOriginToPosition(*m_levelTextUPtr);

        m_levelTextUPtr->setPosition(
            { ((topRect.size.x * 0.5f) - (m_livesTextUPtr->getGlobalBounds().size.x * 0.5f)),
              (topRect.size.y - m_livesTextUPtr->getGlobalBounds().size.y) });
    }

    void TopPanel::draw(sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        t_target.draw(*m_scoreTextUPtr, t_states);
        t_target.draw(*m_livesTextUPtr, t_states);
        t_target.draw(*m_levelTextUPtr, t_states);
    }

} // namespace snake2
