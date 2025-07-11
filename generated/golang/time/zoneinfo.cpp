// generated by GoCpp from file '$(ImportDir)/time/zoneinfo.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/time/zoneinfo.h"
#include "gocpp/support.h"

#include "golang/errors/errors.h"
#include "golang/sync/atomic/type.h"
#include "golang/sync/mutex.h"
#include "golang/sync/once.h"
#include "golang/syscall/env_windows.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/zerrors_windows.h"
#include "golang/time/time.h"
#include "golang/time/zoneinfo_read.h"
#include "golang/time/zoneinfo_windows.h"

namespace golang::time
{
    namespace rec
    {
        using namespace mocklib::rec;
        using sync::rec::Do;
    }

    // A Location maps time instants to the zone in use at that time.
    // Typically, the Location represents the collection of time offsets
    // in use in a geographical area. For many Locations the time offset varies
    // depending on whether daylight savings time is in use at the time instant.
    //
    // Location is used to provide a time zone in a printed Time value and for
    // calculations involving intervals that may cross daylight savings time
    // boundaries.
    
    template<typename T> requires gocpp::GoStruct<T>
    Location::operator T()
    {
        T result;
        result.name = this->name;
        result.zone = this->zone;
        result.tx = this->tx;
        result.extend = this->extend;
        result.cacheStart = this->cacheStart;
        result.cacheEnd = this->cacheEnd;
        result.cacheZone = this->cacheZone;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Location::operator==(const T& ref) const
    {
        if (name != ref.name) return false;
        if (zone != ref.zone) return false;
        if (tx != ref.tx) return false;
        if (extend != ref.extend) return false;
        if (cacheStart != ref.cacheStart) return false;
        if (cacheEnd != ref.cacheEnd) return false;
        if (cacheZone != ref.cacheZone) return false;
        return true;
    }

    std::ostream& Location::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << name;
        os << " " << zone;
        os << " " << tx;
        os << " " << extend;
        os << " " << cacheStart;
        os << " " << cacheEnd;
        os << " " << cacheZone;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Location& value)
    {
        return value.PrintTo(os);
    }

    // A zone represents a single time zone such as CET.
    
    template<typename T> requires gocpp::GoStruct<T>
    zone::operator T()
    {
        T result;
        result.name = this->name;
        result.offset = this->offset;
        result.isDST = this->isDST;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool zone::operator==(const T& ref) const
    {
        if (name != ref.name) return false;
        if (offset != ref.offset) return false;
        if (isDST != ref.isDST) return false;
        return true;
    }

    std::ostream& zone::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << name;
        os << " " << offset;
        os << " " << isDST;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct zone& value)
    {
        return value.PrintTo(os);
    }

    // A zoneTrans represents a single time zone transition.
    
    template<typename T> requires gocpp::GoStruct<T>
    zoneTrans::operator T()
    {
        T result;
        result.when = this->when;
        result.index = this->index;
        result.isstd = this->isstd;
        result.isutc = this->isutc;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool zoneTrans::operator==(const T& ref) const
    {
        if (when != ref.when) return false;
        if (index != ref.index) return false;
        if (isstd != ref.isstd) return false;
        if (isutc != ref.isutc) return false;
        return true;
    }

    std::ostream& zoneTrans::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << when;
        os << " " << index;
        os << " " << isstd;
        os << " " << isutc;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct zoneTrans& value)
    {
        return value.PrintTo(os);
    }

    // alpha and omega are the beginning and end of time for zone
    // transitions.
    // UTC represents Universal Coordinated Time (UTC).
    Location* UTC = & utcLoc;
    // utcLoc is separate so that get can refer to &utcLoc
    // and ensure that it never returns a nil *Location,
    // even if a badly behaved client has changed UTC.
    Location utcLoc = gocpp::Init<Location>([](auto& x) {
        x.name = "UTC"s;
    });
    // Local represents the system's local time zone.
    // On Unix systems, Local consults the TZ environment
    // variable to find the time zone to use. No TZ means
    // use the system default /etc/localtime.
    // TZ="" means use UTC.
    // TZ="foo" means use file foo in the system timezone directory.
    Location* Local = & localLoc;
    // localLoc is separate so that initLocal can initialize
    // it even if a client has changed Local.
    Location localLoc;
    sync::Once localOnce;
    struct Location* rec::get(struct Location* l)
    {
        if(l == nullptr)
        {
            return & utcLoc;
        }
        if(l == & localLoc)
        {
            rec::Do(gocpp::recv(localOnce), initLocal);
        }
        return l;
    }

