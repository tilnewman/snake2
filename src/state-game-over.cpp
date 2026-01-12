//
// state-game-over.cpp
//
#include "state-game-over.hpp"

#include "color-range.hpp"
#include "config.hpp"
#include "context.hpp"
#include "font.hpp"
#include "game-info.hpp"
#include "layout.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"

namespace snake2
{

    StatAnimation::StatAnimation(
        const Context & t_context, const std::string & t_labelStr, const std::size_t t_stat)
        : phase{ StatAnimPhase::Label }
        , label_text{ t_context.font.makeText(FontSize::Large, t_labelStr, sf::Color::Cyan) }
        , stat_text{ t_context.font.makeText(
              FontSize::Large, std::to_string(t_stat), sf::Color::Cyan) }
        , elapsed_sec{ 0.0f }
    {
        const sf::FloatRect screenRect{ t_context.layout.screenRect() };
        label_text.setPosition({ screenRect.size.x, (screenRect.size.y * 0.5f) });
        stat_text.setPosition({ screenRect.size.x, (screenRect.size.y * 0.55f) });
    }

    //

    StateGameOver::StateGameOver()
        : m_colorElapsedSec{ 0.0f }
        , m_text{ util::SfmlDefaults::instance().font() }
        , m_color1{}
        , m_color2{}
        , m_animations{}
        , m_animIndex{ 0 }
        , m_slider{ 2.5f }
    {}

    void StateGameOver::onEnter(const Context & t_context)
    {
        // setup color cycling
        m_color1 = sf::Color::Cyan;
        m_color2 = colors::randomVibrant(t_context.random);

        // setup snake title text
        m_text = t_context.font.makeText(FontSize::Colossal, "Game Over", m_color1);
        util::centerInside(m_text, t_context.layout.screenRect());
        m_text.move({ 0.0f, -(t_context.layout.screenRect().size.y * 0.2f) });

        // setup animations
        m_animations.reserve(12);

        m_animations.emplace_back(t_context, "Final Score", t_context.game.score);

        m_animations.emplace_back(t_context, "Final Level", t_context.game.level);

        m_animations.emplace_back(
            t_context, "Longest Tail Length", t_context.game.longest_tail_length);

        m_animations.emplace_back(t_context, "Food Pieces Eaten", t_context.game.food_pieces_eaten);

        m_animations.emplace_back(
            t_context, "Shrink Pieces Eaten", t_context.game.shrink_pieces_eaten);

        m_animations.emplace_back(t_context, "Slow Pieces Eaten", t_context.game.slow_pieces_eaten);

        m_animations.emplace_back(
            t_context, "Tail Pieces Eaten", t_context.game.snake_pieces_eaten);

        m_animations.emplace_back(
            t_context, "Brick Pieces Eaten", t_context.game.brick_pieces_eaten);

        m_animations.emplace_back(t_context, "Near Misses", t_context.game.miss_count);

        m_animations.emplace_back(t_context, "Times Killed", t_context.game.death_count);
    }

    void StateGameOver::onExit(const Context &) {}

    void StateGameOver::update(const Context & t_context, const float t_elapsedSec)
    {
        updateSnakeTextColor(t_context, t_elapsedSec);
        updateAnimations(t_context, t_elapsedSec);
    }

    void StateGameOver::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr{ t_event.getIf<sf::Event::KeyPressed>() };
        const auto * mousePtr{ t_event.getIf<sf::Event::MouseButtonPressed>() };
        if (keyPtr || mousePtr)
        {
            t_context.state.setPending(State::Quit);
            return;
        }
    }

    void StateGameOver::draw(
        const Context &, sf::RenderTarget & t_target, const sf::RenderStates & t_states) const
    {
        t_target.draw(m_text, t_states);
        t_target.draw(m_animations.at(m_animIndex).label_text, t_states);
        t_target.draw(m_animations.at(m_animIndex).stat_text, t_states);
    }

    void StateGameOver::updateSnakeTextColor(const Context & t_context, const float t_elapsedSec)
    {
        const float timeBetweenColorsSec{ 1.5f };
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

    void StateGameOver::updateAnimations(const Context & t_context, const float t_elapsedSec)
    {
        StatAnimation & anim = m_animations.at(m_animIndex);

        if (StatAnimPhase::Label == anim.phase)
        {
            const sf::FloatRect screenRect{ t_context.layout.screenRect() };

            const float amountToMoveLabel{ screenRect.size.x -
                                           ((screenRect.size.x * 0.5f) -
                                            (anim.label_text.getGlobalBounds().size.x * 0.5f)) };

            const float amountToMoveStat{ screenRect.size.x -
                                          ((screenRect.size.x * 0.5f) -
                                           (anim.stat_text.getGlobalBounds().size.x * 0.5f)) };

            const float moveRatio{ m_slider.update(t_elapsedSec) };

            anim.label_text.setPosition({ screenRect.size.x, anim.label_text.getPosition().y });
            anim.label_text.move({ -(amountToMoveLabel * moveRatio), 0.0f });

            anim.stat_text.setPosition({ screenRect.size.x, anim.stat_text.getPosition().y });
            anim.stat_text.move({ -(amountToMoveStat * moveRatio), 0.0f });

            if (!m_slider.isMoving())
            {
                m_slider.restart();
                anim.phase = StatAnimPhase::Hold;
            }
        }
        else if (StatAnimPhase::Hold == anim.phase)
        {
            anim.elapsed_sec += t_elapsedSec;
            if (anim.elapsed_sec > 4.0f)
            {
                anim.elapsed_sec = 0.0f;
                anim.phase       = StatAnimPhase::Label;

                if (++m_animIndex >= m_animations.size())
                {
                    m_animIndex = 0;
                }
            }
        }
    }

} // namespace snake2
