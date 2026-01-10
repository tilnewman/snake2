#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED
//
// config.hpp
//
#include <filesystem>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace snake2
{

    struct Config
    {
        std::filesystem::path media_path{};
        sf::VideoMode video_mode{ { 4112u, 2580u }, 32u };
        unsigned framerate_limit{ 0 };
        float top_region_height_ratio{ 0.035f };
        float cell_size_ratio{ 0.02f };
        sf::Color grid_frame_color{ 28, 28, 28 };
        sf::Color cell_background_color{ 16, 16, 16 };
        sf::Color cell_outline_color{ 0, 0, 0 };
        sf::Color cell_snake_first_color{ 64, 255, 64 };
        sf::Color cell_snake_last_color{ 0, 255, 0 };
        sf::Color cell_snake_death_color{ sf::Color::Red };
        sf::Color cell_food_color{ sf::Color::Yellow };
        sf::Color cell_wall_color{ 93, 46, 20 };
        sf::Color cell_shrink_color{ sf::Color::Magenta };
        sf::Color cell_slow_color{ sf::Color::Cyan };
        sf::Color cell_fast_color{ 255, 50, 100 };
        float snake_speed_change_ratio{ 0.25f };
        float cell_anim_duration_sec{ 0.25f };
        float cell_anim_scale_max{ 3.0f };
    };

} // namespace snake2

#endif // CONFIG_HPP_INCLUDED
