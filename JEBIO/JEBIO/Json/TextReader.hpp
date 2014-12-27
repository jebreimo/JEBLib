#ifndef JEB_TEXTREADER_HPP
#define JEB_TEXTREADER_HPP

#include <memory>
#include <iosfwd>
#include <vector>
#include <JEB/String/StringConversion.hpp>

namespace JEBIO {

class TextReader
{
public:
    typedef std::vector<char> Buffer;

    static const size_t DefaultBufferSize = 16 * 1024;

    /** @brief Opens a file, detects its encoding and return a TextReader.
     *
     *  @throws std::runtime_error if the file doesn't exist, can't be opened
     *      or has an unrecognized encoding.
     */
    static TextReader open(const std::string& fileName,
                           size_t bufferSize = DefaultBufferSize);

    TextReader(size_t bufferSize = DefaultBufferSize);
    TextReader(std::istream& stream,
               String::Encoding_t streamEncoding,
               size_t bufferSize = DefaultBufferSize);

    /** @brief The TextReader will delete stream in its destructor.
     */
    TextReader(std::unique_ptr<std::istream> stream,
               String::Encoding_t streamEncoding,
               size_t bufferSize = DefaultBufferSize);
    TextReader(TextReader&& rhs);
    ~TextReader();

    TextReader& operator=(TextReader&& rhs);

    bool hasStream() const;
    std::istream& stream() const;
    void setStream(std::istream& stream);
    void setStream(std::unique_ptr<std::istream> streamPtr);
    std::istream* releaseStream();

    String::Encoding_t streamEncoding() const;
    void setStreamEncoding(String::Encoding_t encoding);

    String::Encoding_t detectStreamEncoding();

    /** @brief Reads a new buffer from the file and discards the previous.
     */
    size_t read(char* buffer, size_t bufferSize);
private:
    bool read();

    Buffer m_Buffer;
    size_t m_BufferOffset;
    String::StringConverter m_Converter;
    size_t m_ContentEnd;
    std::istream* m_Stream;
    std::unique_ptr<std::istream> m_StreamPtr;
};

}

#endif
