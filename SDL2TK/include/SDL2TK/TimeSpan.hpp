#ifndef TIMESPAN_HPP
#define TIMESPAN_HPP

#include <cstdint>

namespace SDL2TK
{
    const int64_t NanosecondsPerTick = 100;
    const int64_t TicksPerMicrosecond = 10;
    const int64_t TicksPerMillisecond = TicksPerMicrosecond * 1000;
    const int64_t TicksPerSecond = TicksPerMillisecond * 1000;
    const int64_t TicksPerMinute = TicksPerSecond * 60;
    const int64_t TicksPerHour = TicksPerMinute * 60;
    const int64_t TicksPerDay = TicksPerHour * 24;
    const int64_t TicksPerWeek = TicksPerDay * 7;

    class TimeSpan
    {
        public:
            constexpr TimeSpan() : _ticks(0) {}
            constexpr explicit TimeSpan(int64_t ticks) : _ticks(ticks) {}
            constexpr TimeSpan(const TimeSpan& other) : _ticks(other._ticks) {}

            constexpr int64_t Ticks() const { return _ticks; }

            TimeSpan& operator=(const TimeSpan& other);
            TimeSpan& operator+=(const TimeSpan& other);
            TimeSpan& operator-=(const TimeSpan& other);
            TimeSpan& operator*=(int64_t multiplier);
            TimeSpan& operator/=(int64_t divisor);

            constexpr const TimeSpan operator+(const TimeSpan& other) const
            {
                return TimeSpan(_ticks + other._ticks);
            }

            constexpr const TimeSpan operator-(const TimeSpan& other) const
            {
                return TimeSpan(_ticks - other._ticks);
            }

            constexpr const TimeSpan operator-() const
            {
                return TimeSpan(-_ticks);
            }

            constexpr const TimeSpan operator*(int64_t multiplier) const
            {
                return TimeSpan(_ticks * multiplier);
            }

            constexpr const TimeSpan operator/(int64_t divisor) const
            {
                return TimeSpan(_ticks / divisor);
            }

            constexpr bool operator==(const TimeSpan& other) const
            {
                return _ticks == other._ticks;
            }

            constexpr bool operator!=(const TimeSpan& other) const
            {
                return _ticks != other._ticks;
            }

            constexpr bool operator<(const TimeSpan& other) const
            {
                return _ticks < other._ticks;
            }

            constexpr bool operator<=(const TimeSpan& other) const
            {
                return _ticks <= other._ticks;
            }

            constexpr bool operator>(const TimeSpan& other) const
            {
                return _ticks > other._ticks;
            }

            constexpr bool operator>=(const TimeSpan& other) const
            {
                return _ticks >= other._ticks;
            }

            constexpr int64_t ToNanoseconds() const
            {
                return _ticks * NanosecondsPerTick;
            }

            constexpr int64_t ToMicroseconds() const
            {
                return _ticks / TicksPerMicrosecond;
            }

            constexpr int64_t ToMilliseconds() const
            {
                return _ticks / TicksPerMillisecond;
            }

            constexpr int64_t ToSeconds() const
            {
                return _ticks / TicksPerSecond;
            }

            constexpr int64_t ToMinutes() const
            {
                return _ticks / TicksPerMinute;
            }

            constexpr int64_t ToHours() const
            {
                return _ticks / TicksPerHour;
            }

            constexpr int64_t ToDays() const
            {
                return _ticks / TicksPerDay;
            }

            constexpr int64_t ToWeeks() const
            {
                return _ticks / TicksPerWeek;
            }

            static constexpr
            const TimeSpan FromNanoseconds(int64_t nanoseconds)
            {
                return TimeSpan(nanoseconds / NanosecondsPerTick);
            }

            static constexpr
            const TimeSpan FromMicroseconds(int64_t microseconds)
            {
                return TimeSpan(microseconds * TicksPerMicrosecond);
            }

            static constexpr
            const TimeSpan FromMilliseconds(int64_t milliseconds)
            {
                return TimeSpan(milliseconds * TicksPerMillisecond);
            }

            static constexpr
            const TimeSpan FromSeconds(int64_t seconds)
            {
                return TimeSpan(seconds * TicksPerSecond);
            }

            static constexpr
            const TimeSpan FromMinutes(int64_t minutes)
            {
                return TimeSpan(minutes * TicksPerMinute);
            }

            static constexpr
            const TimeSpan FromHours(int64_t hours)
            {
                return TimeSpan(hours * TicksPerHour);
            }

            static constexpr
            const TimeSpan FromDays(int64_t days)
            {
                return TimeSpan(days * TicksPerDay);
            }

            static constexpr
            const TimeSpan FromWeeks(int64_t weeks)
            {
                return TimeSpan(weeks * TicksPerWeek);
            }

            static const TimeSpan FromSDL();

        private:
            int64_t _ticks;
    };
}

#endif
