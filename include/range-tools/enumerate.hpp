#ifndef RANGE_TOOLS_ENUMERATE_HPP
#define RANGE_TOOLS_ENUMERATE_HPP

#include <tuple>

#include "util.hpp"

namespace range_tools {

namespace internal {

template <typename Index, typename Iter>
class EnumerateIteratorBase {
public:
    using iterator_category = typename std::iterator_traits<Iter>::iterator_category;
    using value_type = std::tuple<Index, std::decay_t<DereferIterator<Iter>>>;
    using difference_type = typename std::iterator_traits<Iter>::difference_type;
    using pointer = void;
    using reference = std::tuple<Index, DereferIterator<Iter>>;

    EnumerateIteratorBase(Index index, const Iter &iter) : _index(index), _iter(iter) {}

    EnumerateIteratorBase<Index, Iter> &operator++() {
        ++_index;
        ++_iter;
        return *this;
    }

    EnumerateIteratorBase<Index, Iter> operator++(int) {
        auto tmp = *this;
        ++_index;
        ++_iter;
        return tmp;
    }

    bool operator==(const EnumerateIteratorBase<Index, Iter> &other) const {
        return _index == other._index && _iter == other._iter;
    }

    bool operator!=(const EnumerateIteratorBase<Index, Iter> &other) const {
        return _index != other._index || _iter != other._iter;
    }

    reference operator*() const {
        return reference(_index, *_iter);
    }

protected:
    Index _index;
    Iter _iter;
};

template <typename Index, typename Iter, typename = void>
class EnumerateIterator : public EnumerateIteratorBase<Index, Iter> {
public:
    using EnumerateIteratorBase<Index, Iter>::EnumerateIteratorBase;
};

template <typename Index, typename Iter>
class EnumerateIterator<Index, Iter, std::enable_if_t<IS_BIDIR_ITERATOR<Iter>>>
    : public EnumerateIteratorBase<Index, Iter> {
public:
    using EnumerateIteratorBase<Index, Iter>::EnumerateIteratorBase;

    EnumerateIterator<Index, Iter> &operator--() {
        --_index;
        --_iter;
        return *this;
    }

    EnumerateIterator<Index, Iter> operator--(int) {
        auto tmp = *this;
        --_index;
        --_iter;
        return tmp;
    }

private:
    using EnumerateIteratorBase<Index, Iter>::_index;
    using EnumerateIteratorBase<Index, Iter>::_iter;
};

template <typename Cont, typename Index>
class EnumerateBase {
public:
    using size_type = SizeType<Cont>;

    using iterator = EnumerateIterator<Index, Iterator<Cont>>;
    using const_iterator = EnumerateIterator<Index, Iterator<const Cont>>;

    EnumerateBase(Cont &&cont) : _cont(std::forward<Cont>(cont)) {}

    iterator begin(void) {
        return iterator(0, std::begin(_cont));
    }

    iterator end(void) {
        return iterator(internal::size(_cont), std::end(_cont));
    }

protected:
    Cont _cont;
};

template <typename Cont, typename Index, typename = void>
class Enumerate : public EnumerateBase<Cont, Index> {
public:
    using EnumerateBase<Cont, Index>::EnumerateBase;
};

template <typename Cont, typename Index>
class Enumerate<Cont, Index, std::enable_if_t<IS_BIDIR_ITERATOR<Iterator<Cont>>>> : public EnumerateBase<Cont, Index> {
public:
    using EnumerateBase<Cont, Index>::EnumerateBase;
    using typename EnumerateBase<Cont, Index>::iterator;
    using typename EnumerateBase<Cont, Index>::const_iterator;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using EnumerateBase<Cont, Index>::begin;
    using EnumerateBase<Cont, Index>::end;

    reverse_iterator rbegin(void) {
        return reverse_iterator(end());
    }

    reverse_iterator rend(void) {
        return reverse_iterator(begin());
    }
};

}  // namespace internal

template <typename Cont>
auto enumerate(Cont &&base) {
    return internal::Enumerate<Cont, internal::SizeType<Cont>>(std::forward<Cont>(base));
}

template <typename T>
auto enumerate(std::initializer_list<T> &&base) {
    return internal::Enumerate<std::initializer_list<T>, std::size_t>(std::forward<std::initializer_list<T>>(base));
}

}  // namespace range_tools

#endif
