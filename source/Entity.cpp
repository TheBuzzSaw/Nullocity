#include "Entity.hpp"

Entity::Entity(SimpleBufferObject& mObject)
{
    _radius = 1;
    _object = &mObject;
}

Entity::~Entity()
{
}

void Entity::Update()
{
    updatePosition();
}

void Entity::Draw(SimpleProgram& program)
{
    program.Draw(*_object, GL_TRIANGLES);
}

void Entity::updatePosition()
{
    _position += _velocity;
    _rotationX += _torqueX;
    _rotationY += _torqueY;
}