    // String returns a descriptive name for the time zone information,
    // corresponding to the name argument to LoadLocation or FixedZone.
    std::string rec::String(struct Location* l)
    {
        return rec::get(gocpp::recv(l))->name;
    }

    gocpp::slice<Location*> unnamedFixedZones;
    sync::Once unnamedFixedZonesOnce;
    // FixedZone returns a Location that always uses
    // the given zone name and offset (seconds east of UTC).
    struct Location* FixedZone(std::string name, int offset)
    {
        // Most calls to FixedZone have an unnamed zone with an offset by the hour.
        // Optimize for that case by returning the same *Location for a given hour.
        auto hoursBeforeUTC = 12;
        auto hoursAfterUTC = 14;
        auto hour = offset / 60 / 60;
        if(name == ""s && - hoursBeforeUTC <= hour && hour <= + hoursAfterUTC && hour * 60 * 60 == offset)
        {
            rec::Do(gocpp::recv(unnamedFixedZonesOnce), [=]() mutable -> void
            {
                unnamedFixedZones = gocpp::make(gocpp::Tag<gocpp::slice<Location*>>(), hoursBeforeUTC + 1 + hoursAfterUTC);
                for(auto hr = - hoursBeforeUTC; hr <= + hoursAfterUTC; hr++)
                {
                    unnamedFixedZones[hr + hoursBeforeUTC] = fixedZone(""s, hr * 60 * 60);
                }
            });
            return unnamedFixedZones[hour + hoursBeforeUTC];
        }
        return fixedZone(name, offset);
    }

    struct Location* fixedZone(std::string name, int offset)
    {
        auto l = gocpp::InitPtr<Location>([=](auto& x) {
            x.name = name;
            x.zone = gocpp::slice<zone> { {name, offset, false}};
            x.tx = gocpp::slice<zoneTrans> { {alpha, 0, false, false}};
            x.cacheStart = alpha;
            x.cacheEnd = omega;
        });
        l->cacheZone = & l->zone[0];
        return l;
    }

    // lookup returns information about the time zone in use at an
    // instant in time expressed as seconds since January 1, 1970 00:00:00 UTC.
    //
    // The returned information gives the name of the zone (such as "CET"),
    // the start and end times bracketing sec when that zone is in effect,
    // the offset in seconds east of UTC (such as -5*60*60), and whether
    // the daylight savings is being observed at that time.
    std::tuple<std::string, int, int64_t, int64_t, bool> rec::lookup(struct Location* l, int64_t sec)
    {
        std::string name;
        int offset;
        int64_t start;
        int64_t end;
        bool isDST;
        l = rec::get(gocpp::recv(l));
        if(len(l->zone) == 0)
        {
            name = "UTC"s;
            offset = 0;
            start = alpha;
            end = omega;
            isDST = false;
            return {name, offset, start, end, isDST};
        }
        if(auto zone = l->cacheZone; zone != nullptr && l->cacheStart <= sec && sec < l->cacheEnd)
        {
            name = zone->name;
            offset = zone->offset;
            start = l->cacheStart;
            end = l->cacheEnd;
            isDST = zone->isDST;
            return {name, offset, start, end, isDST};
        }
        if(len(l->tx) == 0 || sec < l->tx[0].when)
        {
            auto zone = & l->zone[rec::lookupFirstZone(gocpp::recv(l))];
            name = zone->name;
            offset = zone->offset;
            start = alpha;
            if(len(l->tx) > 0)
            {
                end = l->tx[0].when;
            }
            else
            {
                end = omega;
            }
            isDST = zone->isDST;
            return {name, offset, start, end, isDST};
        }
        auto tx = l->tx;
        end = omega;
        auto lo = 0;
        auto hi = len(tx);
        for(; hi - lo > 1; )
        {
            auto m = int((unsigned int)(lo + hi) >> 1);
            auto lim = tx[m].when;
            if(sec < lim)
            {
                end = lim;
                hi = m;
            }
            else
            {
                lo = m;
            }
        }
        auto zone = & l->zone[tx[lo].index];
        name = zone->name;
        offset = zone->offset;
        start = tx[lo].when;
        isDST = zone->isDST;
        if(lo == len(tx) - 1 && l->extend != ""s)
        {
            if(auto [ename, eoffset, estart, eend, eisDST, ok] = tzset(l->extend, start, sec); ok)
            {
                return {ename, eoffset, estart, eend, eisDST};
            }
        }
        return {name, offset, start, end, isDST};
    }

