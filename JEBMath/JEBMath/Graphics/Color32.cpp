#include "Color32.hpp"

#include <iomanip>
#include <iostream>
#include <JEBBase/Bits/Union32.hpp>
#include <JEBBase/Bits/Union64.hpp>
#include "JEBMath/Math/ArrayMath.hpp"

using namespace std;

namespace JEB
{

inline uint32_t pack(uint32_t a, uint32_t b, uint32_t c)
{
    return a << 16 | b << 8 | c;
}

inline uint32_t pack(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    return a << 24 | b << 16 | c << 8 | d;
}

Color32::Color32()
    : m_Argb(0xFF000000u)
{
}

Color32::Color32(uint32_t argb)
    : m_Argb(argb)
{
}

Color32::Color32(uint8_t r, uint8_t g, uint8_t b)
    : m_Argb(pack(0xFFu, r, g, b))
{
}

Color32::Color32(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
    : m_Argb(pack(a, r, g, b))
{
}

Color32 Color32::fromRgb(uint32_t rgb)
{
    return Color32(rgb | 0xFF000000u);
}

uint8_t Color32::alpha() const
{
    return (uint8_t)(m_Argb >> 24);
}

void Color32::setAlpha(uint8_t alpha)
{
    m_Argb = (m_Argb & 0x00FFFFFFu) | (uint32_t)alpha << 24;
}

uint32_t Color32::argb() const
{
    return m_Argb;
}

void Color32::setArgb(uint32_t argb)
{
    m_Argb = argb;
}

uint8_t Color32::blue() const
{
    return (uint8_t)(m_Argb & 0xFFu);
}

void Color32::setBlue(uint8_t blue)
{
    m_Argb = (m_Argb & 0xFFFFFF00u) | blue;
}

uint8_t Color32::green() const
{
    return (uint8_t)(m_Argb >> 8 & 0xFFu);
}

void Color32::setGreen(uint8_t green)
{
    m_Argb = (m_Argb & 0xFFFF00FFu) | (uint32_t)green << 8;
}

uint8_t Color32::red() const
{
    return (uint8_t)(m_Argb >> 16 & 0xFFu);
}

void Color32::setRed(uint8_t red)
{
    m_Argb = (m_Argb & 0xFF00FFFFu) | (uint32_t)red << 16;
}

uint32_t Color32::rgb() const
{
    return m_Argb & 0xFFFFFFu;
}

void Color32::setRgb(uint32_t rgb)
{
    m_Argb = 0xFF000000u | rgb;
}

uint32_t Color32::rgba() const
{
    return m_Argb << 8 | m_Argb >> 24;
}

void Color32::setRgba(uint32_t rgba)
{
    m_Argb = rgba >> 8 | rgba << 24;
}

Color32 interpolateArgb(Color32 min, Color32 max, double ratio)
{
    JEBBase::Bits::Union32 min32(min.argb());
    JEBBase::Bits::Union64 min64(min32.u8);
    JEBBase::Bits::Union32 max32(max.argb());
    JEBBase::Bits::Union64 result(max32.u8);
    ArrayMath::subtract(result.u16, min64.u16);
    ArrayMath::multiply(result.u16, ratio);
    ArrayMath::add(result.u16, min64.u16);
    return Color32(JEBBase::Bits::Union32(result.u16).u32);
}

Color32 interpolateRgb(Color32 min, Color32 max, double ratio)
{
    Color32 c = interpolateArgb(min, max, ratio);
    return Color32::fromRgb(c.argb());
}

ostream& operator<<(ostream& os, const Color32& c)
{
    ostream::fmtflags oldFlags = os.flags();
    os << "#" << hex << c.argb();
    os.flags(oldFlags);
    return os;
}

}
