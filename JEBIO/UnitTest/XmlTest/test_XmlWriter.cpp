#include "JEBIO/Xml/XmlWriter.hpp"

#include <sstream>
#include <JEBTest/JEBTest.hpp>

using namespace JEBIO;
using namespace JEBIO::Xml;

void test_Constructor()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    JT_ASSERT(&writer.stream() == &ss);
}

void test_ElementWithoutText()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.beginElement("Document");
    writer.beginAttribute("attr1");
    writer.attributeValue("value1");
    writer.beginAttribute("attr2");
    writer.attributeValue("value2");
    writer.endElement();
    JT_EQUAL(ss.str(), "<Document attr1=\"value1\" attr2=\"value2\"/>");
}

void test_ElementWithText()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.beginElement("Document");
    writer.beginAttribute("attr1");
    writer.attributeValue("value1");
    writer.beginAttribute("attr2");
    writer.attributeValue("value2");
    writer.characterData("Text");
    writer.endElement();
    JT_EQUAL(ss.str(), "<Document attr1=\"value1\" attr2=\"value2\">Text</Document>");
}

void testFormatting(int formatting, const std::string& expected)
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(formatting);
    writer.beginElement("Document");
    writer.beginElement("Element");
    writer.beginAttribute("attr1");
    writer.attributeValue("value1");
    writer.beginAttribute("attr2");
    writer.attributeValue("value2");
    writer.beginElement("Text");
    writer.characterData("Text");
    writer.endElement();
    writer.endElement();
    writer.endElement();
    JT_EQUAL(ss.str(), expected);
}

void test_ElementsWithoutIndentation()
{
    const char* expected = "\
<Document><Element attr1=\"value1\" attr2=\"value2\"><Text>Text</Text></Element></Document>";
    testFormatting(XmlWriter::None,
                   expected);
}

void test_ElementsWithIndentation()
{
    const char* expected = "\
<Document>\n\
  <Element attr1=\"value1\" attr2=\"value2\">\n\
    <Text>Text</Text>\n\
  </Element>\n\
</Document>";
    testFormatting(XmlWriter::IndentElements,
                   expected);
}

void test_ElementsWithAlignment()
{
    const char* expected = "\
<Document><Element attr1=\"value1\"\n\
                   attr2=\"value2\"><Text>Text</Text></Element></Document>";
    testFormatting(XmlWriter::AlignTagText,
                   expected);
}

void test_ElementsWithFullFormatting()
{
    const char* expected = "\
<Document>\n\
  <Element attr1=\"value1\"\n\
           attr2=\"value2\">\n\
    <Text>Text</Text>\n\
  </Element>\n\
</Document>";
    testFormatting(XmlWriter::AlignTagText |
                   XmlWriter::IndentElements,
                   expected);
}

void test_ElementsWithManualFormatting()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("Document");
    writer.beginElement("Element");
    writer.beginAttribute("attr1");
    writer.attributeValue("value1");
    writer.beginAttribute("attr2");
    writer.attributeValue("value2");
    writer.beginElement("Text");
    writer.endTag();
    writer.newline();
    writer.characterData("Text");
    writer.newline(false);
    writer.endElement();
    writer.endElement();
    writer.endElement();
    const char* expected = "\
<Document>\n\
  <Element attr1=\"value1\" attr2=\"value2\">\n\
    <Text>\n\
      Text\n\
    </Text>\n\
  </Element>\n\
</Document>";
    JT_EQUAL(ss.str(), expected);
}

void test_ManualCDATA()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("Document");
    writer.beginSpecialTag("<![CDATA[", "]]>");
    writer.beginElement("Element");
    writer.beginElement("Text");
    writer.characterData("Text");
    writer.endElement();
    writer.endElement();
    writer.endTag();
    writer.endElement();
    const char* expected = "\
<Document>\n\
  <![CDATA[<Element>\n\
             <Text>Text</Text>\n\
           </Element>]]>\n\
</Document>";
    JT_EQUAL(ss.str(), expected);
}

void test_ManualIndentedCDATA()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("Document");
    writer.beginSpecialTag("<![CDATA[", "]]>");
    writer.newline();
    writer.beginElement("Element");
    writer.beginElement("Text");
    writer.characterData("Text");
    writer.endElement();
    writer.endElement();
    writer.endTag();
    writer.endElement();
    const char* expected = "\
<Document>\n\
  <![CDATA[\n\
           <Element>\n\
             <Text>Text</Text>\n\
           </Element>]]>\n\
</Document>";
    JT_EQUAL(ss.str(), expected);
}

