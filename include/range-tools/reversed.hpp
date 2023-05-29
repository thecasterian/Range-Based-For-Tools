#ifndef RANGE_TOOLS_REVERSED_HPP
#define RANGE_TOOLS_REVERSED_HPP

#include "util.hpp"

namespace range_tools {

namespace internal {

template <typename Cont>
class Reversed {
public:
    using iterator = std::reverse_iterator<Iterator<Cont>>;
    using const_iterator = std::reverse_iterator<Iterator<const Cont>>;
    using reverse_iterator = Iterator<Cont>;
    using const_reverse_iterator = Iterator<const Cont>;

    Reversed(Cont &&base) : _cont(std::forward<Cont>(base)) {}

    iterator begin(void) {
        return iterator(_cont.rbegin());
    }

    iterator end(void) {
        return iterator(_cont.rend());
    }

    reverse_iterator rbegin(void) {
        return reverse_iterator(_cont.begin());
    }

    reverse_iterator rend(void) {
        return reverse_iterator(_cont.end());
    }

private:
    Cont _cont;
};

}

template <typename Cont>
internal::Reversed<Cont> reversed(Cont &&base) {
    return internal::Reversed<Cont>(std::forward<Cont>(base));
}

}

#endif
