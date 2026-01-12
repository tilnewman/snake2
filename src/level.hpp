#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED
//
// level.hpp
//
#include <cstddef>

namespace snake2
{

    struct Context;

    //

    struct Level
    {
        std::size_t food_to_spawn_on_start{ 0 };
        std::size_t food_to_spawn_after_start{ 0 };
        std::size_t food_eaten{ 0 };

        void setup(const Context & t_context);
    };

} // namespace snake2

#endif // LEVEL_HPP_INCLUDED
