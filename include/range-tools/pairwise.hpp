#ifndef RANGE_TOOLS_PAIRWISE_HPP
#define RANGE_TOOLS_PAIRWISE_HPP

#include <iterator>
#include <tuple>

namespace range_tools {

namespace internal {

template <typename Iter>
class PairwiseIterator {
public:
    using value_type = std::tuple<typename std::decay_t<Iter>::reference, typename std::decay_t<Iter>::reference>;
    using reference = value_type;

    PairwiseIterator(const Iter &iter1, const Iter &iter2) : _iter1(iter1), _iter2(iter2) {}

    PairwiseIterator &operator++() {
        ++_iter1;
        ++_iter2;
        return *this;
    }

    PairwiseIterator operator++(int) {
        auto tmp = *this;
        ++_iter1;
        ++_iter2;
        return tmp;
    }

    PairwiseIterator &operator--() {
        --_iter1;
        --_iter2;
        return *this;
    }

    PairwiseIterator operator--(int) {
        auto tmp = *this;
        --_iter1;
        --_iter2;
        return tmp;
    }

    bool operator==(const PairwiseIterator<Iter> &other) const {
        return _iter1 == other._iter1 && _iter2 == other._iter2;
    }

    bool operator!=(const PairwiseIterator<Iter> &other) const {
        return _iter1 != other._iter1 || _iter2 != other._iter2;
    }

    reference operator*() const {
        return reference(*_iter1, *_iter2);
    }

private:
    Iter _iter1, _iter2;
};

template <typename Base>
class Pairwise {
public:
    using iterator = PairwiseIterator<Iterator<Base>>;
    using const_iterator = PairwiseIterator<Iterator<const Base>>;
    using reverse_iterator = PairwiseIterator<ReverseIterator<Base>>;
    using const_reverse_iterator = PairwiseIterator<ReverseIterator<const Base>>;

    Pairwise(Base &&base) : _base(std::forward<Base>(base)) {}

    iterator begin(void) {
        auto iter1 = _base.begin(), iter2 = _base.begin();
        if (iter2 != _base.end()) {
            ++iter2;
        }
        return iterator(iter1, iter2);
    }

    iterator end(void) {
        auto iter1 = _base.end(), iter2 = _base.end();
        if (iter1 != _base.begin()) {
            --iter1;
        }
        return iterator(iter1, iter2);
    }

    reverse_iterator rbegin(void) {
        auto iter1 = _base.rbegin(), iter2 = _base.rbegin();
        if (iter1 != _base.rend()) {
            ++iter1;
        }
        return reverse_iterator(iter1, iter2);
    }

    reverse_iterator rend(void) {
        auto iter1 = _base.rend(), iter2 = _base.rend();
        if (iter2 != _base.rbegin()) {
            --iter2;
        }
        return reverse_iterator(iter1, iter2);
    }

private:
    Base _base;
};

}  // namespace internal

template <typename Base>
auto pairwise(Base &&base) {
    return internal::Pairwise<Base>(std::forward<Base>(base));
}

}  // namespace range_tools

#endif
