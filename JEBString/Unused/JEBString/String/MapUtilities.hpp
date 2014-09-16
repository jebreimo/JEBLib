#ifndef JEB_STRING_MAPUTILITIES_HPP
#define JEB_STRING_MAPUTILITIES_HPP

#include <map>
#include "FromString.hpp"
#include "ToString.hpp"

namespace JEB { namespace String {

typedef std::map<std::string, std::string> Map_t;

template <typename T>
bool tryGet(const Map_t& map, const std::string& key, T& value)
{
    Map_t::const_iterator it = map.find(key);
    if (it == map.end())
        return false;

    return fromString(it->second, value);
}

template <>
inline bool tryGet<>(const Map_t& map, const std::string& key, std::string& value)
{
    Map_t::const_iterator it = map.find(key);
    if (it == map.end())
        return false;

    value = it->second;
    return true;
}

template <typename T>
T get(const Map_t& map, const std::string& key, const T& defaultValue)
{
    T value;
    if (tryGet(map, key, value))
        return value;
    else
        return defaultValue;
}

template <typename T>
void set(Map_t& map, const std::string& key, const T& value)
{
    map[key] = toString(value);
}

}}

#endif
