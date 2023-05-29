#ifndef RANGE_TOOLS_UTIL_HPP
#define RANGE_TOOLS_UTIL_HPP

#include <type_traits>

namespace range_tools {

namespace internal {

template <typename Cont>
class IteratorHelper {
public:
    using type = std::conditional_t<std::is_const_v<std::remove_reference_t<Cont>>,
                                    typename std::decay_t<Cont>::const_iterator, typename std::decay_t<Cont>::iterator>;
};

template <typename T>
class IteratorHelper<T *> {
public:
    using type = T *;
};

template <typename T, std::size_t N>
class IteratorHelper<T[N]> {
public:
    using type = T *;
};

template <typename T, std::size_t N>
class IteratorHelper<T (&)[N]> {
public:
    using type = T *;
};

template <typename Cont>
using Iterator = typename IteratorHelper<Cont>::type;

template <typename Iter>
using DereferIterator = typename std::iterator_traits<Iter>::reference;

template <typename Iter>
constexpr bool IS_CONST_ITERATOR = std::is_const_v<std::remove_reference_t<DereferIterator<Iter>>>;

template <typename Iter>
constexpr bool IS_BIDIR_ITERATOR =
    std::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>;

template <typename Cont, typename = void>
class HasSize : public std::false_type {};

template <typename Cont>
class HasSize<Cont, std::void_t<decltype(std::declval<Cont>().size())>> : public std::true_type {};

template <typename Cont>
constexpr auto size(const Cont &cont) {
    if constexpr (HasSize<Cont>::value) {
        return cont.size();
    } else {
        return std::distance(std::begin(cont), std::end(cont));
    }
}

template <typename Cont, typename = void>
class SizeTypeHelper {
public:
    using type = std::size_t;
};

template <typename Cont>
class SizeTypeHelper<Cont, std::void_t<typename Cont::size_type>> {
public:
    using type = typename Cont::size_type;
};

template <typename Cont>
using SizeType = typename SizeTypeHelper<Cont>::type;

}  // namespace internal

}  // namespace range_tools

#endif
