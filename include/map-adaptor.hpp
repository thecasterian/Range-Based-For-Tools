#ifndef RANGE_TOOLS_MAP_ADAPTOR_HPP
#define RANGE_TOOLS_MAP_ADAPTOR_HPP

#include <iterator>

namespace range_tools {

namespace internal {

template <typename Map>
class MapKeysConstIterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename Map::key_type;
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type *;
    using reference = const value_type &;

    typename Map::const_iterator it;

    MapKeysConstIterator(const typename Map::const_iterator &it) : it(it) {}
    MapKeysConstIterator(const MapKeysConstIterator<Map> &) = default;
    MapKeysConstIterator(MapKeysConstIterator<Map> &&) = default;

    MapKeysConstIterator &operator++() {
        ++it;
        return *this;
    }

    MapKeysConstIterator operator++(int) {
        MapKeysConstIterator tmp(*this);
        ++it;
        return tmp;
    }

    bool operator==(const MapKeysConstIterator<Map> &other) const {
        return it == other.it;
    }

    bool operator!=(const MapKeysConstIterator<Map> &other) const {
        return it != other.it;
    }

    reference operator*() const {
        return it->first;
    }

    pointer operator->() const {
        return &it->first;
    }
};

template <typename Map>
class MapKeys {
public:
    using iterator = MapKeysConstIterator<Map>;
    using const_iterator = MapKeysConstIterator<Map>;

    const Map &map;

    MapKeys(const Map &map) : map(map) {}

    iterator begin() const {
        return iterator(map.begin());
    }

    iterator end() const {
        return iterator(map.end());
    }
};

template <typename Map>
class MapValuesIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename Map::mapped_type;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    typename Map::iterator it;

    MapValuesIterator(const typename Map::iterator &it) : it(it) {}
    MapValuesIterator(const MapValuesIterator<Map> &) = default;
    MapValuesIterator(MapValuesIterator<Map> &&) = default;

    MapValuesIterator &operator++() {
        ++it;
        return *this;
    }

    MapValuesIterator operator++(int) {
        MapValuesIterator tmp(*this);
        ++it;
        return tmp;
    }

    bool operator==(const MapValuesIterator<Map> &rhs) const {
        return it == rhs.it;
    }

    bool operator!=(const MapValuesIterator<Map> &rhs) const {
        return it != rhs.it;
    }

    reference operator*() const {
        return it->second;
    }

    pointer operator->() const {
        return &it->second;
    }
};

template <typename Map>
class MapValuesConstIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename Map::mapped_type;
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type *;
    using reference = const value_type &;

    typename Map::const_iterator it;

    MapValuesConstIterator(const typename Map::const_iterator &it) : it(it) {}
    MapValuesConstIterator(const MapValuesConstIterator<Map> &) = default;
    MapValuesConstIterator(MapValuesConstIterator<Map> &&) = default;

    MapValuesConstIterator &operator++() {
        ++it;
        return *this;
    }

    MapValuesConstIterator operator++(int) {
        MapValuesConstIterator tmp(*this);
        ++it;
        return tmp;
    }

    bool operator==(const MapValuesConstIterator<Map> &rhs) const {
        return it == rhs.it;
    }

    bool operator!=(const MapValuesConstIterator<Map> &rhs) const {
        return it != rhs.it;
    }

    reference operator*() const {
        return it->second;
    }

    pointer operator->() const {
        return &it->second;
    }
};

template <typename Map>
class MapValues {
public:
    Map &map;

    using iterator = MapValuesIterator<Map>;
    using const_iterator = MapValuesConstIterator<Map>;

    MapValues(Map &map) : map(map) {}

    iterator begin() const {
        return iterator(map.begin());
    }

    iterator end() const {
        return iterator(map.end());
    }
};

template <typename Map>
class MapValuesConst {
public:
    const Map &map;

    using iterator = MapValuesConstIterator<Map>;
    using const_iterator = MapValuesConstIterator<Map>;

    MapValuesConst(const Map &map) : map(map) {}

    iterator begin() const {
        return iterator(map.begin());
    }

    iterator end() const {
        return iterator(map.end());
    }
};

}  // namespace internal

template <typename Map>
internal::MapKeys<Map> map_keys(const Map &map) {
    return internal::MapKeys<Map>(map);
}

template <typename Map>
internal::MapValues<Map> map_values(Map &map) {
    return internal::MapValues<Map>(map);
}

template <typename Map>
internal::MapValuesConst<Map> map_values(const Map &map) {
    return internal::MapValuesConst<Map>(map);
}

}  // namespace range_tools

#endif
