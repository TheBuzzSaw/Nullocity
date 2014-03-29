#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2TK/Rotation.hpp>
#include <SDL2TK/Vector.hpp>
#include "SimpleProgram.hpp"
#include "SimpleBufferObject.hpp"

class Entity
{
    public:
        Entity(SimpleBufferObject& mObject);
        virtual ~Entity();

        const SDL2TK::Vector2F Position() const { return _position; }
        const SDL2TK::Vector2F Velocity() const { return _position; }
        const SDL2TK::RotationF RotationX() const { return _rotationX; }
        const SDL2TK::RotationF RotationY() const { return _rotationY; }
        const SDL2TK::RotationF TorqueX() const { return _rotationX; }
        const SDL2TK::RotationF TorqueY() const { return _torqueY; }

        const float Radius() const { return _radius; }

        void Update();

        void SetPositon(SDL2TK::Vector2F position) { _position = position; }
        void SetVelocity(SDL2TK::Vector2F velocity) { _velocity = velocity; }
        void SetRotation(SDL2TK::RotationF x, SDL2TK::RotationF y) { _rotationX = x; _rotationY = y; }
        void SetTorque(SDL2TK::RotationF x, SDL2TK::RotationF y) { _torqueX = x; _torqueY = y; }
        void SetRadius(float radius) { _radius = radius; }
        void Draw (SimpleProgram& program);

    protected:
    private:
        SDL2TK::Vector2F _position;
        SDL2TK::RotationF _rotationX;
        SDL2TK::RotationF _rotationY;

        SDL2TK::Vector2F _velocity;
        SDL2TK::RotationF _torqueX;
        SDL2TK::RotationF _torqueY;

        float _radius;

        SimpleBufferObject* _object;

        void updatePosition();
};

#endif
