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

        [[nodiscard]] const sf::FloatRect screenRect() noexcept { return m_screenRect; }
        [[nodiscard]] const sf::FloatRect topRect() noexcept { return m_topRect; }
        [[nodiscard]] const sf::FloatRect bottomRect() noexcept { return m_bottomRect; }
        [[nodiscard]] const sf::FloatRect gridRect() noexcept { return m_gridRect; }

      private:
        sf::FloatRect m_screenRect;
        sf::FloatRect m_topRect;
        sf::FloatRect m_bottomRect;
        sf::FloatRect m_gridRect;
    };

} // namespace snake2

#endif // LAYOUT_HPP_INLCUDED
