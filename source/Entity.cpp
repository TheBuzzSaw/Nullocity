#include "Entity.hpp"

Entity::Entity(SimpleBufferObject& object)
    : _radius(1.0f)
    , _scale(1.0f)
    , _object(&object)
{
}

Entity::~Entity()
{
}

void Entity::Update()
{
    _position += _velocity;
    _rotationX += _torqueX;
    _rotationY += _torqueY;
}

void Entity::Draw(SimpleProgram& program)
{
    program.Draw(*_object, GL_TRIANGLES);
}
