/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "PackedDateTime.hpp"
#include <algorithm>
#include <cassert>
#include <climits>

namespace JEBBase {

const uint64_t EPOCH_YEAR = 1200; /* This must be a leap century, Gregorian calendar was introduced in the 1580-ies. */
const uint64_t MIN_YEAR = 1582;
const uint64_t SECS_PER_DAY = 24ULL * 60ULL * 60ULL;
const uint64_t USECS_PER_SEC = 1000000ULL;
const uint64_t USECS_PER_MIN = 60 * USECS_PER_SEC;
const uint64_t USECS_PER_HOUR = 60 * USECS_PER_MIN;
const uint64_t USECS_PER_DAY = SECS_PER_DAY * USECS_PER_SEC;

/* Internally, March is the first month. */
// static const int gDaysPerMonth[12] = {31, 30, 31, 30, 31, 31,
//                                       30, 31, 30, 31, 31, 28};

static const int gAccumulatedDays[12] = {  0,  31,  61,  92, 122, 153,
                                         184, 214, 245, 275, 306, 337};

static const YearMonthDay DEFAULT_DATE = YearMonthDay(MIN_YEAR, 1, 1);

#ifdef _MSC_VER
    #pragma warning(disable: 4996)
    static void localdate(int* year, int* dayOfYear, int* secOfDay, int* tzSeconds)
    {
        time_t t = time(NULL);
        struct tm* locTime = localtime(&t);
        *year = locTime->tm_year + 1900;
        *dayOfYear = locTime->tm_yday + 1;
        *secOfDay = (locTime->tm_hour * 24 + locTime->tm_min) * 60 + locTime->tm_sec;
        *tzSeconds = _timezone;
    }

    static uint64_t timezoneSecs()
    {
        return _timezone;
    }
#else
    static uint64_t gTimezoneSeconds = ULLONG_MAX;

    void localdate(int* year, int* dayOfYear, int* secOfDay, int* tzSeconds)
    {
        time_t t = time(NULL);
        struct tm* locTime = localtime(&t);
        *year = locTime->tm_year + 1900;
        *dayOfYear = locTime->tm_yday + 1;
        *secOfDay = (locTime->tm_hour * 60 + locTime->tm_min) * 60 + locTime->tm_sec;
        *tzSeconds = locTime->tm_gmtoff;
    }

