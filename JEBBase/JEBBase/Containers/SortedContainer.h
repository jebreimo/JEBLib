#include <algorithm>
#include <utility>

namespace Algorithms
{
  template <typename RndIt, typename T>
  RndIt lower_bound_first(RndIt first, RndIt last, const T& value)
  {
    while (first != last)
    {
      auto mid = first + std::distance(first, last) / 2;
      if (mid->first < value)
        first = mid + 1;
      else
        last = mid;
    }
    return first;
  }

  template <typename RndIt, typename T>
  RndIt binary_find_first(RndIt first, RndIt last, const T& value)
  {
    RndIt it = Algorithms::lower_bound_first(first, last, value);
    if (it == last || value < it->first)
      return last;
    return it;
  }
}

namespace SortedMap
{
  template <typename Container>
  size_t erase(Container& container,
          const typename Container::value_type::first_type& key)
  {
    auto pos = Algorithms::lower_bound_first(
            begin(container), end(container), key);
    if (pos == end(container) || key < pos->first)
      return 0;

    container.erase(pos);
    return 1;
  }

  template <typename Container>
  typename Container::iterator find(
          Container& container,
          const typename Container::value_type::first_type& key)
  {
    return Algorithms::binary_find_first(
            begin(container), end(container), key);
  }

  template <typename Container>
  typename Container::const_iterator find(
          const Container& container,
          const typename Container::value_type::first_type& key)
  {
    return Algorithms::binary_find_first(
            begin(container), end(container), key);
  }

  template <typename Container>
  std::pair<typename Container::iterator, bool> insert(
          Container& container,
          const typename Container::value_type& value)
  {
    auto pos = Algorithms::lower_bound_first(
            begin(container), end(container), value.first);
    if (pos != end(container) && !(value.first < pos->first))
      return std::make_pair(pos, false);
    else
      return std::make_pair(container.insert(container, value), true);
  }

  template <typename Container>
  std::pair<typename Container::iterator, bool> insert(
          Container& container,
          typename Container::value_type&& value)
  {
    auto pos = Algorithms::lower_bound_first(
            begin(container), end(container), value.first);
    if (pos != end(container) && !(value.first < pos->first))
      return std::make_pair(pos, false);
    else
      return std::make_pair(
              container.insert(container, std::move(value)), true);
  }

  template <typename Container>
  typename Container::value_type::second_type& set(
          Container& container,
          const typename Container::value_type::first_type& key,
          const typename Container::value_type::second_type& value)
  {
    auto pos = Algorithms::lower_bound_first(
            begin(container), end(container), key);
    if (pos != end(container) && !(key < pos->first))
      return pos->second = value;
    else
      return container.insert(pos, std::make_pair(key, value))->second;
  }

  template <typename Container>
  typename Container::value_type::second_type& set(
          Container& container,
          const typename Container::value_type::first_type& key,
          typename Container::value_type::second_type&& value)
  {
    auto pos = Algorithms::lower_bound_first(
            begin(container), end(container), key);
    if (pos != end(container) && !(key < pos->first))
      return pos->second = std::move(value);
    else
      return container.insert(container,
                              std::make_pair(key, std::move(value)))->second;
  }

  template <typename Container>
  void sort(Container& container)
  {
    std::sort(begin(container), end(container),
              [](const typename Container::value_type& a,
                 const typename Container::value_type& b)
              {return a.first < b.first;});
  }
}
