#ifndef QUADTREENODE_HPP
#define QUADTREENODE_HPP

#include "Rectangle.hpp"
#include <vector>
#include <iostream>

class Entity;

class QuadtreeNode
{
    public:
        QuadtreeNode();
        ~QuadtreeNode() = default;

        QuadtreeNode* FindSmallestFit(const Rectangle& area);

        void Reset(const Rectangle& area);
        void Divide(QuadtreeNode* nodes, std::vector<Entity*>& entityBuffer);

        bool IsFull(std::size_t maxNodeCapacity) const
        {
            return !_nodes && _entities.size() >= maxNodeCapacity;
        }

        void GetCollisions(Entity& entity, const Rectangle& entityRectangle,
            std::vector<Entity*>& results);

        void DebugDump(std::ostream& stream, int tier);

    protected:
    private:
        QuadtreeNode(const QuadtreeNode&) = delete;
        QuadtreeNode& operator=(const QuadtreeNode&) = delete;

        std::vector<Entity*> _entities;
        QuadtreeNode* _nodes;
        Rectangle _area;

        friend class Quadtree;
};

#endif
