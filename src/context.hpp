#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
//
// context.hpp
//

namespace snake2
{

    struct Config;

    class Layout;
    class GridDisplay;
    class Snake;

    //

    struct Context
    {
        Context(
            const Config & t_config,
            const Layout & t_layout,
            Snake & t_snake,
            const GridDisplay & t_gridDisplay)
            : config{ t_config }
            , layout{ t_layout }
            , snake{ t_snake }
            , grid_display{ t_gridDisplay }
        {}

        const Config & config;
        const Layout & layout;
        Snake & snake;
        const GridDisplay & grid_display;
    };

} // namespace snake2

#endif // CONTEXT_HPP_INCLUDED
