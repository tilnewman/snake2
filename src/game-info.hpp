#ifndef GAME_INFO_HPP_INCLUDED
#define GAME_INFO_HPP_INCLUDED
//
// game-info.hpp
//
#include "json-wrapper.hpp"

#include <cstddef>

namespace snake2
{

    struct GameInfo
    {
        std::size_t lives{ 3 };
        std::size_t score{ 0 };
        std::size_t level{ 1 };

        // statistics tracking
        std::size_t food_pieces_eaten{ 0 };
        std::size_t shrink_pieces_eaten{ 0 };
        std::size_t slow_pieces_eaten{ 0 };
        std::size_t snake_pieces_eaten{ 0 };
        std::size_t brick_pieces_eaten{ 0 };
        std::size_t rainbow_pieces_eaten{ 0 };
        std::size_t longest_tail_length{ 0 };
        std::size_t miss_count{ 0 };
        std::size_t death_count{ 0 };
    };

    inline void to_json(nlohmann::json & j, const GameInfo & gi)
    {
        j = nlohmann::json{
            { "lives", gi.lives },
            { "score", gi.score },
            { "level", gi.level },
            { "food_pieces_eaten", gi.food_pieces_eaten },
            { "shrink_pieces_eaten", gi.shrink_pieces_eaten },
            { "slow_pieces_eaten", gi.slow_pieces_eaten },
            { "snake_pieces_eaten", gi.snake_pieces_eaten },
            { "brick_pieces_eaten", gi.brick_pieces_eaten },
            { "rainbow_pieces_eaten", gi.rainbow_pieces_eaten },
            { "longest_tail_length", gi.longest_tail_length },
            { "miss_count", gi.miss_count },
            { "death_count", gi.death_count },
        };
    }

    inline void from_json(const nlohmann::json & j, GameInfo & gi)
    {
        j.at("lives").get_to(gi.lives);
        j.at("score").get_to(gi.score);
        j.at("level").get_to(gi.level);
        j.at("food_pieces_eaten").get_to(gi.food_pieces_eaten);
        j.at("shrink_pieces_eaten").get_to(gi.shrink_pieces_eaten);
        j.at("slow_pieces_eaten").get_to(gi.slow_pieces_eaten);
        j.at("snake_pieces_eaten").get_to(gi.snake_pieces_eaten);
        j.at("brick_pieces_eaten").get_to(gi.brick_pieces_eaten);
        j.at("rainbow_pieces_eaten").get_to(gi.rainbow_pieces_eaten);
        j.at("longest_tail_length").get_to(gi.longest_tail_length);
        j.at("miss_count").get_to(gi.miss_count);
        j.at("death_count").get_to(gi.death_count);
    }

} // namespace snake2

#endif // GAME_INFO_HPP_INCLUDED
