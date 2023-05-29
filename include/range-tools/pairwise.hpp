#ifndef RANGE_TOOLS_PAIRWISE_HPP
#define RANGE_TOOLS_PAIRWISE_HPP

#include <iterator>
#include <tuple>

namespace range_tools {

namespace internal {

template <typename Iter>
class PairwiseIteratorBase {
public:
    using iterator_category = typename std::iterator_traits<Iter>::iterator_category;
    using value_type = std::tuple<std::decay_t<DereferIterator<Iter>>, std::decay_t<DereferIterator<Iter>>>;
    using difference_type = typename std::iterator_traits<Iter>::difference_type;
    using pointer = void;
    using reference = std::tuple<DereferIterator<Iter>, DereferIterator<Iter>>;

    PairwiseIteratorBase(const Iter &iter1, const Iter &iter2) : _iter1(iter1), _iter2(iter2) {}

    PairwiseIteratorBase<Iter> &operator++() {
        ++_iter1;
        ++_iter2;
        return *this;
    }

    PairwiseIteratorBase<Iter> operator++(int) {
        auto tmp = *this;
        ++_iter1;
        ++_iter2;
        return tmp;
    }

    bool operator==(const PairwiseIteratorBase<Iter> &other) const {
        return _iter1 == other._iter1 && _iter2 == other._iter2;
    }

    bool operator!=(const PairwiseIteratorBase<Iter> &other) const {
        return _iter1 != other._iter1 || _iter2 != other._iter2;
    }

    reference operator*() const {
        return reference(*_iter1, *_iter2);
    }

protected:
    Iter _iter1, _iter2;
};

template <typename Iter, typename = void>
class PairwiseIterator : public PairwiseIteratorBase<Iter> {
public:
    using PairwiseIteratorBase<Iter>::PairwiseIteratorBase;
};

template <typename Iter>
class PairwiseIterator<Iter, std::enable_if_t<IS_BIDIR_ITERATOR<Iter>>> : public PairwiseIteratorBase<Iter> {
public:
    using PairwiseIteratorBase<Iter>::PairwiseIteratorBase;

    PairwiseIterator<Iter> &operator--() {
        --_iter1;
        --_iter2;
        return *this;
    }

    PairwiseIterator<Iter> operator--(int) {
        auto tmp = *this;
        --_iter1;
        --_iter2;
        return tmp;
    }

private:
    using PairwiseIteratorBase<Iter>::_iter1;
    using PairwiseIteratorBase<Iter>::_iter2;
};

template <typename Cont>
class PairwiseBase {
public:
    using size_type = SizeType<Cont>;

    using iterator = PairwiseIterator<Iterator<Cont>>;
    using const_iterator = PairwiseIterator<Iterator<const Cont>>;

    PairwiseBase(Cont &&cont) : _cont(std::forward<Cont>(cont)) {}

    iterator begin(void) {
        auto iter1 = _cont.begin(), iter2 = _cont.begin();
        if (iter2 != _cont.end()) {
            ++iter2;
        }
        return iterator(iter1, iter2);
    }

    iterator end(void) {
        auto iter1 = _cont.end(), iter2 = _cont.end();
        if (iter1 != _cont.begin()) {
            auto size = internal::size(_cont);
            iter1 = _cont.begin();
            std::advance(iter1, size - 1);
        }
        return iterator(iter1, iter2);
    }

protected:
    Cont _cont;
};


template <typename Cont, typename = void>
class Pairwise : public PairwiseBase<Cont> {
public:
    using PairwiseBase<Cont>::PairwiseBase;
};

template <typename Cont>
class Pairwise<Cont, std::enable_if_t<IS_BIDIR_ITERATOR<Iterator<Cont>>>> : public PairwiseBase<Cont> {
public:
    using PairwiseBase<Cont>::PairwiseBase;
    using typename PairwiseBase<Cont>::iterator;
    using typename PairwiseBase<Cont>::const_iterator;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using PairwiseBase<Cont>::begin;

    iterator end(void) {
        auto iter1 = _cont.end(), iter2 = _cont.end();
        if (iter1 != _cont.begin()) {
            --iter1;
        }
        return iterator(iter1, iter2);
    }

    reverse_iterator rbegin(void) {
        return reverse_iterator(end());
    }

    reverse_iterator rend(void) {
        return reverse_iterator(begin());
    }

private:
    using PairwiseBase<Cont>::_cont;
};

}  // namespace internal

template <typename Cont>
auto pairwise(Cont &&cont) {
    return internal::Pairwise<Cont>(std::forward<Cont>(cont));
}

}  // namespace range_tools

#endif
