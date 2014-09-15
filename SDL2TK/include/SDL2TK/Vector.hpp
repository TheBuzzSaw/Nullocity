#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <cstring>
#include <iostream>

namespace SDL2TK
{
    template<typename T> class Vector2;
    template<typename T> class Vector3;
    template<typename T> class Vector4;

    template<typename T>
    class Vector2
    {
        public:
            constexpr Vector2() : _values{0, 0} {}
            constexpr Vector2(T x) : _values{x, 0} {}
            constexpr Vector2(T x, T y) : _values{x, y} {}

            Vector2(const Vector2& other)
            {
                memcpy(_values, other._values, sizeof(T) * 2);
            }

            Vector2(const Vector3<T>& other)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 2);
            }

            Vector2(const Vector4<T>& other)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 2);
            }

            constexpr T LengthSquared() const { return X() * X() + Y() * Y(); }

            T* Data() { return _values; }
            constexpr const T* ReadOnlyData() const { return _values; }

            constexpr T X() const { return _values[0]; }
            constexpr T Y() const { return _values[1]; }

            void X(T value) { _values[0] = value; }
            void Y(T value) { _values[1] = value; }

            Vector2& operator=(const Vector2& other)
            {
                memcpy(_values, other._values, sizeof(T) * 2);
                return *this;
            }

            Vector2& operator+=(const Vector2& other)
            {
                for (int i = 0; i < 2; ++i)
                    _values[i] += other._values[i];

                return *this;
            }

            Vector2& operator-=(const Vector2& other)
            {
                for (int i = 0; i < 2; ++i)
                    _values[i] -= other._values[i];

                return *this;
            }

            Vector2& operator *=(T multiplier)
            {
                for (int i = 0; i < 2; ++i)
                    _values[i] *= multiplier;

                return *this;
            }

            Vector2& operator /=(T divisor)
            {
                for (int i = 0; i < 2; ++i)
                    _values[i] /= divisor;

                return *this;
            }

            const Vector2 operator+(const Vector2& other) const
            {
                return Vector2(*this) += other;
            }

            const Vector2 operator-(const Vector2& other) const
            {
                return Vector2(*this) -= other;
            }

            const Vector2 operator*(T multiplier) const
            {
                return Vector2(*this) *= multiplier;
            }

            const Vector2 operator/(T divisor) const
            {
                return Vector2(*this) /= divisor;
            }

        private:
            T _values[2];
    };

    template<typename T>
    class Vector3
    {
        public:
            constexpr Vector3() : _values{0, 0, 0} {}
            constexpr Vector3(T x) : _values{x, 0, 0} {}
            constexpr Vector3(T x, T y) : _values{x, y, 0} {}
            constexpr Vector3(T x, T y, T z) : _values{x, y, z} {}

            Vector3(const Vector2<T>& other)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 2);
                _values[2] = T(0);
            }

            Vector3(const Vector2<T>& other, T z)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 2);
                _values[2] = z;
            }

            Vector3(const Vector3& other)
            {
                memcpy(_values, other._values, sizeof(T) * 3);
            }

            Vector3(const Vector4<T>& other)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 3);
            }

            Vector3& operator=(const Vector3& other)
            {
                memcpy(_values, other._values, sizeof(_values));
                return *this;
            }

            Vector3& operator+=(const Vector3& other)
            {
                for (int i = 0; i < 3; ++i) _values[i] += other._values[i];
                return *this;
            }

            Vector3& operator-=(const Vector3& other)
            {
                for (int i = 0; i < 3; ++i) _values[i] -= other._values[i];
                return *this;
            }

            Vector3& operator*=(T multiplier)
            {
                for (int i = 0; i < 3; ++i) _values[i] *= multiplier;
                return *this;
            }

            Vector3& operator/=(T divisor)
            {
                for (int i = 0; i < 3; ++i) _values[i] /= divisor;
                return *this;
            }

            const Vector3 operator+(const Vector3& other) const
            {
                return Vector3(*this) += other;
            }

            const Vector3 operator-(const Vector3& other) const
            {
                return Vector3(*this) -= other;
            }

            const Vector3 operator*(T multiplier) const
            {
                return Vector3(*this) *= multiplier;
            }

            const Vector3 operator/(T divisor) const
            {
                return Vector3(*this) /= divisor;
            }

            constexpr const Vector3 operator-() const
            {
                return Vector3(-_values[0], -_values[1], -_values[2]);
            }

            T* Data() { return _values; }
            constexpr const T* ReadOnlyData() const { return _values; }

            constexpr T X() const { return _values[0]; }
            constexpr T Y() const { return _values[1]; }
            constexpr T Z() const { return _values[2]; }

            void X(T value) { _values[0] = value; }
            void Y(T value) { _values[1] = value; }
            void Z(T value) { _values[2] = value; }

            T LengthSquared() const
            {
                return _values[0] * _values[0]
                    + _values[1] * _values[1]
                    + _values[2] * _values[2];
            }

            const Vector3 Normalized() const
            {
                T length = sqrt(LengthSquared());

                return Vector3(
                    _values[0] / length,
                    _values[1] / length,
                    _values[2] / length);
            }

        private:
            T _values[3];
    };

    template<typename T>
    class Vector4
    {
        public:
            constexpr Vector4() : _values{0, 0, 0, 0} {}
            constexpr Vector4(T x) : _values{x, 0, 0, 0} {}
            constexpr Vector4(T x, T y) : _values{x, y, 0, 0} {}
            constexpr Vector4(T x, T y, T z) : _values{x, y, z, 0} {}
            constexpr Vector4(T x, T y, T z, T w) : _values{x, y, z, w} {}

            Vector4(const Vector2<T>& other)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 2);
                _values[2] = T(0);
                _values[3] = T(0);
            }

            Vector4(const Vector2<T>& other, T z)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 2);
                _values[2] = z;
                _values[3] = T(0);
            }

            Vector4(const Vector2<T>& other, T z, T w)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 2);
                _values[2] = z;
                _values[3] = w;
            }

            Vector4(const Vector3<T>& other)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 3);
                _values[3] = T(0);
            }

            Vector4(const Vector3<T>& other, T w)
            {
                memcpy(_values, other.ReadOnlyData(), sizeof(T) * 3);
                _values[3] = w;
            }

            Vector4(const Vector4& other)
            {
                memcpy(_values, other._values, sizeof(T) * 4);
            }

            T* Data() { return _values; }
            constexpr const T* ReadOnlyData() const { return _values; }

            constexpr T X() const { return _values[0]; }
            constexpr T Y() const { return _values[1]; }
            constexpr T Z() const { return _values[2]; }
            constexpr T W() const { return _values[3]; }

            void X(T value) { _values[0] = value; }
            void Y(T value) { _values[1] = value; }
            void Z(T value) { _values[2] = value; }
            void W(T value) { _values[3] = value; }

        private:
            T _values[4];
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Vector2<T>& v)
    {
        return stream << v.X() << ", " << v.Y();
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Vector3<T>& v)
    {
        return stream << v.X() << ", " << v.Y() << ", " << v.Z();
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Vector4<T>& v)
    {
        return stream << v.X() << ", " << v.Y() << ", " << v.Z() << ", "
            << v.W();
    }

    typedef Vector2<float> Vector2F;
    typedef Vector3<float> Vector3F;
    typedef Vector4<float> Vector4F;

    typedef Vector2<double> Vector2D;
    typedef Vector3<double> Vector3D;
    typedef Vector4<double> Vector4D;
}

#endif
