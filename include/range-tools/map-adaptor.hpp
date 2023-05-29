#ifndef RANGE_TOOLS_MAP_ADAPTOR_HPP
#define RANGE_TOOLS_MAP_ADAPTOR_HPP

#include <iterator>
#include <type_traits>

#include "util.hpp"

namespace range_tools {

namespace internal {

template <typename MapIter>
class MapKeysIterator {
public:
    using iterator_category = typename std::iterator_traits<MapIter>::iterator_category;
    using value_type = typename std::decay_t<DereferIterator<MapIter>>::first_type;
    using difference_type = typename std::iterator_traits<MapIter>::difference_type;
    using pointer = const value_type *;
    using reference = const value_type &;

    MapKeysIterator(const MapIter &iter) : _iter(iter) {}

    MapKeysIterator<MapIter> &operator++() {
        ++_iter;
        return *this;
    }

    MapKeysIterator<MapIter> operator++(int) {
        auto tmp = *this;
        ++_iter;
        return tmp;
    }

    MapKeysIterator<MapIter> &operator--() {
        --_iter;
        return *this;
    }

    MapKeysIterator<MapIter> operator--(int) {
        auto tmp = *this;
        --_iter;
        return tmp;
    }

    bool operator==(const MapKeysIterator<MapIter> &other) const {
        return _iter == other._iter;
    }

    bool operator!=(const MapKeysIterator<MapIter> &other) const {
        return _iter != other._iter;
    }

    reference operator*() const {
        return _iter->first;
    }

    pointer operator->() const {
        return &_iter->first;
    }

private:
    MapIter _iter;
};

template <typename Map>
class MapKeys {
public:
    using iterator = MapKeysIterator<Iterator<Map>>;
    using const_iterator = MapKeysIterator<Iterator<const Map>>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    MapKeys(Map &&map) : _map(std::forward<Map>(map)) {}

    iterator begin(void) {
        return iterator(_map.begin());
    }

    iterator end(void) {
        return iterator(_map.end());
    }

    reverse_iterator rbegin(void) {
        return reverse_iterator(_map.rbegin());
    }

    reverse_iterator rend(void) {
        return reverse_iterator(_map.rend());
    }

private:
    Map _map;
};

template <typename MapIter>
class MapValuesIterator {
public:
    using iterator_category = typename std::iterator_traits<MapIter>::iterator_category;
    using value_type = typename std::decay_t<DereferIterator<MapIter>>::second_type;
    using difference_type = typename std::iterator_traits<MapIter>::difference_type;
    using pointer = std::conditional_t<IS_CONST_ITERATOR<MapIter>, const value_type *, value_type *>;
    using reference = std::conditional_t<IS_CONST_ITERATOR<MapIter>, const value_type &, value_type &>;

    MapValuesIterator(const MapIter &iter) : _iter(iter) {}

    MapValuesIterator<MapIter> &operator++() {
        ++_iter;
        return *this;
    }

    MapValuesIterator<MapIter> operator++(int) {
        auto tmp = *this;
        ++_iter;
        return tmp;
    }

    MapValuesIterator<MapIter> &operator--() {
        --_iter;
        return *this;
    }

    MapValuesIterator<MapIter> operator--(int) {
        auto tmp = *this;
        --_iter;
        return tmp;
    }

    bool operator==(const MapValuesIterator<MapIter> &other) const {
        return _iter == other._iter;
    }

    bool operator!=(const MapValuesIterator<MapIter> &other) const {
        return _iter != other._iter;
    }

    reference operator*() const {
        return _iter->second;
    }

    pointer operator->() const {
        return &_iter->second;
    }

private:
    MapIter _iter;
};

template <typename Map>
class MapValues {
public:
    using iterator = MapValuesIterator<Iterator<Map>>;
    using const_iterator = MapValuesIterator<Iterator<const Map>>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    MapValues(Map &&map) : _map(std::forward<Map>(map)) {}

    iterator begin(void) {
        return iterator(_map.begin());
    }

    iterator end(void) {
        return iterator(_map.end());
    }

    reverse_iterator rbegin(void) {
        return reverse_iterator(_map.rbegin());
    }

    reverse_iterator rend(void) {
        return reverse_iterator(_map.rend());
    }

private:
    Map _map;
};

}  // namespace internal

template <typename Map>
auto map_keys(Map &&map) {
    return internal::MapKeys<Map>(std::forward<Map>(map));
}

template <typename Map>
auto map_values(Map &&map) {
    return internal::MapValues<Map>(std::forward<Map>(map));
}

}  // namespace range_tools

#endif
