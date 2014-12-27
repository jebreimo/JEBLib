#include "TextReader.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <JEB/IO/Encoding.hpp>
#include <JEB/String/StringConversion.hpp>

namespace JEBIO {

static const size_t PrologueSize = 8;

TextReader TextReader::open(const std::string& fileName, size_t bufferSize)
{
    std::unique_ptr<std::istream> stream(new std::ifstream(fileName));
    if (!*stream)
        throw std::runtime_error(fileName + ": unable to open the file.");
    TextReader reader(std::move(stream), String::Encoding::Unknown, bufferSize);
    if (reader.detectStreamEncoding() == String::Encoding::Unknown)
        throw std::runtime_error(fileName + ": unable to detect the encoding.");
    return reader;
}

TextReader::TextReader(size_t bufferSize)
    : m_Buffer(bufferSize + PrologueSize),
      m_BufferOffset(PrologueSize),
      m_ContentEnd(PrologueSize),
      m_Stream(&std::cin)
{
    m_Converter.setErrorMethod(String::StringConverter::InsertCharacter);
}

TextReader::TextReader(std::istream& stream,
                       String::Encoding_t streamEncoding,
                       size_t bufferSize)
    : m_Buffer(bufferSize + PrologueSize),
      m_BufferOffset(PrologueSize),
      m_ContentEnd(PrologueSize),
      m_Stream(&stream)
{
    if (streamEncoding != String::Encoding::Unknown)
        m_Converter.setEncodings(streamEncoding, String::Encoding::Utf8);
    m_Converter.setErrorMethod(String::StringConverter::InsertCharacter);
}

TextReader::TextReader(std::unique_ptr<std::istream> stream,
                       String::Encoding_t streamEncoding,
                       size_t bufferSize)
    : m_Buffer(bufferSize + PrologueSize),
      m_BufferOffset(PrologueSize),
      m_ContentEnd(PrologueSize),
      m_Stream(stream.get()),
      m_StreamPtr(std::move(stream))
{
    if (streamEncoding != String::Encoding::Unknown)
        m_Converter.setEncodings(streamEncoding, String::Encoding::Utf8);
    m_Converter.setErrorMethod(String::StringConverter::InsertCharacter);
}

TextReader::TextReader(TextReader&& rhs)
    : m_Buffer(std::move(rhs.m_Buffer)),
      m_BufferOffset(rhs.m_BufferOffset),
      m_Converter(rhs.m_Converter),
      m_ContentEnd(rhs.m_ContentEnd),
      m_Stream(rhs.m_Stream),
      m_StreamPtr(rhs.releaseStream())
{
    rhs.m_BufferOffset = 0;
}

TextReader::~TextReader()
{}

TextReader& TextReader::operator=(TextReader&& rhs)
{
    m_Stream = &rhs.stream();
    m_StreamPtr.reset(rhs.releaseStream());
    m_Converter = rhs.m_Converter;
    m_Buffer = std::move(rhs.m_Buffer);
    m_BufferOffset = rhs.m_BufferOffset;
    m_ContentEnd = rhs.m_ContentEnd;
    rhs.m_BufferOffset = 0;
    return *this;
}

bool TextReader::hasStream() const
{
    return m_Stream != nullptr;
}

std::istream& TextReader::stream() const
{
    if (!m_Stream)
        throw std::logic_error("Attempt to access stream member before it's been assigned.");
    return *m_Stream;
}

void TextReader::setStream(std::istream& stream)
{
    m_StreamPtr.reset();
    m_Stream = &stream;
}

void TextReader::setStream(std::unique_ptr<std::istream> streamPtr)
{
    m_StreamPtr = std::move(streamPtr);
    m_Stream = m_StreamPtr.get();
}

std::istream* TextReader::releaseStream()
{
    m_Stream = nullptr;
    return m_StreamPtr.release();
}

String::Encoding_t TextReader::streamEncoding() const
{
    return m_Converter.sourceEncoding();
}

void TextReader::setStreamEncoding(String::Encoding_t encoding)
{
    m_Converter.setEncodings(encoding, String::Encoding::Utf8);
}


String::Encoding_t TextReader::detectStreamEncoding()
{
    if (!read())
        return String::Encoding::Unknown;

    char* start = &m_Buffer[m_BufferOffset];
    auto result = IO::readEncoding(start, m_ContentEnd - m_BufferOffset);
    setStreamEncoding(result.first);
    m_BufferOffset += size_t(result.second - start);
    return result.first;
}

size_t TextReader::read(char* outBuffer, size_t outBufferSize)
{
    if (!outBuffer)
        throw std::invalid_argument("outBuffer is null");
    else if (outBufferSize == 0)
        throw std::invalid_argument("outBufferSize is 0");

    size_t outBufferOffset = 0;
    while (outBufferOffset < outBufferSize)
    {
        if (!read())
            return outBufferOffset;
        auto sizes = m_Converter.convert(
                &m_Buffer[m_BufferOffset],
                m_ContentEnd - m_BufferOffset,
                &outBuffer[outBufferOffset],
                outBufferSize - outBufferOffset);

        m_BufferOffset += sizes.first;
        if (m_BufferOffset > PrologueSize && m_ContentEnd - m_BufferOffset < PrologueSize)
        {
            size_t newOffset = size_t(PrologueSize + m_BufferOffset - m_ContentEnd);
            std::copy(m_Buffer.begin() + m_BufferOffset,
                      m_Buffer.begin() + m_ContentEnd,
                      m_Buffer.begin() + newOffset);
            m_BufferOffset = newOffset;
            m_ContentEnd = PrologueSize;
        }
        outBufferOffset += sizes.second;
        if (sizes.first == 0 || outBufferOffset == outBufferSize)
            return outBufferOffset;
    }
    return outBufferOffset;
}

bool TextReader::read()
{
    if (!m_Stream)
        throw std::logic_error("Stream is not set.");

    if (m_ContentEnd != PrologueSize)
        return true;

    m_Stream->read(&m_Buffer[PrologueSize], m_Buffer.size() - PrologueSize);
    if (m_Stream->gcount() == 0)
    {
        if (m_BufferOffset < PrologueSize)
            throw std::runtime_error("Incomplete character at the end of stream");
        return false;
    }
    m_ContentEnd = PrologueSize + m_Stream->gcount();
    return true;
}

}