void test_EndElementMismatch()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("Document");
    writer.beginSpecialTag("<![CDATA[", "]]>");
    JT_THROWS(writer.endElement(), std::runtime_error);
}

void test_EndTagMismatch()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginSpecialTag("<!--", "-->");
    writer.beginElement("Document");
    writer.characterData("text");
    JT_THROWS(writer.endTag(), std::logic_error);
}

void test_Comment()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("Document");
    writer.beginSpecialTag("<!--", "-->");
    writer.rawText(" Kjetil &\nKjartan Show!\n");
    writer.endTag();
    writer.endElement();
    const char* expected = "\
<Document>\n\
  <!-- Kjetil &\n\
Kjartan Show!\n\
  -->\n\
</Document>";
    JT_EQUAL(ss.str(), expected);
}

void test_Indentation()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("Document");
    writer.beginElement("Points");
    writer.endTag();
    writer.newline();
    writer.characterData("107.530");
    writer.characterData(" ");
    writer.characterData("260.322");
    writer.newline();
    writer.characterData("117.530");
    writer.characterData(" ");
    writer.characterData("270.322");
    writer.newline();
    writer.characterData("127.530");
    writer.characterData(" ");
    writer.characterData("280.322");
    writer.newline(false);
    writer.endElement();
    writer.endElement();
    const char* expected = "\
<Document>\n\
  <Points>\n\
    107.530 260.322\n\
    117.530 270.322\n\
    127.530 280.322\n\
  </Points>\n\
</Document>";
    JT_EQUAL(ss.str(), expected);
}

void test_SpecialChars()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("Document");
    writer.attribute("specialChars", "a\"b'c&d<e>f");
    writer.characterData("a\"b'c&d<e>f");
    writer.endElement();
    const char* expected = "\
<Document specialChars=\"a&quot;b'c&amp;d&lt;e&gt;f\">a\"b'c&amp;d&lt;e&gt;f</Document>";
    JT_EQUAL(ss.str(), expected);
}

void test_SwitchAttributeAlignmentOnAndOff()
{
    std::stringstream ss;
    ss.setf(std::ios_base::fixed);
    ss.precision(6);
    XmlWriter writer(ss);
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("gpx");
    writer.setFormatting(XmlWriter::IndentElements | XmlWriter::AlignTagText);
    writer.attribute("creator", 1000);
    writer.attribute("version", "1.1");
    writer.attribute("xmlns", "http://www.topografix.com/GPX/1/1");
    writer.attribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    writer.attribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd");
    writer.setFormatting(XmlWriter::IndentElements);
    writer.beginElement("trkpt");
    writer.attribute("lat", 54.123456);
    writer.attribute("lon", 10.123456);
    writer.element("name", "Name");
    writer.endElement();
    writer.endElement();
    const char* expected = "\
<gpx creator=\"1000\"\n\
     version=\"1.1\"\n\
     xmlns=\"http://www.topografix.com/GPX/1/1\"\n\
     xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
     xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">\n\
  <trkpt lat=\"54.123456\" lon=\"10.123456\">\n\
    <name>Name</name>\n\
  </trkpt>\n\
</gpx>";
    JT_EQUAL(ss.str(), expected);
}

void test_Utf8()
{
    std::stringstream ss;
    XmlWriter writer(ss);
    writer.beginElement("Elem");
    writer.attribute("attr", "ABC \xC3\x86\xC3\x98\xC3\x85");
    writer.characterData("ABC \xC3\x86\xC3\x98\xC3\x85");
    writer.endElement();
    const char* expected = "\
<Elem attr=\"ABC \xC3\x86\xC3\x98\xC3\x85\">ABC \xC3\x86\xC3\x98\xC3\x85</Elem>";
    JT_EQUAL(ss.str(), expected);
}

JT_TEST(test_Constructor,
             test_ElementWithoutText,
             test_ElementWithText,
             test_ElementsWithoutIndentation,
             test_ElementsWithIndentation,
             test_ElementsWithAlignment,
             test_ElementsWithFullFormatting,
             test_ElementsWithManualFormatting,
             test_ManualCDATA,
             test_ManualIndentedCDATA,
             test_EndElementMismatch,
             test_EndTagMismatch,
             test_Comment,
             test_Indentation,
             test_SpecialChars,
             test_SwitchAttributeAlignmentOnAndOff,
             test_Utf8
             );
