#ifndef WALLS_HPP_INCLUDED
#define WALLS_HPP_INCLUDED
//
// walls.hpp
//

namespace snake2
{

    struct Context;

    //

    class Walls
    {
      public:
        void halfHoriz(const Context & t_context);
        void halfVert(const Context & t_context);
        void full(const Context & t_context);
        void fullWithHoles(const Context & t_context);
    };

} // namespace snake2

#endif // WALLS_HPP_INCLUDED
