#ifndef ROTATION_HPP
#define ROTATION_HPP

namespace SDL2TK
{
    template<typename T>
    class Rotation
    {
        public:
            static constexpr const T Pi = 3.1415926535897932384626433832795;
            static constexpr const T Tau = Pi * T(2);
            static constexpr const T DegreesPerRadian = T(180) / Pi;
            static constexpr const T RadiansPerDegree = Pi / T(180);

            constexpr Rotation() : _radians(0) {}
            constexpr Rotation(const Rotation& other)
                : _radians(other._radians) {}

            Rotation& operator=(const Rotation& other)
            {
                _radians = other._radians;
                return *this;
            }

            Rotation& operator+=(const Rotation& other)
            {
                _radians = Cycle(_radians + other._radians);
                return *this;
            }

            Rotation& operator-=(const Rotation& other)
            {
                _radians = Cycle(_radians - other._radians);
                return *this;
            }

            constexpr T ToRadians() const
            {
                return _radians;
            }

            constexpr T ToDegrees() const
            {
                return _radians * DegreesPerRadian;
            }

            constexpr const Rotation operator-() const
            {
                return Rotation(Cycle(-_radians));
            }

            const Rotation operator+(const Rotation other) const
            {
                return Rotation(Cycle(_radians + other._radians));
            }

            const Rotation operator-(const Rotation other) const
            {
                return Rotation(Cycle(_radians - other._radians));
            }

            static constexpr const Rotation FromRadians(T radians)
            {
                return Rotation(radians);
            }

            static constexpr const Rotation FromDegrees(T degrees)
            {
                return Rotation(degrees * RadiansPerDegree);
            }

        private:
            constexpr Rotation(T radians) : _radians(radians) {}

            T _radians;

            static T Cycle(T radians)
            {
                T result = radians;

                if (result >= Pi)
                    result -= Tau;
                else if (result < -Pi)
                    result += Tau;

                return result;
            }
    };

    template<typename T> constexpr const T Rotation<T>::Pi;
    template<typename T> constexpr const T Rotation<T>::Tau;
    template<typename T> constexpr const T Rotation<T>::DegreesPerRadian;
    template<typename T> constexpr const T Rotation<T>::RadiansPerDegree;

    typedef Rotation<float> RotationF;
    typedef Rotation<double> RotationD;
}

#endif
