#include "FromString.hpp"

#include <cctype>
#include <cstdlib>
#include <locale>

namespace JEB { namespace String {

bool fromString(const std::string& s, bool& value)
{
    if (s == "1" || s == "true")
        value = true;
    else if (s == "0" || s == "false")
        value = false;
    else
        return false;

    return true;
}

bool fromString(const std::wstring& s, bool& value)
{
    if (s == L"1" || s == L"true")
        value = true;
    else if (s == L"0" || s == L"false")
        value = false;
    else
        return false;

    return true;
}

bool fromString(const std::string& s, double value)
{
    char* end;
    value = std::strtod(s.c_str(), &end);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}

bool fromString(const std::string& s, std::string& value)
{
    value = s;
    return true;
}

bool fromString(const std::wstring& s, std::wstring& value)
{
    value = s;
    return true;
}

bool fromString(std::string&& s, std::string& value)
{
    value = std::move(s);
    return true;
}

bool fromString(std::wstring&& s, std::wstring& value)
{
    value = std::move(s);
    return true;
}

bool fromString(const std::wstring& s, double value)
{
    wchar_t* end;
    value = std::wcstod(s.c_str(), &end);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}

bool fromString(const std::string& s, long& value, int base)
{
    char* end;
    value = std::strtol(s.c_str(), &end, base);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}

bool fromString(const std::wstring& s, long& value, int base)
{
    wchar_t* end;
    value = std::wcstol(s.c_str(), &end, base);
    return end != s.c_str() && (*end == '\0' || std::isspace(*end));
}

}}
