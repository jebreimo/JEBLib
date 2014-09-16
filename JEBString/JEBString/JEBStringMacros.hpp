//***************************************************************************
// Copyright © 2014, Jan Erik Breimo.
// Created 2014-01-22 by Jan Erik Breimo
//***************************************************************************
#ifndef JEBSTRING_JEBSTRINGMACROS_HPP
#define JEBSTRING_JEBSTRINGMACROS_HPP

#include <sstream>

#ifdef _MSC_VER
  #define FORMAT_STRING(msg) \
      static_cast<std::ostringstream&>(static_cast<std::ostream&>(std::ostringstream()) << msg).str()
  #define FORMAT_WSTRING(msg) \
      static_cast<std::wostringstream&>(static_cast<std::wostream&>(std::wostringstream()) << msg).str()
#else
  #define FORMAT_STRING(msg) \
      (std::ostringstream() << msg).str()
  #define FORMAT_WSTRING(msg) \
      (std::wostringstream() << msg).str()
#endif

#endif
