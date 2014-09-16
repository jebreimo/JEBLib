#ifndef JEB_COLOR32_HPP
#define JEB_COLOR32_HPP

#include <iosfwd>
#include <cstdint>
#include "JEBMath/JEBMathDefinitions.hpp"

namespace JEB
{

class Color32
{
public:
    static Color32 fromRgb(uint32_t rgb);

    Color32();
    Color32(uint32_t argb);
    Color32(uint8_t r, uint8_t g, uint8_t b);
    Color32(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

    uint8_t alpha() const;
    void setAlpha(uint8_t alpha);

    uint32_t argb() const;
    void setArgb(uint32_t argb);

    uint8_t blue() const;
    void setBlue(uint8_t blue);

    uint8_t green() const;
    void setGreen(uint8_t green);

    uint8_t red() const;
    void setRed(uint8_t red);

    uint32_t rgb() const;
    void setRgb(uint32_t rgb);

    uint32_t rgba() const;
    void setRgba(uint32_t rgba);
private:
    uint32_t m_Argb;
};

Color32 interpolateArgb(Color32 min, Color32 max, double ratio);
Color32 interpolateRgb(Color32 min, Color32 max, double ratio);

std::ostream& operator<<(std::ostream& os, const Color32& c);

}

#endif
