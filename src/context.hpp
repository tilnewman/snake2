#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
//
// context.hpp
//

namespace util
{
    class Random;
}

namespace snake2
{

    struct Config;

    class Layout;
    class GridDisplay;
    class Snake;
    class Actors;
    class CellAnimationManager;

    //

    struct Context
    {
        Context(
            const Config & t_config,
            const Layout & t_layout,
            const GridDisplay & t_gridDisplay,
            const util::Random & t_random,
            Snake & t_snake,
            Actors & t_actors,
            CellAnimationManager & t_cellAnimationManager)
            : config{ t_config }
            , layout{ t_layout }
            , grid_display{ t_gridDisplay }
            , random{ t_random }
            , snake{ t_snake }
            , actors{ t_actors }
            , cell_anim{ t_cellAnimationManager }

        {}

        const Config & config;
        const Layout & layout;
        const GridDisplay & grid_display;
        const util::Random & random;
        Snake & snake;
        Actors & actors;
        CellAnimationManager & cell_anim;
    };

} // namespace snake2

#endif // CONTEXT_HPP_INCLUDED
