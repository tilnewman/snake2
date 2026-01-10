#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
//
// context.hpp
//

namespace util
{
    class Random;
    class SoundPlayer;
} // namespace util

namespace snake2
{

    struct Config;

    class Layout;
    class GridDisplay;
    class Snake;
    class Actors;
    class CellAnimationManager;
    class FontManager;
    class StateManager;

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
            CellAnimationManager & t_cellAnimationManager,
            util::SoundPlayer & t_soundPlayer,
            FontManager & t_fontManager,
            StateManager & t_stateManager)
            : config{ t_config }
            , layout{ t_layout }
            , grid_display{ t_gridDisplay }
            , random{ t_random }
            , snake{ t_snake }
            , actors{ t_actors }
            , cell_anim{ t_cellAnimationManager }
            , sfx{ t_soundPlayer }
            , font{ t_fontManager }
            , state{ t_stateManager }
        {}

        const Config & config;
        const Layout & layout;
        const GridDisplay & grid_display;
        const util::Random & random;
        Snake & snake;
        Actors & actors;
        CellAnimationManager & cell_anim;
        util::SoundPlayer & sfx;
        FontManager & font;
        StateManager & state;
    };

} // namespace snake2

#endif // CONTEXT_HPP_INCLUDED
