#ifndef JEB_JSONLIB_JSONVALUEERROR_HPP
#define JEB_JSONLIB_JSONVALUEERROR_HPP

#include <stdexcept>

namespace JEBIO { namespace Json {

class JsonValueError : public std::runtime_error
{
public:
    JsonValueError(const std::string& msg) : std::runtime_error(msg) {}
};

}}

#endif
