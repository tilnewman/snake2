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

    //

    struct Context
    {
        Context(const Config & t_config, const Layout & t_layout, const GridDisplay & t_gridDisplay)
            : config{ t_config }
            , layout{ t_layout }
            , grid_display{ t_gridDisplay }
        {}

        const Config & config;
        const Layout & layout;
        const GridDisplay & grid_display;
    };

} // namespace snake2

#endif // CONTEXT_HPP_INCLUDED
