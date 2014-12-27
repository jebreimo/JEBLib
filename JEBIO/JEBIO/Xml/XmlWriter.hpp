#ifndef JEB_XMLWRITER_HPP
#define JEB_XMLWRITER_HPP

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>
#include "Indentation.hpp"

/** @file Defines the class XmlWriter.
 */

namespace JEBIO { namespace Xml {

/** @brief XmlWriter writes UTF-8 encoded formatted XML to an instance of
 *  std::ostream.
 */
class XmlWriter
{
public:
    enum Formatting
    {
        None = 0,
        IndentElements = 1,
        AlignTagText = 2,
    };

    /** @brief Construct an XmlWriter that writes to std::cout.
     */
    XmlWriter();
    /** @brief Construct an XmlWriter that writes to @a stream.
     *
     *  @a stream should remain valid during the entire life-time of the
     *  constructed instance, unless setStream is used to select a different
     *  stream.
     */
    XmlWriter(std::ostream& stream);
    XmlWriter(std::unique_ptr<std::ostream> stream);
    XmlWriter(XmlWriter&& rhs);
    ~XmlWriter();

    XmlWriter& operator=(XmlWriter&& rhs);

    bool open(const std::string& filename);
    void close();

    /** @brief Write the XML declaration tag.
     *
     *  The encoding is always utf-8.
     *  @param standalone the standalone attribute.
     *  @param version the version attribute.
     */
    void xmlDeclaration(bool standalone = true,
                        const std::string& version = "1.0");

    void beginAttribute(const std::string& name);
    void endAttribute();

    void attributeValue(const std::string& value);
    void attributeValue(const std::wstring& value);
    void attributeValue(int32_t value);
    void attributeValue(int64_t value);
    void attributeValue(double value);
    void attributeValue(double value, int precision);

    void attribute(const std::string& name, const std::string& value);
    void attribute(const std::string& name, const std::wstring& value);
    void attribute(const std::string& name, int32_t value);
    void attribute(const std::string& name, int64_t value);
    void attribute(const std::string& name, double value);
    void attribute(const std::string& name, double value, int precision);

    void beginElement(const std::string& name);
    void endElement();

    void element(const std::string& name, const std::string& charData);
    void element(const std::string& name, const std::wstring& charData);
    void element(const std::string& name, int32_t value);
    void element(const std::string& name, int64_t value);
    void element(const std::string& name, double value);
    void element(const std::string& name, double value, int precision);

    void endTag();

    void characterData(const std::string& charData);
    void characterData(const std::wstring& charData);
    void characterData(int32_t value);
    void characterData(int64_t value);
    void characterData(double value);
    void characterData(double value, int precision);

    void rawCharacterData(const std::string& rawData);

    void beginSpecialTag(const std::string& start, const std::string& end);

    void rawText(const std::string& text);

    void beginComment();
    void endComment();
    void comment(const std::string& str);

    void beginCData();
    void endCData();
    void cdata(const std::string& str);

    void indentLine();
    void newline(bool indent = true);

    int formatting() const;
    void setFormatting(int formatting);

    size_t indentationLevel() const;
    void setIndentationLevel(size_t indentationLevel);

    const std::string& indentation() const;
    void setIndentation(const std::string& indentation);

    bool hasStream() const;
    std::ostream& stream() const;
    void setStream(std::ostream& stream);
    void setStream(std::unique_ptr<std::ostream> stream);
    std::ostream* releaseStream();

    std::string currentIndentation();
private:
    void reset();
    void tagContext();
    void textContext();
    size_t linePos() const;
    void ensureNewline();
    void writeAttributeSeparator();
    void writeAttributeText(const std::string& s);
    void writeElementText(const std::string& s);
    void write(const std::string& s);
    void write(std::string::const_iterator beg,
               std::string::const_iterator end);

    enum State
    {
        AttributeValue,
        ElementTag,
        SpecialTag,
        Text
    };

    enum FormattingState
    {
        StartOfLine,
        AfterIndentation,
        AfterBraces,
        AfterEndTag,
        FirstAttribute,
        AfterText
    };

    std::vector<std::string> m_Context;
    int m_Formatting;
    FormattingState m_FormattingState;
    Indentation m_Indentation;
    size_t m_LinePos;
    size_t m_PrevStreamPos;
    std::vector<State> m_States;
    std::ostream* m_Stream;
    std::unique_ptr<std::ostream> m_StreamPtr;
};

}}

#endif
