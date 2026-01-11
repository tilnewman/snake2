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
    struct GameInfo;
    struct Level;

    class Layout;
    class GridDisplay;
    class Snake;
    class Actors;
    class CellAnimationManager;
    class FontManager;
    class StateManager;
    class TextAnimationManager;
    class TopPanel;

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
            TextAnimationManager & t_textAnimationManager,
            util::SoundPlayer & t_soundPlayer,
            FontManager & t_fontManager,
            StateManager & t_stateManager,
            GameInfo & t_gameInfo,
            Level & t_levelInfo,
            TopPanel & t_topPanel)
            : config{ t_config }
            , layout{ t_layout }
            , grid_display{ t_gridDisplay }
            , random{ t_random }
            , snake{ t_snake }
            , actors{ t_actors }
            , cell_anim{ t_cellAnimationManager }
            , text_anim{ t_textAnimationManager }
            , sfx{ t_soundPlayer }
            , font{ t_fontManager }
            , state{ t_stateManager }
            , game{ t_gameInfo }
            , level{ t_levelInfo }
            , top{ t_topPanel }
        {}

        const Config & config;
        const Layout & layout;
        const GridDisplay & grid_display;
        const util::Random & random;
        Snake & snake;
        Actors & actors;
        CellAnimationManager & cell_anim;
        TextAnimationManager & text_anim;
        util::SoundPlayer & sfx;
        FontManager & font;
        StateManager & state;
        GameInfo & game;
        Level & level;
        TopPanel & top;
    };

} // namespace snake2

#endif // CONTEXT_HPP_INCLUDED
