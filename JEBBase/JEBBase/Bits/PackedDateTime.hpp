/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_BITS_PACKEDDATETIME_H
#define JEBBASE_BITS_PACKEDDATETIME_H

#include <ctime>
#include <cstdint>
#include <utility>
#include "JEBBase/JEBBaseDefinitions.hpp"

/** @file This file defines a memory efficient representation of
    Gregorian dates and time. The resolution for time is microseconds
    and years range from 1200 to more than 500,000.

    PackedDateTime has several advantages, first it has no invalid values,
    every value maps to a unique date and time; second is it's a 64-bit integer
    so all operators that apply to integers also applies to dates and times,
    in particular assignment, omparison, addition´and subtraction operators;
    third, all these operations are very fast.
*/

namespace JEBBase {

enum Timezones
{
    TZ_UTC = 0, /* Coordinated Universal Time, civil time */
    TZ_GMT = 0, /* Greenwich Mean Time (UTC) */
    TZ_BST = 60 * 60, /* British Summer Time (UTC+1) */
    TZ_IST = 60 * 60, /* Irish Summer Time (UTC+1) */
    TZ_WET = 0, /* Western Europe Time (UTC) */
    TZ_WEST = 60 * 60, /* Western Europe Summer Time (UTC+1) */
    TZ_CET = 60 * 60, /* Central Europe Time (UTC+1) */
    TZ_CEST = 2 * 60 * 60, /* Central Europe Summer Time (UTC+2) */
    TZ_EET = 2 * 60 * 60, /* Eastern Europe Time (UTC+2) */
    TZ_EEST = 3 * 60 * 60, /* Eastern Europe Summer Time (UTC+3) */
    TZ_MSK = 3 * 60 * 60, /* Moscow Time (UTC+3) */
    TZ_MSD = 4 * 60 * 60, /* Moscow Summer Time (UTC+4) */
    TZ_AST = -4 * 60 * 60, /* Atlantic Standard Time (UTC-4) */
    TZ_ADT = -3 * 60 * 60, /* Atlantic Daylight Saving Time (UTC-3) */
    TZ_EST = -5 * 60 * 60, /* Eastern Standard Time (UTC-5) */
    TZ_EDT = -4 * 60 * 60, /* Eastern Daylight Saving Time (UTC-4) */
    TZ_CST = -6 * 60 * 60, /* Central Standard Time (UTC-6) */
    TZ_CDT = -5 * 60 * 60, /* Central Daylight Saving Time (UTC-5) */
    TZ_MST = -7 * 60 * 60, /* Mountain Standard Time (UTC-7) */
    TZ_MDT = -6 * 60 * 60, /* Mountain Daylight Saving Time (UTC-6) */
    TZ_PST = -8 * 60 * 60, /* Pacific Standard Time (UTC-8) */
    TZ_PDT = -7 * 60 * 60, /* Pacific Daylight Saving Time (UTC-7) */
    TZ_HST = -10 * 60 * 60, /* Hawaiian Standard Time (UTC-10) */
    TZ_AKST = -9 * 60 * 60, /* Alaska Standard Time (UTC-9) */
    TZ_AKDT = -8 * 60 * 60, /* Alaska Standard Daylight Saving Time (UTC-8) */
};

struct DayOfWeek
{
    enum Enum
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
};

typedef DayOfWeek::Enum DayOfWeek_t;

struct YearMonthDay
{
    int year, month, day;

    YearMonthDay()
        : year(), month(), day()
    {}

    YearMonthDay(int year, int month, int day)
        : year(year), month(month), day(day)
    {}
};

struct YearDay
{
    int year, day;

    YearDay() : year(), day()
    {}

    YearDay(int year, int day)
        : year(year), day(day)
    {}
};

struct YearWeekDay
{
    int year, week;
    DayOfWeek_t day;

    YearWeekDay() : year(), week(), day()
    {}

    YearWeekDay(int year, int week, DayOfWeek_t day)
        : year(year), week(week), day(day)
    {}
};

struct HourMinuteSecond
{
    int hour, minute, second, usecond;

    HourMinuteSecond()
        : hour(0), minute(0), second(0), usecond(0)
    {}

    HourMinuteSecond(int hour, int minute, int second, int usecond = 0)
        : hour(hour),
          minute(minute),
          second(second),
          usecond(usecond)
    {}
};

struct TimeDelta
{
    int days, seconds, useconds;

