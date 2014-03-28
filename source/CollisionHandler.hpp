#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "entity.hpp"
#include <vector>

class CollisionHandler
{
    public:
        CollisionHandler() = default;
        virtual ~CollisionHandler();

        void AddEntity(Entity& entity) { Collidables.push_back(&entity); }

        void CheckCollisions();
    protected:
    private:
        std::vector<Entity*> Collidables;
};

#endif // COLLISIONHANDLER_HPP
