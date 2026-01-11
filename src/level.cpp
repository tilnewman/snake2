//
// level.cpp
//
#include "level.hpp"

#include "config.hpp"
#include "context.hpp"
#include "game-info.hpp"
#include "random.hpp"
#include "walls.hpp"

namespace snake2
{

    void Level::setup(const Context & t_context)
    {
        food_eaten             = 0;
        food_to_spawn_on_start = t_context.config.food_pieces_per_level;

        const std::size_t levelNumber{ t_context.game.level };

        // walls and obstacles
        if (levelNumber == 1)
        {
            // no walls on level 1
        }
        else if (levelNumber == 2)
        {
            Walls::halfVert(t_context);
        }
        else if (levelNumber == 3)
        {
            Walls::halfHoriz(t_context);
        }
        else if (levelNumber == 4)
        {
            Walls::full(t_context);
            Walls::cutHolesInBorderWalls(t_context);
        }
        else if (levelNumber == 5)
        {
            Walls::full(t_context);
        }
        else if (levelNumber == 6)
        {
            Walls::full(t_context);
            Walls::centerBlock(t_context);
        }
        else
        {
            if (t_context.random.fromTo(1, 6) == 1)
            {
                if (t_context.random.boolean())
                {
                    Walls::halfVert(t_context);
                }
                else
                {
                    Walls::halfHoriz(t_context);
                }
            }
            else
            {
                Walls::full(t_context);

                if (t_context.random.boolean())
                {
                    Walls::cutHolesInBorderWalls(t_context);
                }
            }

            if (t_context.random.boolean())
            {
                Walls::centerBlock(t_context);
            }
        }
    }

} // namespace snake2