    // lookupFirstZone returns the index of the time zone to use for times
    // before the first transition time, or when there are no transition
    // times.
    //
    // The reference implementation in localtime.c from
    // https://www.iana.org/time-zones/repository/releases/tzcode2013g.tar.gz
    // implements the following algorithm for these cases:
    //  1. If the first zone is unused by the transitions, use it.
    //  2. Otherwise, if there are transition times, and the first
    //     transition is to a zone in daylight time, find the first
    //     non-daylight-time zone before and closest to the first transition
    //     zone.
    //  3. Otherwise, use the first zone that is not daylight time, if
    //     there is one.
    //  4. Otherwise, use the first zone.
    int rec::lookupFirstZone(struct Location* l)
    {
        if(! rec::firstZoneUsed(gocpp::recv(l)))
        {
            return 0;
        }
        if(len(l->tx) > 0 && l->zone[l->tx[0].index].isDST)
        {
            for(auto zi = int(l->tx[0].index) - 1; zi >= 0; zi--)
            {
                if(! l->zone[zi].isDST)
                {
                    return zi;
                }
            }
        }
        for(auto [zi, gocpp_ignored] : l->zone)
        {
            if(! l->zone[zi].isDST)
            {
                return zi;
            }
        }
        return 0;
    }

    // firstZoneUsed reports whether the first zone is used by some
    // transition.
    bool rec::firstZoneUsed(struct Location* l)
    {
        for(auto [gocpp_ignored, tx] : l->tx)
        {
            if(tx.index == 0)
            {
                return true;
            }
        }
        return false;
    }

    // tzset takes a timezone string like the one found in the TZ environment
    // variable, the time of the last time zone transition expressed as seconds
    // since January 1, 1970 00:00:00 UTC, and a time expressed the same way.
    // We call this a tzset string since in C the function tzset reads TZ.
    // The return values are as for lookup, plus ok which reports whether the
    // parse succeeded.
    std::tuple<std::string, int, int64_t, int64_t, bool, bool> tzset(std::string s, int64_t lastTxSec, int64_t sec)
    {
        std::string name;
        int offset;
        int64_t start;
        int64_t end;
        bool isDST;
        bool ok;
        std::string stdName = {};
        std::string dstName = {};
        int stdOffset = {};
        int dstOffset = {};
        std::tie(stdName, s, ok) = tzsetName(s);
        if(ok)
        {
            std::tie(stdOffset, s, ok) = tzsetOffset(s);
        }
        if(! ok)
        {
            return {""s, 0, 0, 0, false, false};
        }
        stdOffset = - stdOffset;
        if(len(s) == 0 || s[0] == ',')
        {
            return {stdName, stdOffset, lastTxSec, omega, false, true};
        }
        std::tie(dstName, s, ok) = tzsetName(s);
        if(ok)
        {
            if(len(s) == 0 || s[0] == ',')
            {
                dstOffset = stdOffset + secondsPerHour;
            }
            else
            {
                std::tie(dstOffset, s, ok) = tzsetOffset(s);
                dstOffset = - dstOffset;
            }
        }
        if(! ok)
        {
            return {""s, 0, 0, 0, false, false};
        }
        if(len(s) == 0)
        {
            s = ",M3.2.0,M11.1.0"s;
        }
        if(s[0] != ',' && s[0] != ';')
        {
            return {""s, 0, 0, 0, false, false};
        }
        s = s.make_slice(1);
        rule startRule = {};
        rule endRule = {};
        std::tie(startRule, s, ok) = tzsetRule(s);
        if(! ok || len(s) == 0 || s[0] != ',')
        {
            return {""s, 0, 0, 0, false, false};
        }
        s = s.make_slice(1);
        std::tie(endRule, s, ok) = tzsetRule(s);
        if(! ok || len(s) > 0)
        {
            return {""s, 0, 0, 0, false, false};
        }
        auto [year, gocpp_id_0, gocpp_id_1, yday] = absDate(uint64_t(sec + unixToInternal + internalToAbsolute), false);
        auto ysec = int64_t(yday * secondsPerDay) + sec % secondsPerDay;
        auto d = daysSinceEpoch(year);
        auto abs = int64_t(d * secondsPerDay);
        abs += absoluteToInternal + internalToUnix;
        auto startSec = int64_t(tzruleTime(year, startRule, stdOffset));
        auto endSec = int64_t(tzruleTime(year, endRule, dstOffset));
        auto [dstIsDST, stdIsDST] = std::tuple{true, false};
        if(endSec < startSec)
        {
            std::tie(startSec, endSec) = std::tuple{endSec, startSec};
            std::tie(stdName, dstName) = std::tuple{dstName, stdName};
            std::tie(stdOffset, dstOffset) = std::tuple{dstOffset, stdOffset};
            std::tie(stdIsDST, dstIsDST) = std::tuple{dstIsDST, stdIsDST};
        }
        if(ysec < startSec)
        {
            return {stdName, stdOffset, abs, startSec + abs, stdIsDST, true};
        }
        else
        if(ysec >= endSec)
        {
            return {stdName, stdOffset, endSec + abs, abs + 365 * secondsPerDay, stdIsDST, true};
        }
        else
        {
            return {dstName, dstOffset, startSec + abs, endSec + abs, dstIsDST, true};
        }
    }

