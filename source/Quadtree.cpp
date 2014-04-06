#include "Quadtree.hpp"
#include <cstring>

Quadtree::Quadtree()
{
    memset(_subtrees, 0, sizeof(_subtrees));
}

Quadtree::~Quadtree()
{
}
