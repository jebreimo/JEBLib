/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_CONTAINERS_VECTORUTILITIES_HPP
#define JEBBASE_CONTAINERS_VECTORUTILITIES_HPP

#include <memory>
#include <utility>
#include <vector>

#include "JEBBase/JEBBaseDefinitions.hpp"

namespace JEBBase { namespace Containers {

template <typename T>
std::vector<T>& append(std::vector<T>& dst, std::vector<T>&& src)
{
    dst.reserve(dst.size() + src.size());
    for (auto it = begin(src); it != end(src); ++it)
        dst.push_back(std::move(*it));
    return dst;
}

template <typename T>
std::vector<T>& append(std::vector<T>& dst, const std::vector<T>& src)
{
    dst.reserve(dst.size() + src.size());
    for (auto it = begin(src); it != end(src); ++it)
        dst.push_back(*it);
    return dst;
}

template <typename T>
std::vector<T*>& appendPointers(std::vector<T*>& dst, std::vector<T>& src)
{
    dst.reserve(dst.size() + src.size());
    for (auto it = begin(src); it != end(src); ++it)
        dst.push_back(&*it);
    return dst;
}

template <typename T>
std::vector<const T*>& appendPointers(std::vector<const T*>& dst,
                                      std::vector<T*>& src)
{
    dst.reserve(dst.size() + src.size());
    for (auto it = begin(src); it != end(src); ++it)
        dst.push_back(*it);
    return dst;
}

template <typename T>
std::vector<const T*>& appendPointers(std::vector<const T*>& dst,
                                      std::vector<T>& src)
{
    dst.reserve(dst.size() + src.size());
    for (auto it = begin(src); it != end(src); ++it)
        dst.push_back(&*it);
    return dst;
}

template <typename T>
std::vector<const T*>& appendPointers(std::vector<const T*>& dst,
                                      const std::vector<T>& src)
{
    dst.reserve(dst.size() + src.size());
    for (auto it = begin(src); it != end(src); ++it)
        dst.push_back(&*it);
    return dst;
}

template <typename T>
std::vector<T*>& appendPointers(std::vector<T*>& dst,
                                const std::vector<std::unique_ptr<T>>& src)
{
    dst.reserve(dst.size() + src.size());
    for (auto it = begin(src); it != end(src); ++it)
        dst.push_back(it->get());
    return dst;
}

template <typename T>
std::vector<const T*> constPointers(std::vector<T>& src)
{
    std::vector<const T*> dst;
    return appendPointers(dst, src);
}

template <typename T>
std::vector<const T*> constPointers(std::vector<T*>& src)
{
    std::vector<const T*> dst;
    return appendPointers(dst, src);
}

template <typename T>
std::vector<T> makeVector(const T& p)
{
  return std::vector<T>(1, p);
}

template <typename T>
std::vector<T> makeVector(T&& p)
{
  std::vector<T> v;
  v.push_back(std::move(p));
  return v;
}

template <typename T>
std::vector<T*> pointers(std::vector<T>& src)
{
    std::vector<T*> dst;
    return appendPointers(dst, src);
}

template <typename T>
std::vector<const T*> pointers(const std::vector<T>& src)
{
    std::vector<const T*> dst;
    return appendPointers(dst, src);
}

template <typename T>
std::vector<T*> pointers(const std::vector<std::unique_ptr<T>>& src)
{
  std::vector<T*> dst;
  return appendPointers(dst, src);
}

}}

#endif
