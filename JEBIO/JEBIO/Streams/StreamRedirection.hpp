#ifndef JEB_SYS_STREAMREDIRECTION_HPP
#define JEB_SYS_STREAMREDIRECTION_HPP

#include <ios>
#include "JEBIO/JEBIODefinitions.hpp"

namespace JEBIO {

class StreamRedirection
{
public:
    StreamRedirection(std::ios& stream, std::ios& replacement);
    StreamRedirection(std::ios& stream, std::streambuf* replacement);
    StreamRedirection(StreamRedirection&& other);
    ~StreamRedirection();
private:
    std::ios& m_Stream;
    std::streambuf* m_OriginalBuffer;
};

}

#endif
