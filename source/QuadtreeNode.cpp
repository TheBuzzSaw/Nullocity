#include "QuadtreeNode.hpp"
#include "Entity.hpp"
#include <cstring>

QuadtreeNode::QuadtreeNode()
    : _nodes(nullptr)
    , _parentNode(nullptr)
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

void QuadtreeNode::Reset(const Rectangle& area, QuadtreeNode* parentNode)
{
    _entities.clear();
    _nodes = nullptr;
    _parentNode = parentNode;
    _area = area;
}

void QuadtreeNode::Divide(QuadtreeNode* nodes,
    std::vector<Entity*>& entityBuffer)
{
    _nodes = nodes;
    _nodes[0].Reset(_area.UpperLeft(), this);
    _nodes[1].Reset(_area.UpperRight(), this);
    _nodes[2].Reset(_area.LowerLeft(), this);
    _nodes[3].Reset(_area.LowerRight(), this);

    entityBuffer = _entities;
    _entities.clear();

    for (auto i : entityBuffer)
    {
        auto radius = i->Radius();
        auto position = i->Position();

        Rectangle entityRectangle(position, SDL2TK::Vector2F(radius, radius));
        QuadtreeNode* node = this;

        for (int j = 0; j < 4; ++j)
        {
            if (_nodes[j]._area.Contains(entityRectangle))
            {
                node = _nodes + j;
                break;
            }
        }

        node->_entities.push_back(i);
    }
}

void QuadtreeNode::Audit(std::vector<Entity*>& entityBuffer)
{
    auto i = _entities.begin();

    while (i != _entities.end())
    {
        auto entity = *i;
        auto radius = entity->Radius();
        auto position = entity->Position();

        Rectangle entityRectangle(position, SDL2TK::Vector2F(radius, radius));

        if (!_area.Contains(entityRectangle))
        {
            entityBuffer.push_back(entity);
            i = _entities.erase(i);
        }
        else
        {
            ++i;
        }
    }

    if (_nodes)
    {
        for (int i = 0; i < 4; ++i)
            _nodes[i].Audit(entityBuffer);
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

void QuadtreeNode::DebugDump(std::ostream& stream, int tier)
{
    char indent[64];
    memset(indent, ' ', sizeof(indent));
    indent[tier * 2] = '\0';

    stream
        << indent
        << "QuadtreeNode ("
        << _entities.size()
        << " entit"
        << (_entities.size() == 1 ? "y" : "ies")
        << ") "
        << _area.Center().X()
        << ", "
        << _area.Center().Y()
        << " with radii "
        << _area.Radii().X()
        << ", "
        << _area.Radii().Y()
        << '\n';

    for (auto i : _entities)
    {
        auto position = i->Position();
        stream << indent << "  " << position.X() << ", " << position.Y()
            << " with radius " << i->Radius() << '\n';
    }

    if (_nodes)
    {
        for (int i = 0; i < 4; ++i)
            _nodes[i].DebugDump(stream, tier + 1);
    }
}
