#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED
//
// level.hpp
//
#include <cstddef>

namespace snake2
{

    struct Level
    {
        std::size_t food_to_spawn_on_start{ 0 };
        std::size_t food_to_spawn_after_start{ 0 };
        bool will_spawn_shrink_pieces{ false };
        bool will_spawn_slow_pieces{ false };

        void setup(const std::size_t t_levelNumber);
    };

} // namespace snake2

#endif // LEVEL_HPP_INCLUDED
