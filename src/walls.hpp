#ifndef WALLS_HPP_INCLUDED
#define WALLS_HPP_INCLUDED
//
// walls.hpp
//
#include <cstdlib>

namespace snake2
{

    struct Context;

    //

    class Walls
    {
      public:
        static void halfHoriz(const Context & t_context);
        static void halfVert(const Context & t_context);
        static void full(const Context & t_context, const std::size_t t_thickness);
        static void cutHolesInBorderWalls(const Context & t_context);
        static void centerBlock(const Context & t_context);
    };

} // namespace snake2

#endif // WALLS_HPP_INCLUDED
