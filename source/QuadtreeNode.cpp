#include "QuadtreeNode.hpp"
#include "Entity.hpp"

QuadtreeNode::QuadtreeNode()
    : _nodes(nullptr)
{
}

QuadtreeNode* QuadtreeNode::FindSmallestFit(const Rectangle& area)
{
    QuadtreeNode* result = this;

    if (_nodes)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (_nodes[i]._area.Contains(area))
                result = _nodes[i].FindSmallestFit(area);
        }
    }

    return result;
}

void QuadtreeNode::Reset(const Rectangle& area)
{
    _entities.clear();
    _nodes = nullptr;
    _area = area;
}

void QuadtreeNode::Divide(QuadtreeNode* nodes,
    std::vector<Entity*>& entityBuffer)
{
    _nodes = nodes;
    _nodes[0].Reset(_area.UpperLeft());
    _nodes[1].Reset(_area.UpperRight());
    _nodes[2].Reset(_area.LowerLeft());
    _nodes[3].Reset(_area.LowerRight());

    entityBuffer = _entities;
    _entities.clear();

    for (auto i : entityBuffer)
    {
        Entity& entity = *i;
        auto radius = entity.Radius();
        auto position = entity.Position();

        Rectangle entityRectangle(position, SDL2TK::Vector2F(radius, radius));
        QuadtreeNode* node = this;

        for (int j = 0; j < 4; ++j)
        {
            if (_nodes[j]._area.Contains(entityRectangle)) node = _nodes + j;
        }

        node->_entities.push_back(i);
    }
}

void QuadtreeNode::GetCollisions(Entity& entity,
    const Rectangle& entityRectangle, std::vector<Entity*>& results)
{
    for (auto i : _entities)
    {
        if (&entity < i && entity.Overlaps(*i))
            results.push_back(i);

        if (_nodes)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (!entityRectangle.Avoids(_nodes[j]._area))
                    _nodes[j].GetCollisions(entity, entityRectangle, results);
            }
        }
    }
}
