#include "Quadtree.hpp"
#include "QuadtreeNode.hpp"
#include "Entity.hpp"
#include <cstring>

Quadtree::Quadtree(std::size_t maxNodeCapacity)
    : _next(0)
    , _maxNodeCapacity(maxNodeCapacity)
{
}

Quadtree::~Quadtree()
{
    for (auto i : _nodePool) delete [] i;
}

void Quadtree::Clear()
{
    _next = 0;
    _node.Reset(_area);
}

void Quadtree::Add(Entity& entity)
{
    auto radius = entity.Radius();
    auto position = entity.Position();

    Rectangle entityRectangle(position, SDL2TK::Vector2F(radius, radius));

    QuadtreeNode* node = _node.FindSmallestFit(entityRectangle);

    while (node->IsFull(_maxNodeCapacity))
    {
        node->Divide(GetFourNodes(), _entityBuffer);
        node = node->FindSmallestFit(entityRectangle);
    }

    node->_entities.push_back(&entity);
}

QuadtreeNode* Quadtree::GetFourNodes()
{
    QuadtreeNode* result;

    if (_next < _nodePool.size())
    {
        result = _nodePool[_next++];
    }
    else
    {
        result = new QuadtreeNode[4];
        _nodePool.push_back(result);
        ++_next;
    }

    return result;
}
