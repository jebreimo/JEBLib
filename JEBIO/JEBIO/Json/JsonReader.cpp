#include "JsonReader.hpp"

#include <iostream>

namespace JEB { namespace Json {

JsonReader::JsonReader()
    : m_TextReader(&std::cin)
{}

}}
