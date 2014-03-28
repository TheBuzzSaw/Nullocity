#include "CollisionHandler.hpp"
#include <iostream>

CollisionHandler::~CollisionHandler()
{

}

void CollisionHandler::CheckCollisions()
{
    auto size = Collidables.size();
    for (decltype(size) i = 0; i < size; i++)
    {
        for (decltype(size) j = i + 1; j < size; j++)
        {
            SDL2TK::Vector2F object1Pos = Collidables[i]->Position();
            SDL2TK::Vector2F object2Pos = Collidables[j]->Position();
            float object1Rad = Collidables[i]->Radius();
            float object2Rad = Collidables[j]->Radius();
            float minimumDistance = object1Rad + object2Rad;
            minimumDistance *= minimumDistance;
            float distance = (object1Pos - object2Pos).LengthSquared() - minimumDistance;

            if (distance <= 0)
            {
                std::cout << "Collision! " << i << " " << j << std::endl;
            }
        }
    }
}
