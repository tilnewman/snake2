#ifndef GAME_INFO_HPP_INCLUDED
#define GAME_INFO_HPP_INCLUDED
//
// game-info.hpp
//
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
        std::size_t longest_tail_length{ 0 };
        std::size_t miss_count{ 0 };
    };

} // namespace snake2

#endif // GAME_INFO_HPP_INCLUDED
