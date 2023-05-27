#ifndef RANGE_TOOLS_UTIL_HPP
#define RANGE_TOOLS_UTIL_HPP

#include <type_traits>

namespace range_tools {

namespace internal {

template <typename T>
using Iterator = std::conditional_t<std::is_const_v<std::remove_reference_t<T>>,
                                    typename std::decay_t<T>::const_iterator, typename std::decay_t<T>::iterator>;

template <typename T>
using ReverseIterator = std::conditional_t<std::is_const_v<std::remove_reference_t<T>>,
                                           typename std::decay_t<T>::const_reverse_iterator,
                                           typename std::decay_t<T>::reverse_iterator>;

template <typename T>
using DereferIterator = decltype(*std::declval<T>());

template <typename T>
constexpr bool IsConstIterator = std::is_const_v<std::remove_reference_t<DereferIterator<T>>>;

}  // namespace internal

}  // namespace range_tools

#endif
