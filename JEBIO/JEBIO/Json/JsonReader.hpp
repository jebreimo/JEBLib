#ifndef JEB_JSONREADER_HPP
#define JEB_JSONREADER_HPP

#include <cstdint>
#include <JEB/IO/TextReader.hpp>

namespace JEB { namespace Json {

class JsonReader
{
public:
    enum TokenType
    {
        Invalid,
        Null,
        True,
        False,
        String,
        Integer,
        Float,
        Key,
        StartObject,
        EndObject,
        StartArray,
        EndArray,
        Colon, ///< Current token is a colon, only when using nextToken
        Comma, ///< Current token is a comma, only when using nextToken
        Comment, ///< Current token is a comment, only when using nextToken
        Newline, ///< Current token is a newline, only when using nextToken
        Whitespace ///< Current token is whitespace, only when using nextToken
    };

    JsonReader();
    JsonReader(std::istream& stream,
               String::Encoding_t streamEncoding);

    /** @a stream will be deleted by the destructor unless
     *  releaseStream is called.
     */
    JsonReader(std::unique_ptr<std::istream> stream,
               String::Encoding_t streamEncoding);

    bool next();
    TokenType tokenType();

    std::string string() const;
    int integer() const;
    int64_t integer64() const;
    double real() const;
    bool boolean() const;
    JsonValue value();

    /** @brief Lower-level version of next. Returns all tokens.
     */
    bool nextToken();
    std::string token();
    std::pair<const char*, const char*> getToken() const;

    std::istream* stream() const;
    void setStream(std::istream& streamPtr);
    void setStream(std::unique_ptr<std::istream> stream);
    std::istream* releaseStream();
private:
    IO::TextReader m_TextReader;
    JsonTokenizer m_Tokenizer;
};

}}

#endif
