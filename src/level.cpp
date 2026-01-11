//
// level.cpp
//
#include "level.hpp"

#include "config.hpp"
#include "context.hpp"
#include "game-info.hpp"

namespace snake2
{

    void Level::setup(const Context & t_context)
    {
        //const std::size_t levelNumber{ t_context.game.level };

        food_eaten             = 0;
        food_to_spawn_on_start = t_context.config.food_pieces_per_level;

        // TODO
    }

} // namespace snake2