    TimeDelta() : days(), seconds(), useconds()
    {}

    TimeDelta(int days, int seconds, int useconds = 0)
        : days(days), seconds(seconds), useconds(useconds)
    {}
};

/** Number of micro-seconds since the epoch.
*/
typedef uint64_t PackedDateTime;

/** @brief Returns the PackedDateTime value for the given date and time
    in the local timezone.
*/
PackedDateTime pack(const YearMonthDay& date, const HourMinuteSecond& time);

/** @brief Returns the PackedDateTime value for the given date and time
    in @a timezone.
*/
PackedDateTime pack(const YearMonthDay& date, const HourMinuteSecond& time,
                    int timezone);

/** @brief Returns the PackedDateTime value for the given date
    in the local timezone.
    @note Time will be 12:00:00 in the local timezone.
*/
PackedDateTime pack(const YearMonthDay& date);

/** @brief Returns the PackedDateTime value for the given date
    in @a timezone.
*/
PackedDateTime pack(const YearMonthDay& date, int timezone);

/** @brief Returns the PackedDateTime value for the given time
    in the local timezone.
    @note Date will be 1200-01-01.
*/
PackedDateTime pack(const HourMinuteSecond& time);

/** @brief Returns the PackedDateTime value for the given time
    in @a timezone.
    @param hour the hour (the range is 0 to 23)
    @param minute the minute (the range is 0 to 59)
    @param second the second (the range is 0 to 59)
    @param usecond the microsecond (the range is 0 to 999,999)
    @param timezone the time zone measured in seconds (meaningful values
           are within the range -13 to 13 hours).
    @note Date will be 1200-01-01.
*/
PackedDateTime pack(const HourMinuteSecond& time, int timezone);

/** @brief Returns the PackedDateTime value for the current date and time
    in the local timezone.
*/
PackedDateTime packNow();

std::pair<YearMonthDay, HourMinuteSecond>
    unpackDateTime(PackedDateTime dateTime);

std::pair<YearMonthDay, HourMinuteSecond>
    unpackDateTime(PackedDateTime dateTime, int timezone);

YearMonthDay unpackDate(PackedDateTime dateTime);

YearMonthDay unpackDate(PackedDateTime dateTime, int timezone);

HourMinuteSecond unpackTime(PackedDateTime dateTime);

HourMinuteSecond unpackTime(PackedDateTime dateTime, int timezone);

void dateTimeToTm(tm& time, PackedDateTime dateTime);
void dateTimeToTm(tm& time, PackedDateTime dateTime, int timezone);
PackedDateTime pack(const tm& time);

/** @brief Returns the day of week of @a dateTime. Monday is 1, Sunday is 7.
    @param dateTime the packed date and time
*/
YearWeekDay unpackYearWeekDay(
        PackedDateTime dateTime,
        DayOfWeek_t firstDayOfWeek = DayOfWeek::Monday);

/** @brief Returns the day of week of @a dateTime. Monday is 1, Sunday is 7.
    @param dateTime the packed date and time
    @param timezone the time zone measured in seconds (meaningful values
           are within the range -13 to 13 hours).
*/
YearWeekDay unpackYearWeekDay(
        PackedDateTime dateTime,
        DayOfWeek_t firstDayOfWeek,
        int timezone);

/** @brief Computes the year and day of year of @a dateTime in the
    local time zone.
    @param year receives the year
    @param dayOfYear receives the day of year (the range is 1  to 366)
    @param dateTime the packed date and time
*/
YearDay unpackYearDay(PackedDateTime dateTime);

/** @brief Computes the year and day of year of @a dateTime
    in time zone @a timezone.
    @param year receives the year
    @param dayOfYear receives the day of year (the range is 1  to 366)
    @param dateTime the packed date and time
    @param timezone the time zone measured in seconds (meaningful values
           are within the range -13 to 13 hours).
*/
YearDay unpackYearDay(PackedDateTime dateTime, int timezone);

DayOfWeek_t dayOfWeek(PackedDateTime dateTime);
DayOfWeek_t dayOfWeek(PackedDateTime dateTime, int timezone);

typedef int64_t PackedDateTimeDelta;

PackedDateTimeDelta packDelta(const TimeDelta& delta);
TimeDelta unpackDelta(PackedDateTimeDelta delta);

}

#endif