    // tzsetName returns the timezone name at the start of the tzset string s,
    // and the remainder of s, and reports whether the parsing is OK.
    std::tuple<std::string, std::string, bool> tzsetName(std::string s)
    {
        if(len(s) == 0)
        {
            return {""s, ""s, false};
        }
        if(s[0] != '<')
        {
            for(auto [i, r] : s)
            {
                //Go switch emulation
                {
                    auto condition = r;
                    int conditionId = -1;
                    if(condition == '0') { conditionId = 0; }
                    else if(condition == '1') { conditionId = 1; }
                    else if(condition == '2') { conditionId = 2; }
                    else if(condition == '3') { conditionId = 3; }
                    else if(condition == '4') { conditionId = 4; }
                    else if(condition == '5') { conditionId = 5; }
                    else if(condition == '6') { conditionId = 6; }
                    else if(condition == '7') { conditionId = 7; }
                    else if(condition == '8') { conditionId = 8; }
                    else if(condition == '9') { conditionId = 9; }
                    else if(condition == ',') { conditionId = 10; }
                    else if(condition == '-') { conditionId = 11; }
                    else if(condition == '+') { conditionId = 12; }
                    switch(conditionId)
                    {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                        case 11:
                        case 12:
                            if(i < 3)
                            {
                                return {""s, ""s, false};
                            }
                            return {s.make_slice(0, i), s.make_slice(i), true};
                            break;
                    }
                }
            }
            if(len(s) < 3)
            {
                return {""s, ""s, false};
            }
            return {s, ""s, true};
        }
        else
        {
            for(auto [i, r] : s)
            {
                if(r == '>')
                {
                    return {s.make_slice(1, i), s.make_slice(i + 1), true};
                }
            }
            return {""s, ""s, false};
        }
    }

    // tzsetOffset returns the timezone offset at the start of the tzset string s,
    // and the remainder of s, and reports whether the parsing is OK.
    // The timezone offset is returned as a number of seconds.
    std::tuple<int, std::string, bool> tzsetOffset(std::string s)
    {
        int offset;
        std::string rest;
        bool ok;
        if(len(s) == 0)
        {
            return {0, ""s, false};
        }
        auto neg = false;
        if(s[0] == '+')
        {
            s = s.make_slice(1);
        }
        else
        if(s[0] == '-')
        {
            s = s.make_slice(1);
            neg = true;
        }
        // The tzdata code permits values up to 24 * 7 here,
        // although POSIX does not.
        int hours = {};
        std::tie(hours, s, ok) = tzsetNum(s, 0, 24 * 7);
        if(! ok)
        {
            return {0, ""s, false};
        }
        auto off = hours * secondsPerHour;
        if(len(s) == 0 || s[0] != ':')
        {
            if(neg)
            {
                off = - off;
            }
            return {off, s, true};
        }
        int mins = {};
        std::tie(mins, s, ok) = tzsetNum(s.make_slice(1), 0, 59);
        if(! ok)
        {
            return {0, ""s, false};
        }
        off += mins * secondsPerMinute;
        if(len(s) == 0 || s[0] != ':')
        {
            if(neg)
            {
                off = - off;
            }
            return {off, s, true};
        }
        int secs = {};
        std::tie(secs, s, ok) = tzsetNum(s.make_slice(1), 0, 59);
        if(! ok)
        {
            return {0, ""s, false};
        }
        off += secs;
        if(neg)
        {
            off = - off;
        }
        return {off, s, true};
    }

