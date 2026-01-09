#ifndef GRID_TYPES_HPP_INCLUDED
#define GRID_TYPES_HPP_INCLUDED
//
// grid-types.hpp
//
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace snake2
{

    using GridPos_t = sf::Vector2i;
    using GridPosVec_t = std::vector<GridPos_t>;
}

#endif // GRID_TYPES_HPP_INCLUDED
