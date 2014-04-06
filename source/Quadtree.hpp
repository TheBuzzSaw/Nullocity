#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "QuadtreeNode.hpp"
#include <vector>
#include <iostream>

class Quadtree
{
    public:
        Quadtree(std::size_t maxNodeCapacity);
        ~Quadtree();

        void SetArea(const Rectangle& area) { _area = area; }

        void Clear();
        void Add(Entity& entity);
        const std::vector<Entity*>& GetCollisions(Entity& entity);
        void DebugDump(std::ostream& stream);

    protected:
    private:
        Quadtree(const Quadtree&) = delete;
        Quadtree& operator=(const Quadtree&) = delete;

        QuadtreeNode* GetFourNodes();

        std::vector<QuadtreeNode*> _nodePool;
        std::vector<Entity*> _entityBuffer;
        std::size_t _next;
        std::size_t _maxNodeCapacity;

        QuadtreeNode _node;
        Rectangle _area;
};

#endif
