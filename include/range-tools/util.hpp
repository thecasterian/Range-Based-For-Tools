#ifndef RANGE_TOOLS_UTIL_HPP
#define RANGE_TOOLS_UTIL_HPP

#include <type_traits>

namespace range_tools {

namespace internal {

template <typename Base>
using Iterator = std::conditional_t<std::is_const_v<std::remove_reference_t<Base>>,
                                    typename std::decay_t<Base>::const_iterator, typename std::decay_t<Base>::iterator>;

template <typename Base>
using ReverseIterator = std::conditional_t<std::is_const_v<std::remove_reference_t<Base>>,
                                           typename std::decay_t<Base>::const_reverse_iterator,
                                           typename std::decay_t<Base>::reverse_iterator>;

template <typename Iter>
using DereferIterator = typename std::iterator_traits<Iter>::reference;

template <typename Iter>
constexpr bool IS_CONST_ITERATOR = std::is_const_v<std::remove_reference_t<DereferIterator<Iter>>>;

}  // namespace internal

}  // namespace range_tools

#endif
