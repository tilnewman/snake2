#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED
//
// config.hpp
//
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace snake2
{

    struct Config
    {
        sf::VideoMode video_mode{ { 4112u, 2580u }, 32u };
        unsigned framerate_limit{ 0 };
        float top_region_height_ratio{ 0.035f };
        sf::Vector2u cell_counts{ 100u, 60u };
        sf::Color grid_color_background{ 22, 22, 22 };
        sf::Color grid_color_outline{ 0, 0, 0 };
    };

} // namespace gameoflife

#endif // CONFIG_HPP_INCLUDED
