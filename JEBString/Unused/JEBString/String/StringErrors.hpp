#include <stdexcept>

namespace JEB { namespace String {

class EncodingError : public std::runtime_error
{
    EncodingError() : std::runtime_error() {}
    EncodingError(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidCharacter : public EncodingError
{
public:
    InvalidCharacter() : EncodingError() {}
    InvalidCharacter(const std::string& msg) : EncodingError(msg) {}
};

class IncompleteCharacter : public EncodingError
{
public:
    IncompleteCharacter() : EncodingError() {}
    IncompleteCharacter(const std::string& msg) : EncodingError(msg) {}
};

}}
