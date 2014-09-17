#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Matrix4x4.hpp"

namespace SDL2TK
{
    template<typename T>
    class Camera
    {
        public:
            Camera()
            {
            }

            Camera(const Camera& other)
                : _position(other._position)
                , _horizontal(other._horizontal)
                , _vertical(other._vertical)
                , _twist(other._twist)
                , _distance(other._distance)
            {
            }

            ~Camera()
            {
            }

            Camera& operator=(const Camera& other)
            {
                if (this != &other)
                {
                    _position = other._position;
                    _horizontal = other._horizontal;
                    _vertical = other._vertical;
                    _twist = other._twist;
                    _distance = other._distance;
                }

                return *this;
            }

            void Position(const Vector3<T>& position)
            {
                _position = position;
            }

            const Vector3<T>& Position() const
            {
                return _position;
            }

            void Horizontal(const Rotation<T> horizontal)
            {
                _horizontal = horizontal;
            }

            const Rotation<T> Horizontal() const
            {
                return _horizontal;
            }

            void Vertical(const Rotation<T> vertical)
            {
                _vertical = vertical;
            }

            const Rotation<T> Vertical() const
            {
                return _vertical;
            }

            void Twist(const Rotation<T> twist)
            {
                _twist = twist;
            }

            void Distance(T distance)
            {
                _distance = std::max<T>(distance, 0);
            }

            T Distance() const
            {
                return _distance;
            }

            void Apply(Matrix4x4<T>& matrix) const
            {
                matrix
                    .Translate(0, 0, -_distance)
                    .RotateY(_twist)
                    .RotateX(_vertical)
                    .RotateZ(_horizontal)
                    .Translate(-_position);
            }

        private:
            Vector3<T> _position;
            Rotation<T> _horizontal;
            Rotation<T> _vertical;
            Rotation<T> _twist;
            T _distance;
    };
}

#endif