    static uint64_t timezoneSecs()
    {
        if (gTimezoneSeconds == ULLONG_MAX)
        {
            int year, dayOfYear, secOfDay, tzSeconds;
            localdate(&year, &dayOfYear, &secOfDay, &tzSeconds);
            gTimezoneSeconds = tzSeconds;
        }
        return gTimezoneSeconds;
    }
#endif

static int isLeapYear(int year)
{
    return (year % 16 == 0) || (year % 4 == 0 && year % 25 != 0);
}

static int daysSinceEpochY(int year)
{
    assert(MIN_YEAR <= year);
    int years = year - EPOCH_YEAR;
    return years * 365 + (years + 3) / 4 - (years + 99) / 100 + (years + 399) / 400;
}

static int daysSinceEpochYD(YearDay yd)
{
    assert(1 <= yd.day && yd.day <= (isLeapYear(yd.year) ? 366 : 365));
    int daysInJanFeb = 31 + (isLeapYear(yd.year) ? 29 : 28);
    if (yd.day > daysInJanFeb)
    {
        yd.day -= daysInJanFeb + 1;
        ++yd.year;
    }
    else
    {
        yd.day += gAccumulatedDays[10] - 1;
    }

    return daysSinceEpochY(yd.year) + yd.day;
}

static int daysSinceEpochYMD(YearMonthDay date)
{
    assert(1 <= date.month && date.month <= 12);
    assert(1 <= date.day && date.day <= 31);

    /* Make March the first month of the year. */
    if (date.month > 2)
    {
        date.month -= 3;
        ++date.year;
    }
    else
    {
        date.month += 9;
    }
    return daysSinceEpochY(date.year)
         + gAccumulatedDays[date.month]
         + date.day - 1;
}

static void toInternalYD(int* year, int* dayOfYear, uint64_t daysSinceEpoch)
{
    const int days400 = 400 * 365 + 4 * 24 + 1; /* Number of days in 4 centuries. */
    const int days100 = 100 * 365 + 24; /* Number of days in a century not divisible by 400. */
    const int days4 = 4 * 365 + 1; /* Number of days in 4 years. */

    *year = EPOCH_YEAR + 400 * (daysSinceEpoch / days400);
    daysSinceEpoch %= days400;

    if (daysSinceEpoch > days100 + 1)
    {
        daysSinceEpoch -= days100 + 1;
        *year += 100 * (1 + daysSinceEpoch / days100);
        daysSinceEpoch %= days100;
        if (daysSinceEpoch < days4 - 1)
        {
            *year += daysSinceEpoch / 365;
            daysSinceEpoch %= 365;
        }
        else
        {
            *year += 4;
            daysSinceEpoch -= days4 - 1;
        }
    }

    *year += 4 * (daysSinceEpoch / days4);
    daysSinceEpoch %= days4;

    if (daysSinceEpoch > 365)
    {
        *year += (daysSinceEpoch - 1) / 365;
        *dayOfYear = (daysSinceEpoch - 1) % 365;
    }
    else
    {
        *dayOfYear = daysSinceEpoch;
    }
}

static YearMonthDay toYMD(uint64_t daysSinceEpoch)
{
    int year = 0, dayOfYear = 0;
    toInternalYD(&year, &dayOfYear, daysSinceEpoch);
    auto it = std::upper_bound(std::begin(gAccumulatedDays),
                               std::end(gAccumulatedDays),
                               dayOfYear);
    int month = std::distance(std::begin(gAccumulatedDays), it);
    int dayOfMonth = dayOfYear - gAccumulatedDays[month - 1] + 1;

    if (month > 10)
    {
        month -= 10;
    }
    else
    {
        month += 2;
        --year;
    }
    return YearMonthDay(year, month, dayOfMonth);
}

static HourMinuteSecond toHMS(int64_t useconds)
{
    auto hour = useconds / (60 * 60 * USECS_PER_SEC);
    useconds %= (60 * 60 * USECS_PER_SEC);
    auto minute = useconds / (60 * USECS_PER_SEC);
    useconds %= (60 * USECS_PER_SEC);
    auto second = useconds / USECS_PER_SEC;
    auto usecond = useconds % USECS_PER_SEC;
    return HourMinuteSecond(hour, minute, second, usecond);
}

static uint64_t usecsSinceMidnight(HourMinuteSecond time)
{
    assert(0 <= time.hour && time.hour < 24);
    assert(0 <= time.minute && time.minute < 60);
    assert(0 <= time.second && time.second < 60);
    assert(0 <= time.usecond && time.usecond < USECS_PER_SEC);
    return time.hour * USECS_PER_HOUR + time.minute * USECS_PER_MIN +
           time.second * USECS_PER_SEC + time.usecond;
}

static uint64_t packDaysUseconds(int64_t days, int64_t usecs)
{
    return days * USECS_PER_DAY + usecs;
}

static std::pair<uint64_t, uint64_t> unpackDaysUseconds(PackedDateTime dateTime)
{
    return std::make_pair(dateTime / USECS_PER_DAY, dateTime % USECS_PER_DAY);
}

// static void unpackTimezone(int* hour, int* minute, int* second, int timezone)
// {
//     *hour = timezone / (60 * 60);
//     timezone %= 60 * 60;
//     if (timezone < 0)
//     {
//         *hour -= 1;
//         timezone += 60 * 60;
//     }
//     *minute = timezone / 60;
//     *second = timezone % 60;
// }

static int toWeek(int dayOfYear, int dayOfWeek, int firstDayOfWeek)
{
    int logicalDayOfWeek = dayOfWeek - firstDayOfWeek;
    if (logicalDayOfWeek < 0)
        logicalDayOfWeek += 6;
    return (dayOfYear + 10 - logicalDayOfWeek) / 7;
}

#pragma mark Pack

PackedDateTime pack(const YearMonthDay& date, const HourMinuteSecond& time)
{
    return pack(date, time, timezoneSecs());
}

PackedDateTime pack(const YearMonthDay& date, const HourMinuteSecond& time,
                    int timezone)
{
    int64_t days = daysSinceEpochYMD(date);
    int64_t usecs = usecsSinceMidnight(time);
    return packDaysUseconds(days, usecs - timezone * USECS_PER_SEC);
}

PackedDateTime pack(const YearMonthDay& date)
{
    return pack(date, timezoneSecs());
}

PackedDateTime pack(const YearMonthDay& date, int timezone)
{
    return pack(date, HourMinuteSecond(12, 0, 0), timezone);
}

PackedDateTime pack(const HourMinuteSecond& time)
{
    return pack(time, timezoneSecs());
}

PackedDateTime pack(const HourMinuteSecond& time, int timezone)
{
    return pack(DEFAULT_DATE, time, timezone);
}

PackedDateTime packNow()
{
    int year, dayOfYear, secOfDay, tzSeconds;
    int64_t days, usecs;
    localdate(&year, &dayOfYear, &secOfDay, &tzSeconds);
    days = daysSinceEpochYD(YearDay(year, dayOfYear));
    usecs = secOfDay * USECS_PER_SEC;
    return packDaysUseconds(days, usecs - tzSeconds * USECS_PER_SEC);
}

DayOfWeek_t dayOfWeek(PackedDateTime dateTime)
{
    return dayOfWeek(dateTime, timezoneSecs());
}

DayOfWeek_t dayOfWeek(PackedDateTime dateTime, int timezone)
{
    PackedDateTime usecs = dateTime + timezone * USECS_PER_SEC;
    return DayOfWeek_t((usecs / USECS_PER_DAY) % 7);
}

YearDay unpackYearDay(PackedDateTime dateTime)
{
    return unpackYearDay(dateTime, timezoneSecs());
}

YearDay unpackYearDay(PackedDateTime dateTime, int timezone)
{
    int year = 0, day = 0;
    auto days = (dateTime + timezone * USECS_PER_SEC) / USECS_PER_DAY;
    toInternalYD(&year, &day, days);
    if (day >= gAccumulatedDays[10])
    {
        day -= gAccumulatedDays[10];
    }
    else
    {
        --year;
        day += 31 + (isLeapYear(year) ? 29 : 28);
    }
    return YearDay(year, day + 1);
}

YearWeekDay unpackYearWeekDay(PackedDateTime dateTime,
                              DayOfWeek_t firstDayOfWeek)
{
    return unpackYearWeekDay(dateTime, firstDayOfWeek, timezoneSecs());
}

YearWeekDay unpackYearWeekDay(PackedDateTime dateTime,
                              DayOfWeek_t firstDayOfWeek,
                              int timezone)
{
    YearDay yd = unpackYearDay(dateTime, timezone);
    int dow = dayOfWeek(dateTime, timezone);
    int week = toWeek(yd.day - 1, dow, firstDayOfWeek);
    if (week == 0)
    {
        --yd.year;
        week = toWeek(yd.day + 364 + (isLeapYear(yd.year) ? 1 : 0),
                            dow, firstDayOfWeek);
    }
    else if (week == 53 &&
             1 == toWeek(yd.day - 366 - (isLeapYear(yd.year - 1) ? 1 : 0),
                         dow, firstDayOfWeek))
    {
        ++yd.year;
        week = 1;
    }
    return YearWeekDay(yd.year, week, DayOfWeek_t(dow));
}

std::pair<YearMonthDay, HourMinuteSecond>
    unpackDateTime(PackedDateTime dateTime)
{
    return unpackDateTime(dateTime, timezoneSecs());
}

std::pair<YearMonthDay, HourMinuteSecond>
    unpackDateTime(PackedDateTime dateTime, int timezone)
{
    auto dayUsecs = unpackDaysUseconds(dateTime + timezone * USECS_PER_SEC);
    return std::make_pair(toYMD(dayUsecs.first), toHMS(dayUsecs.second));
}

YearMonthDay unpackDate(PackedDateTime dateTime)
{
    return unpackDate(dateTime, timezoneSecs());
}

YearMonthDay unpackDate(PackedDateTime dateTime, int timezone)
{
    return toYMD(unpackDaysUseconds(dateTime + timezone * USECS_PER_SEC).first);
}

HourMinuteSecond unpackTime(PackedDateTime dateTime)
{
    return unpackTime(dateTime, timezoneSecs());
}

HourMinuteSecond unpackTime(PackedDateTime dateTime, int timezone)
{
    return toHMS(unpackDaysUseconds(dateTime + timezone * USECS_PER_SEC).second);
}

void dateTimeToTm(tm& time, PackedDateTime dateTime)
{
    return dateTimeToTm(time, dateTime, timezoneSecs());
}

void dateTimeToTm(tm& time, PackedDateTime dateTime, int timezone)
{
    auto dt = unpackDateTime(dateTime, timezone);
    time.tm_mon = dt.first.month - 1;
    time.tm_mday = dt.first.day;
    time.tm_hour = dt.second.hour;
    time.tm_min = dt.second.minute;
    time.tm_sec = dt.second.second;
    time.tm_year = dt.first.year >= 1900 ? dt.first.year - 1900 : 0;
    time.tm_wday = dayOfWeek(dateTime, timezone) % 7;
    auto yd = unpackYearDay(dateTime, timezone);
    time.tm_yday = yd.day - 1;
    time.tm_gmtoff = timezone;
}

PackedDateTime pack(const tm& time)
{
    return pack(YearMonthDay(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday),
                HourMinuteSecond(time.tm_hour, time.tm_min, time.tm_sec, 0),
                time.tm_gmtoff);
}

PackedDateTimeDelta packDelta(const TimeDelta& delta)
{
    return delta.days * USECS_PER_DAY +
           delta.seconds * USECS_PER_SEC +
           delta.useconds;
}

TimeDelta unpackDelta(PackedDateTimeDelta delta)
{
    auto days = delta / USECS_PER_DAY;
    delta %= USECS_PER_DAY;
    auto seconds = delta / USECS_PER_SEC;
    return TimeDelta(days, seconds, delta % USECS_PER_SEC);
}

}
