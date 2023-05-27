#ifndef RANGE_TOOLS_MAP_ADAPTOR_HPP
#define RANGE_TOOLS_MAP_ADAPTOR_HPP

#include <iterator>
#include <type_traits>

#include "util.hpp"

namespace range_tools {

namespace internal {

template <typename MapIter>
class MapValuesIterator {
public:
    using value_type = typename std::decay_t<DereferIterator<MapIter>>::second_type;
    using reference = std::conditional_t<IsConstIterator<MapIter>, const value_type &, value_type &>;

    MapValuesIterator(const MapIter &iter) : _iter(iter) {}

    MapValuesIterator &operator++() {
        ++_iter;
        return *this;
    }

    MapValuesIterator operator++(int) {
        auto tmp = *this;
        ++_iter;
        return tmp;
    }

    bool operator==(const MapValuesIterator &other) const {
        return _iter == other._iter;
    }

    bool operator!=(const MapValuesIterator &other) const {
        return _iter != other._iter;
    }

    reference operator*() const {
        return _iter->second;
    }

private:
    MapIter _iter;
};

template <typename Map>
class MapValues {
public:
    using iterator = MapValuesIterator<Iterator<Map>>;
    using reverse_iterator = MapValuesIterator<ReverseIterator<Map>>;

    MapValues(Map &&map) : _map(std::forward<Map>(map)) {}

    iterator begin() {
        return iterator(_map.begin());
    }

    iterator end() {
        return iterator(_map.end());
    }

    reverse_iterator rbegin() {
        return reverse_iterator(_map.rbegin());
    }

    reverse_iterator rend() {
        return reverse_iterator(_map.rend());
    }

private:
    Map _map;
};

}  // namespace internal

template <typename Map>
auto map_values(Map &&map) {
    return internal::MapValues<Map>(std::forward<Map>(map));
}

}  // namespace range_tools

#endif
