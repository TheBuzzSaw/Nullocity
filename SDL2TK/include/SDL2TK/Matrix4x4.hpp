#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include "Rotation.hpp"
#include "Vector.hpp"

#include <cmath>
#include <cstring>
#include <iomanip>

#ifdef near
#undef near
#endif

#ifdef far
#undef far
#endif

namespace SDL2TK
{
    template<typename T>
    class Matrix4x4
    {
        public:
            Matrix4x4()
            {
                memcpy(_values, _identity, sizeof(T) * 16);
            }

            Matrix4x4(const T* values)
            {
                memcpy(_values, values, sizeof(T) * 16);
            }

            Matrix4x4(const Matrix4x4<T>& other)
            {
                memcpy(_values, other._values, sizeof(T) * 16);
            }

            Matrix4x4(const Matrix4x4<T>& left, const Matrix4x4<T>& right)
            {
                Multiply(left, right);
            }

            Matrix4x4<T>& LoadIdentity()
            {
                memcpy(_values, _identity, sizeof(T) * 16);
                return *this;
            }

            Matrix4x4<T>& Rotate(const Rotation<T> rotation, T x, T y, T z)
            {
                T c = cos(rotation.ToRadians());
                T ci = T(1) - c;
                T s = sin(rotation.ToRadians());

                Matrix4x4<T> matrix;

                matrix[0] = x * x * ci + c;
                matrix[4] = x * y * ci - (z * s);
                matrix[8] = x * z * ci + (y * s);
                matrix[1] = y * x * ci + (z * s);
                matrix[5] = y * y * ci + c;
                matrix[9] = y * z * ci - (x * s);
                matrix[2] = x * z * ci - (y * s);
                matrix[6] = y * z * ci + (x * s);
                matrix[10] = z * z * ci + c;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& RotateX(const Rotation<T> rotation)
            {
                T c = cos(rotation.ToRadians());
                T s = sin(rotation.ToRadians());

                Matrix4x4<T> matrix;

                matrix[5] = c;
                matrix[9] = -s;
                matrix[6] = s;
                matrix[10] = c;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& RotateY(const Rotation<T> rotation)
            {
                T c = cos(rotation.ToRadians());
                T s = sin(rotation.ToRadians());

                Matrix4x4<T> matrix;

                matrix[0] = c;
                matrix[8] = s;
                matrix[2] = -s;
                matrix[10] = c;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& RotateZ(const Rotation<T> rotation)
            {
                T c = cos(rotation.ToRadians());
                T s = sin(rotation.ToRadians());

                Matrix4x4<T> matrix;

                matrix[0] = c;
                matrix[4] = -s;
                matrix[1] = s;
                matrix[5] = c;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& Scale(T scale)
            {
                Matrix4x4<T> matrix;

                matrix[0] = scale;
                matrix[5] = scale;
                matrix[10] = scale;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& ScaleX(T scale)
            {
                Matrix4x4<T> matrix;

                matrix[0] = scale;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& ScaleY(T scale)
            {
                Matrix4x4<T> matrix;

                matrix[5] = scale;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& ScaleZ(T scale)
            {
                Matrix4x4<T> matrix;

                matrix[10] = scale;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& Scale(T x, T y, T z)
            {
                Matrix4x4<T> matrix;

                matrix[0] = x;
                matrix[5] = y;
                matrix[10] = z;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& Translate(T x, T y, T z)
            {
                Matrix4x4<T> matrix;

                matrix[12] = x;
                matrix[13] = y;
                matrix[14] = z;

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& Translate(const Vector3<T>& translation)
            {
                Matrix4x4<T> matrix;

                matrix[12] = translation.X();
                matrix[13] = translation.Y();
                matrix[14] = translation.Z();

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            /// projection
            Matrix4x4<T>& Frustum(T left, T right, T bottom, T top, T near,
                T far)
            {
                Matrix4x4<T> matrix;

                matrix[0] = (T(2) * near) / (right - left);
                matrix[8] = (right + left) / (right - left);
                matrix[5] = (T(2) * near) / (top - bottom);
                matrix[9] = (top + bottom) / (top - bottom);
                matrix[10] = (far + near) / (near - far);
                matrix[14] = (T(2) * far * near) / (near - far);
                matrix[11] = T(-1);
                matrix[15] = T(0);

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& Perspective(const Rotation<T> fieldOfView, T ratio,
                T near, T far, bool autoAdjust = false)
            {
                /// adaptation of gluPerspective
                /// http://www.opengl.org/sdk/docs/man/xhtml/gluPerspective.xml
                T r = fieldOfView.ToRadians();
                if (autoAdjust && ratio < T(1))
                    r /= ratio;

                T f = T(1) / tan(r / T(2));

                Matrix4x4<T> matrix;

                matrix[0] = f / ratio;
                matrix[5] = f;
                matrix[10] = (far + near) / (near - far);
                matrix[14] = (T(2) * far * near) / (near - far);
                matrix[11] = T(-1);
                matrix[15] = T(0);

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& Orthographic(T left, T right, T bottom, T top, T near, T far)
            {
                Matrix4x4<T> matrix;

                matrix[0] = T(2) / (right - left);
                matrix[12] = (right + left) / (right - left);
                matrix[5] = T(2) / (top - bottom);
                matrix[13] = (top + bottom) / (top - bottom);
                matrix[10] = T(2) / (near - far);
                matrix[14] = (far + near) / (far - near);

                return Multiply(Matrix4x4<T>(_values), matrix);
            }

            Matrix4x4<T>& Orthographic(T range, T ratio)
            {
                if (ratio < T(1))
                {
                    Orthographic(-range, range, -range / ratio, range / ratio,
                        range, -range);
                }
                else
                {
                    Orthographic(-range * ratio, range * ratio, -range, range,
                        range, -range);
                }

                return *this;
            }

            /// matrix operators
            Matrix4x4<T>& operator=(const Matrix4x4<T>& other)
            {
                if (this != &other)
                    memcpy(_values, other._values, sizeof(T) * 16);

                return *this;
            }

            Matrix4x4<T>& Multiply(const Matrix4x4<T>& left,
                const Matrix4x4<T>& right)
            {
                /// The actual math has been completely unrolled (out of for
                /// loops) for performance improvements.

                _values[0] = (left[0] * right[0])
                    + (left[4] * right[1])
                    + (left[8] * right[2])
                    + (left[12] * right[3]);

                _values[4] = (left[0] * right[4])
                    + (left[4] * right[5])
                    + (left[8] * right[6])
                    + (left[12] * right[7]);

                _values[8] = (left[0] * right[8])
                    + (left[4] * right[9])
                    + (left[8] * right[10])
                    + (left[12] * right[11]);

                _values[12] = (left[0] * right[12])
                    + (left[4] * right[13])
                    + (left[8] * right[14])
                    + (left[12] * right[15]);

                _values[1] = (left[1] * right[0])
                    + (left[5] * right[1])
                    + (left[9] * right[2])
                    + (left[13] * right[3]);

                _values[5] = (left[1] * right[4])
                    + (left[5] * right[5])
                    + (left[9] * right[6])
                    + (left[13] * right[7]);

                _values[9] = (left[1] * right[8])
                    + (left[5] * right[9])
                    + (left[9] * right[10])
                    + (left[13] * right[11]);

                _values[13] = (left[1] * right[12])
                    + (left[5] * right[13])
                    + (left[9] * right[14])
                    + (left[13] * right[15]);

                _values[2] = (left[2] * right[0])
                    + (left[6] * right[1])
                    + (left[10] * right[2])
                    + (left[14] * right[3]);

                _values[6] = (left[2] * right[4])
                    + (left[6] * right[5])
                    + (left[10] * right[6])
                    + (left[14] * right[7]);

                _values[10] = (left[2] * right[8])
                    + (left[6] * right[9])
                    + (left[10] * right[10])
                    + (left[14] * right[11]);

                _values[14] = (left[2] * right[12])
                    + (left[6] * right[13])
                    + (left[10] * right[14])
                    + (left[14] * right[15]);

                _values[3] = (left[3] * right[0])
                    + (left[7] * right[1])
                    + (left[11] * right[2])
                    + (left[15] * right[3]);

                _values[7] = (left[3] * right[4])
                    + (left[7] * right[5])
                    + (left[11] * right[6])
                    + (left[15] * right[7]);

                _values[11] = (left[3] * right[8])
                    + (left[7] * right[9])
                    + (left[11] * right[10])
                    + (left[15] * right[11]);

                _values[15] = (left[3] * right[12])
                    + (left[7] * right[13])
                    + (left[11] * right[14])
                    + (left[15] * right[15]);

                return *this;
            }

            void Inverse()
            {
                const Matrix4x4<T> matrix(*this);
                matrix.copyInverseTo(*this);
            }

            void CopyInverseTo(Matrix4x4<T>& other) const
            {
                T wtmp[4][8];
                T m0;
                T m1;
                T m2;
                T m3;
                T s;
                T* r0;
                T* r1;
                T* r2;
                T* r3;

                r0 = wtmp[0];
                r1 = wtmp[1];
                r2 = wtmp[2];
                r3 = wtmp[3];

                r0[0] = at(0, 0);
                r0[1] = at(0, 1);
                r0[2] = at(0, 2);
                r0[3] = at(0, 3);
                r0[4] = 1.0;
                r0[5] = r0[6] = r0[7] = 0.0;
                r1[0] = at(1, 0);
                r1[1] = at(1, 1);
                r1[2] = at(1, 2);
                r1[3] = at(1, 3);
                r1[5] = 1.0;
                r1[4] = r1[6] = r1[7] = 0.0;
                r2[0] = at(2, 0);
                r2[1] = at(2, 1);
                r2[2] = at(2, 2);
                r2[3] = at(2, 3);
                r2[6] = 1.0;
                r2[4] = r2[5] = r2[7] = 0.0;
                r3[0] = at(3, 0);
                r3[1] = at(3, 1);
                r3[2] = at(3, 2);
                r3[3] = at(3, 3);
                r3[7] = 1.0;
                r3[4] = r3[5] = r3[6] = 0.0;

                if (fabs(r3[0]) > fabs(r2[0])) std::swap(r3, r2);
                if (fabs(r2[0]) > fabs(r1[0])) std::swap(r2, r1);
                if (fabs(r1[0]) > fabs(r0[0])) std::swap(r1, r0);
                if (0.0 == r0[0]) return;

                m1 = r1[0] / r0[0];
                m2 = r2[0] / r0[0];
                m3 = r3[0] / r0[0];
                s = r0[1];
                r1[1] -= m1 * s;
                r2[1] -= m2 * s;
                r3[1] -= m3 * s;
                s = r0[2];
                r1[2] -= m1 * s;
                r2[2] -= m2 * s;
                r3[2] -= m3 * s;
                s = r0[3];
                r1[3] -= m1 * s;
                r2[3] -= m2 * s;
                r3[3] -= m3 * s;
                s = r0[4];

                if (s != 0.0)
                {
                    r1[4] -= m1 * s;
                    r2[4] -= m2 * s;
                    r3[4] -= m3 * s;
                }
                s = r0[5];
                if (s != 0.0)
                {
                    r1[5] -= m1 * s;
                    r2[5] -= m2 * s;
                    r3[5] -= m3 * s;
                }
                s = r0[6];
                if (s != 0.0)
                {
                    r1[6] -= m1 * s;
                    r2[6] -= m2 * s;
                    r3[6] -= m3 * s;
                }
                s = r0[7];
                if (s != 0.0)
                {
                    r1[7] -= m1 * s;
                    r2[7] -= m2 * s;
                    r3[7] -= m3 * s;
                }

                if (fabs(r3[1]) > fabs(r2[1])) std::swap(r3, r2);
                if (fabs(r2[1]) > fabs(r1[1])) std::swap(r2, r1);
                if (0.0 == r1[1]) return;

                m2 = r2[1] / r1[1];
                m3 = r3[1] / r1[1];
                r2[2] -= m2 * r1[2];
                r3[2] -= m3 * r1[2];
                r2[3] -= m2 * r1[3];
                r3[3] -= m3 * r1[3];
                s = r1[4];
                if (0.0 != s)
                {
                    r2[4] -= m2 * s;
                    r3[4] -= m3 * s;
                }
                s = r1[5];
                if (0.0 != s)
                {
                    r2[5] -= m2 * s;
                    r3[5] -= m3 * s;
                }
                s = r1[6];
                if (0.0 != s)
                {
                    r2[6] -= m2 * s;
                    r3[6] -= m3 * s;
                }
                s = r1[7];
                if (0.0 != s)
                {
                    r2[7] -= m2 * s;
                    r3[7] -= m3 * s;
                }

                if (fabs(r3[2]) > fabs(r2[2])) std::swap(r3, r2);
                if (0.0 == r2[2]) return;

                m3 = r3[2] / r2[2];
                r3[3] -= m3 * r2[3];
                r3[4] -= m3 * r2[4];
                r3[5] -= m3 * r2[5];
                r3[6] -= m3 * r2[6];
                r3[7] -= m3 * r2[7];

                if (0.0 == r3[3]) return;

                s = 1.0 / r3[3];
                r3[4] *= s;
                r3[5] *= s;
                r3[6] *= s;
                r3[7] *= s;

                m2 = r2[3];
                s = 1.0 / r2[2];
                r2[4] = s * (r2[4] - r3[4] * m2);
                r2[5] = s * (r2[5] - r3[5] * m2);
                r2[6] = s * (r2[6] - r3[6] * m2);
                r2[7] = s * (r2[7] - r3[7] * m2);
                m1 = r1[3];
                r1[4] -= r3[4] * m1;
                r1[5] -= r3[5] * m1;
                r1[6] -= r3[6] * m1;
                r1[7] -= r3[7] * m1;
                m0 = r0[3];
                r0[4] -= r3[4] * m0;
                r0[5] -= r3[5] * m0;
                r0[6] -= r3[6] * m0;
                r0[7] -= r3[7] * m0;

                m1 = r1[2];
                s = 1.0 / r1[1];
                r1[4] = s * (r1[4] - r2[4] * m1);
                r1[5] = s * (r1[5] - r2[5] * m1);
                r1[6] = s * (r1[6] - r2[6] * m1);
                r1[7] = s * (r1[7] - r2[7] * m1);
                m0 = r0[2];
                r0[4] -= r2[4] * m0;
                r0[5] -= r2[5] * m0;
                r0[6] -= r2[6] * m0;
                r0[7] -= r2[7] * m0;

                m0 = r0[1];
                s = 1.0 / r0[0];
                r0[4] = s * (r0[4] - r1[4] * m0);
                r0[5] = s * (r0[5] - r1[5] * m0);
                r0[6] = s * (r0[6] - r1[6] * m0);
                r0[7] = s * (r0[7] - r1[7] * m0);

                other(0, 0) = r0[4];
                other(0, 1) = r0[5];
                other(0, 2) = r0[6];
                other(0, 3) = r0[7];
                other(1, 0) = r1[4];
                other(1, 1) = r1[5];
                other(1, 2) = r1[6];
                other(1, 3) = r1[7];
                other(2, 0) = r2[4];
                other(2, 1) = r2[5];
                other(2, 2) = r2[6];
                other(2, 3) = r2[7];
                other(3, 0) = r3[4];
                other(3, 1) = r3[5];
                other(3, 2) = r3[6];
                other(3, 3) = r3[7];
            }

            const Matrix4x4<T> Inversed() const
            {
                Matrix4x4<T> result;
                copyInverseTo(result);
                return result;
            }

            void Multiply(const Vector4<T>& position, Vector4<T>& result) const
            {
                result.X(at(0, 0) * position.X() + at(0, 1) * position.Y()
                    + at(0, 2) * position.Z() + at(0, 3) * position.W());

                result.Y(at(1, 0) * position.X() + at(1, 1) * position.Y()
                    + at(1, 2) * position.Z() + at(1, 3) * position.W());

                result.Z(at(2, 0) * position.X() + at(2, 1) * position.Y()
                    + at(2, 2) * position.Z() + at(2, 3) * position.W());

                result.W(at(3, 0) * position.X() + at(3, 1) * position.Y()
                    + at(3, 2) * position.Z() + at(3, 3) * position.W());
            }

            void Transform(const Vector3<T>& position, Vector3<T>& result) const
            {
                Vector4<T> rawPosition(position, T(1));
                Vector4<T> rawResult;

                Multiply(rawPosition, rawResult);

                result.X(rawResult.X() / rawResult.W());
                result.Y(rawResult.Y() / rawResult.W());
                result.Z(rawResult.Z() / rawResult.W());
            }

            Vector3<T> Transform(const Vector3<T>& position)
            {
                Vector3<T> result;
                Transform(position, result);
                return result;
            }

            /// Allow this object to behave as a simple array.
            inline operator T*() { return _values; }
            inline operator const T*() const { return _values; }

            /// Allow simply access by row and column.
            T& operator()(size_t row, size_t column)
            {
                return _values[column * 4 + row];
            }

            T operator()(size_t row, size_t column) const
            {
                return _values[column * 4 + row];
            }

            /// simple comparison operators
            bool operator==(const Matrix4x4<T>& other) const
            {
                return !memcmp(_values, other._values, 16 * sizeof(T));
            }

            bool operator!=(const Matrix4x4<T>& other) const
            {
                return memcmp(_values, other._values, 16 * sizeof(T));
            }

            Matrix4x4<T>& operator*=(const Matrix4x4<T>& other)
            {
                return Multiply(Matrix4x4<T>(_values), other);
            }

            const Matrix4x4<T> operator*(const Matrix4x4<T>& other) const
            {
                return Matrix4x4<T>(Matrix4x4<T>(_values), other);
            }

        private:
            inline T& at(size_t row, size_t column)
            {
                return _values[column * 4 + row];
            }

            inline T at(size_t row, size_t column) const
            {
                return _values[column * 4 + row];
            }

            T _values[16]; // stored in column-major order

            static const T _identity[16];
    };

    /// The identity matrix is pre-built so that it can just be copied to newly
    /// born matrices. This makes it faster than manually filling the identity
    /// matrix and/or having to iterate through a loop.
    template<typename T>
    const T Matrix4x4<T>::_identity[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };

    /// For easy display/debugging and/or serialization, the extraction operator
    /// has been overloaded to allow matrices in output streams.
    template<typename T>
    std::ostream& operator<<(std::ostream& inStream,
        const Matrix4x4<T>& other)
    {
        inStream << std::setprecision(2);
        for (size_t i = 0; i < 4; ++i)
        {
            if (i) inStream << '\n';
            for (size_t j = 0; j < 4; ++j)
            {
                inStream << std::setw(6) << other(i, j);
            }
        }

        return inStream;
    }

    typedef Matrix4x4<float> Matrix4x4F;
    typedef Matrix4x4<double> Matrix4x4D;
}

#endif
