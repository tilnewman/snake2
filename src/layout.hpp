#ifndef LAYOUT_HPP_INLCUDED
#define LAYOUT_HPP_INLCUDED
//
// layout.hpp
//
#include "config.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace snake2
{

    class Layout
    {
      public:
        Layout();

        void setup(const Config & t_config);

        [[nodiscard]] const sf::FloatRect screenRect() const noexcept { return m_screenRect; }
        [[nodiscard]] const sf::FloatRect topRect() const noexcept { return m_topRect; }
        [[nodiscard]] const sf::FloatRect bottomRect() const noexcept { return m_bottomRect; }
        [[nodiscard]] const sf::FloatRect gridRect() const noexcept { return m_gridRect; }
        [[nodiscard]] const sf::Vector2f cellSize() const noexcept { return m_cellSize; }
        [[nodiscard]] const sf::Vector2u cellCount() const noexcept { return m_cellCount; }

      private:
        sf::FloatRect m_screenRect;
        sf::FloatRect m_topRect;
        sf::FloatRect m_bottomRect;
        sf::FloatRect m_gridRect;
        sf::Vector2f m_cellSize;
        sf::Vector2u m_cellCount;
    };

} // namespace snake2

#endif // LAYOUT_HPP_INLCUDED