    // ruleKind is the kinds of rules that can be seen in a tzset string.
    // rule is a rule read from a tzset string.
    
    template<typename T> requires gocpp::GoStruct<T>
    rule::operator T()
    {
        T result;
        result.kind = this->kind;
        result.day = this->day;
        result.week = this->week;
        result.mon = this->mon;
        result.time = this->time;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool rule::operator==(const T& ref) const
    {
        if (kind != ref.kind) return false;
        if (day != ref.day) return false;
        if (week != ref.week) return false;
        if (mon != ref.mon) return false;
        if (time != ref.time) return false;
        return true;
    }

    std::ostream& rule::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << kind;
        os << " " << day;
        os << " " << week;
        os << " " << mon;
        os << " " << time;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct rule& value)
    {
        return value.PrintTo(os);
    }

    // tzsetRule parses a rule from a tzset string.
    // It returns the rule, and the remainder of the string, and reports success.
    std::tuple<struct rule, std::string, bool> tzsetRule(std::string s)
    {
        rule r = {};
        if(len(s) == 0)
        {
            return {rule {}, ""s, false};
        }
        auto ok = false;
        if(s[0] == 'J')
        {
            int jday = {};
            std::tie(jday, s, ok) = tzsetNum(s.make_slice(1), 1, 365);
            if(! ok)
            {
                return {rule {}, ""s, false};
            }
            r.kind = ruleJulian;
            r.day = jday;
        }
        else
        if(s[0] == 'M')
        {
            int mon = {};
            std::tie(mon, s, ok) = tzsetNum(s.make_slice(1), 1, 12);
            if(! ok || len(s) == 0 || s[0] != '.')
            {
                return {rule {}, ""s, false};
            }
            int week = {};
            std::tie(week, s, ok) = tzsetNum(s.make_slice(1), 1, 5);
            if(! ok || len(s) == 0 || s[0] != '.')
            {
                return {rule {}, ""s, false};
            }
            int day = {};
            std::tie(day, s, ok) = tzsetNum(s.make_slice(1), 0, 6);
            if(! ok)
            {
                return {rule {}, ""s, false};
            }
            r.kind = ruleMonthWeekDay;
            r.day = day;
            r.week = week;
            r.mon = mon;
        }
        else
        {
            int day = {};
            std::tie(day, s, ok) = tzsetNum(s, 0, 365);
            if(! ok)
            {
                return {rule {}, ""s, false};
            }
            r.kind = ruleDOY;
            r.day = day;
        }
        if(len(s) == 0 || s[0] != '/')
        {
            r.time = 2 * secondsPerHour;
            return {r, s, true};
        }
        int offset;
        std::tie(offset, s_tmp, ok) = tzsetOffset(s.make_slice(1));
        auto& s = s_tmp;
        if(! ok)
        {
            return {rule {}, ""s, false};
        }
        r.time = offset;
        return {r, s, true};
    }

    // tzsetNum parses a number from a tzset string.
    // It returns the number, and the remainder of the string, and reports success.
    // The number must be between min and max.
    std::tuple<int, std::string, bool> tzsetNum(std::string s, int min, int max)
    {
        int num;
        std::string rest;
        bool ok;
        if(len(s) == 0)
        {
            return {0, ""s, false};
        }
        num = 0;
        for(auto [i, r] : s)
        {
            if(r < '0' || r > '9')
            {
                if(i == 0 || num < min)
                {
                    return {0, ""s, false};
                }
                return {num, s.make_slice(i), true};
            }
            num *= 10;
            num += int(r) - '0';
            if(num > max)
            {
                return {0, ""s, false};
            }
        }
        if(num < min)
        {
            return {0, ""s, false};
        }
        return {num, ""s, true};
    }

