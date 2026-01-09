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
        float cell_size_ratio{ 0.025f };
        sf::Color grid_frame_color{ 28, 28, 28 };
        sf::Color cell_background_color{ 16, 16, 16 };
        sf::Color cell_outline_color{ 0, 0, 0 };
        sf::Color cell_snake_first_color{ 64, 255, 64 };
        sf::Color cell_snake_last_color{ 0, 255, 0 };
        sf::Color cell_snake_death_color{ sf::Color::Red };
        sf::Color cell_food_color{ sf::Color::Yellow };
        sf::Color cell_wall_color{ 93, 46, 20 };
        sf::Color cell_shrink_color{ sf::Color::Magenta };
    };

} // namespace snake2

#endif // CONFIG_HPP_INCLUDED
