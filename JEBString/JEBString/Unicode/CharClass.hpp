#ifndef JEBSTRING_UNICODE_CHARCLASS_HPP
#define JEBSTRING_UNICODE_CHARCLASS_HPP

#include <cstdint>
#include "JEBString/JEBStringDefinitions.hpp"

namespace JEBString { namespace Unicode {

namespace CharClass
{
    enum Enum
    {
        UppercaseLetter =       0x00000001ul, // an uppercase letter
        LowercaseLetter =       0x00000002ul, // a lowercase letter
        TitlecaseLetter =       0x00000004ul, // a digraphic character, with first part uppercase
        CasedLetter =           0x00000007ul, // Lu | Ll | Lt
        ModifierLetter =        0x00000008ul, // a modifier letter
        OtherLetter =           0x00000010ul, // other letters, including syllables and ideographs
        Letter =                0x0000001Ful, // Lu | Ll | Lt | Lm | Lo
        NonspacingMark =        0x00000020ul, // a nonspacing combining mark (zero advance width)
        SpacingMark =           0x00000040ul, // a spacing combining mark (positive advance width)
        EnclosingMark =         0x00000080ul, // an enclosing combining mark
        Mark =                  0x000000E0ul, // Mn | Mc | Me
        DecimalNumber =         0x00000100ul, // a decimal digit
        LetterNumber =          0x00000200ul, // a letterlike numeric character
        OtherNumber =           0x00000400ul, // a numeric character of other type
        Number =                0x00000700ul, // Nd | Nl | No
        ConnectorPunctuation =  0x00000800ul, // a connecting punctuation mark, like a tie
        DashPunctuation =       0x00001000ul, // a dash or hyphen punctuation mark
        OpenPunctuation =       0x00002000ul, // an opening punctuation mark (of a pair)
        ClosePunctuation =      0x00004000ul, // a closing punctuation mark (of a pair)
        InitialPunctuation =    0x00008000ul, // an initial quotation mark
        FinalPunctuation =      0x00010000ul, // a final quotation mark
        OtherPunctuation =      0x00020000ul, // a punctuation mark of other type
        Punctuation =           0x0003F800ul, // Pc | Pd | Ps | Pe | Pi | Pf | Po
        MathSymbol =            0x00040000ul, // a symbol of mathematical use
        CurrencySymbol =        0x00080000ul, // a currency sign
        ModifierSymbol =        0x00100000ul, // a non-letterlike modifier symbol
        OtherSymbol =           0x00200000ul, // a symbol of other type
        Symbol =                0x003C0000ul, // Sm | Sc | Sk | So
        SpaceSeparator =        0x00400000ul, // a space character (of various non-zero widths)
        LineSeparator =         0x00800000ul, // U+2028 LINE SEPARATOR only
        ParagraphSeparator =    0x01000000ul, // U+2029 PARAGRAPH SEPARATOR only
        Separator =             0x01C00000ul, // Zs | Zl | Zp
        Control =               0x02000000ul, // a C0 or C1 control code
        Format =                0x04000000ul, // a format control character
        Surrogate =             0x08000000ul, // a surrogate code point
        PrivateUse =            0x10000000ul, // a private-use character
        Unassigned =            0x20000000ul, // a reserved unassigned code point or a noncharacter
        Other =                 0x3E000000ul  // Cc | Cf | Cs | Co | Cn
    };
}

CharClass::Enum charClass(uint32_t ch);

}}

#endif