    // tzruleTime takes a year, a rule, and a timezone offset,
    // and returns the number of seconds since the start of the year
    // that the rule takes effect.
    int tzruleTime(int year, struct rule r, int off)
    {
        int s = {};
        //Go switch emulation
        {
            auto condition = r.kind;
            int conditionId = -1;
            if(condition == ruleJulian) { conditionId = 0; }
            else if(condition == ruleDOY) { conditionId = 1; }
            else if(condition == ruleMonthWeekDay) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    s = (r.day - 1) * secondsPerDay;
                    if(isLeap(year) && r.day >= 60)
                    {
                        s += secondsPerDay;
                    }
                    break;
                case 1:
                    s = r.day * secondsPerDay;
                    break;
                case 2:
                    auto m1 = (r.mon + 9) % 12 + 1;
                    auto yy0 = year;
                    if(r.mon <= 2)
                    {
                        yy0--;
                    }
                    auto yy1 = yy0 / 100;
                    auto yy2 = yy0 % 100;
                    auto dow = ((26 * m1 - 2) / 10 + 1 + yy2 + yy2 / 4 + yy1 / 4 - 2 * yy1) % 7;
                    if(dow < 0)
                    {
                        dow += 7;
                    }
                    auto d = r.day - dow;
                    if(d < 0)
                    {
                        d += 7;
                    }
                    for(auto i = 1; i < r.week; i++)
                    {
                        if(d + 7 >= daysIn(Month(r.mon), year))
                        {
                            break;
                        }
                        d += 7;
                    }
                    d += int(daysBefore[r.mon - 1]);
                    if(isLeap(year) && r.mon > 2)
                    {
                        d++;
                    }
                    s = d * secondsPerDay;
                    break;
            }
        }
        return s + r.time - off;
    }

    // lookupName returns information about the time zone with
    // the given name (such as "EST") at the given pseudo-Unix time
    // (what the given time of day would be in UTC).
    std::tuple<int, bool> rec::lookupName(struct Location* l, std::string name, int64_t unix)
    {
        int offset;
        bool ok;
        l = rec::get(gocpp::recv(l));
        for(auto [i, gocpp_ignored] : l->zone)
        {
            auto zone = & l->zone[i];
            if(zone->name == name)
            {
                auto [nam, offset, gocpp_id_2, gocpp_id_3, gocpp_id_4] = rec::lookup(gocpp::recv(l), unix - int64_t(zone->offset));
                if(nam == zone->name)
                {
                    return {offset, true};
                }
            }
        }
        for(auto [i, gocpp_ignored] : l->zone)
        {
            auto zone = & l->zone[i];
            if(zone->name == name)
            {
                return {zone->offset, true};
            }
        }
        return {offset, ok};
    }

    gocpp::error errLocation = errors::New("time: invalid location name"s);
    std::string* zoneinfo;
    sync::Once zoneinfoOnce;
    // LoadLocation returns the Location with the given name.
    //
    // If the name is "" or "UTC", LoadLocation returns UTC.
    // If the name is "Local", LoadLocation returns Local.
    //
    // Otherwise, the name is taken to be a location name corresponding to a file
    // in the IANA Time Zone database, such as "America/New_York".
    //
    // LoadLocation looks for the IANA Time Zone database in the following
    // locations in order:
    //
    //   - the directory or uncompressed zip file named by the ZONEINFO environment variable
    //   - on a Unix system, the system standard installation location
    //   - $GOROOT/lib/time/zoneinfo.zip
    //   - the time/tzdata package, if it was imported
    std::tuple<struct Location*, struct gocpp::error> LoadLocation(std::string name)
    {
        if(name == ""s || name == "UTC"s)
        {
            return {UTC, nullptr};
        }
        if(name == "Local"s)
        {
            return {Local, nullptr};
        }
        if(containsDotDot(name) || name[0] == '/' || name[0] == '\\')
        {
            return {nullptr, errLocation};
        }
        rec::Do(gocpp::recv(zoneinfoOnce), [=]() mutable -> void
        {
            auto [env, gocpp_id_5] = syscall::Getenv("ZONEINFO"s);
            zoneinfo = & env;
        });
        gocpp::error firstErr = {};
        if(*zoneinfo != ""s)
        {
            if(auto [zoneData, err] = loadTzinfoFromDirOrZip(*zoneinfo, name); err == nullptr)
            {
                if(auto [z, err] = LoadLocationFromTZData(name, zoneData); err == nullptr)
                {
                    return {z, nullptr};
                }
                firstErr = err;
            }
            else
            if(err != syscall::go_ENOENT)
            {
                firstErr = err;
            }
        }
        if(auto [z, err] = loadLocation(name, platformZoneSources); err == nullptr)
        {
            return {z, nullptr};
        }
        else
        if(firstErr == nullptr)
        {
            firstErr = err;
        }
        return {nullptr, firstErr};
    }

    // containsDotDot reports whether s contains "..".
    bool containsDotDot(std::string s)
    {
        if(len(s) < 2)
        {
            return false;
        }
        for(auto i = 0; i < len(s) - 1; i++)
        {
            if(s[i] == '.' && s[i + 1] == '.')
            {
                return true;
            }
        }
        return false;
    }

}

