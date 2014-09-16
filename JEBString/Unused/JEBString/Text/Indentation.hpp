#ifndef JEB_INDENTATION_HPP
#define JEB_INDENTATION_HPP

#include <iosfwd>
#include <string>
#include <vector>
#include "JEB/JEBDefinitions.hpp"

namespace JEB {

class Indentation
{
public:
    Indentation();
    Indentation(const Indentation& rhs);
    Indentation(Indentation&& rhs);
    ~Indentation();

    Indentation& operator=(const Indentation& rhs);
    Indentation& operator=(Indentation&& rhs);

    const std::string& indentationString() const;
    void setIndentationString(const std::string& str);

    void clear();
    void pushIndent();
    void pushAlignment(unsigned pos);
    void pop();

    void write(std::ostream& os) const;

    static const std::string& defaultIndentationString();
    static void setDefaultIndentationString(const std::string& str);
private:
    std::string m_IndentationString;
    std::vector<int> m_Indents;
    static std::string s_DefaultIndentationString;
};

std::ostream& operator<<(std::ostream& os, const Indentation& i);

}

#endif
