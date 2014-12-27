#include "Indentation.hpp"

#include <cassert>
#include <limits>
#include <ostream>
#include <stdexcept>

using namespace std;

namespace JEBIO {

std::string Indentation::s_DefaultIndentationString("  ");

Indentation::Indentation()
    : m_IndentationString(s_DefaultIndentationString)
{
}

Indentation::Indentation(const Indentation& rhs)
    : m_IndentationString(rhs.m_IndentationString),
      m_Indents(rhs.m_Indents)
{
}

Indentation::Indentation(Indentation&& rhs)
    : m_IndentationString(std::move(rhs.m_IndentationString)),
      m_Indents(std::move(rhs.m_Indents))
{
}

Indentation::~Indentation()
{}

Indentation& Indentation::operator=(const Indentation& rhs)
{
    m_IndentationString = rhs.m_IndentationString;
    m_Indents = rhs.m_Indents;
    return *this;
}

Indentation& Indentation::operator=(Indentation&& rhs)
{
    m_IndentationString.clear();
    m_IndentationString.swap(rhs.m_IndentationString);
    m_Indents.clear();
    m_Indents.swap(rhs.m_Indents);
    return *this;
}

const std::string& Indentation::indentationString() const
{
    return m_IndentationString;
}

void Indentation::setIndentationString(const std::string& indentationString)
{
    m_IndentationString = indentationString;
}

void Indentation::clear()
{
    m_Indents.clear();
}

void Indentation::pushIndent()
{
    m_Indents.push_back(-1);
}

void Indentation::pushAlignment(unsigned pos)
{
    assert((int)pos >= 0);
    m_Indents.push_back(pos);
}

void Indentation::pop()
{
    if (m_Indents.empty())
        throw runtime_error("Can't pop, stack is empty");
    m_Indents.erase(m_Indents.end() - 1);
}

void Indentation::write(ostream& os) const
{
    for (vector<int>::const_iterator it = m_Indents.begin(); it != m_Indents.end(); it++)
    {
        if (*it == -1)
        {
            os << m_IndentationString;
        }
        else
        {
            for (int i = 0; i < *it; i++)
                os.put(' ');
        }
    }
}

const std::string& Indentation::defaultIndentationString()
{
    return s_DefaultIndentationString;
}

void Indentation::setDefaultIndentationString(const std::string& str)
{
    s_DefaultIndentationString = str;
}

std::ostream& operator<<(std::ostream& os, const Indentation& i)
{
    i.write(os);
    return os;
}

}
