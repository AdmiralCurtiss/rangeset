#pragma once

#include <cassert>
#include <map>
#include <type_traits>

namespace HyoutaUtilities {
// Like RangeSet, but additionally stores a map of the ranges sorted by their size, for quickly finding the largest or
// smallest range.
template <typename T> class RangeSizeSet {
private:
  // Key type used in the by-size multimap. Should be a type big enough to hold all possible distances between
  // possible 'from' and 'to'.
  // I'd actually love to just do
  // using SizeT = typename std::conditional<std::is_pointer_v<T>,
  //     std::size_t, typename std::make_unsigned<T>::type>::type;
  // but that's apparently not possible due to the std::make_unsigned<T>::type not existing for pointer types
  // so we'll work around this...
  template <typename U, bool IsPointer> struct GetSizeType { using S = typename std::make_unsigned<U>::type; };
  template <typename U> struct GetSizeType<U, true> { using S = std::size_t; };
  using SizeT = typename GetSizeType<T, std::is_pointer_v<T>>::S;

  // Value type stored in the regular range map.
  struct Value {
    // End point of the range.
    T To;

    // Pointer to the same range in the by-size multimap.
    typename std::multimap<SizeT, typename std::map<T, Value>::iterator, std::greater<SizeT>>::iterator SizeIt;

    Value(T to) : To(to) {}

    bool operator==(const Value& other) const {
      return this->To == other.To;
    }

    bool operator!=(const Value& other) const {
      return !operator==(other);
    }
  };

  using MapT = std::map<T, Value>;
  using SizeMapT = std::multimap<SizeT, typename MapT::iterator, std::greater<SizeT>>;

public:
  struct const_iterator {
  public:
    const T& from() const {
      return It->first;
    }

    const T& to() const {
      return It->second.To;
    }

    const_iterator& operator++() {
      ++It;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old = *this;
      ++It;
      return old;
    }

    const_iterator& operator--() {
      --It;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator old = *this;
      --It;
      return old;
    }

    bool operator==(const const_iterator& rhs) const {
      return this->It == rhs.It;
    }

    bool operator!=(const const_iterator& rhs) const {
      return !operator==(rhs);
    }

  private:
    typename MapT::const_iterator It;
    const_iterator(typename MapT::const_iterator it) : It(it) {}
    friend class RangeSizeSet;
  };

  struct by_size_const_iterator {
  public:
    const T& from() const {
      return It->second->first;
    }

    const T& to() const {
      return It->second->second.To;
    }

    by_size_const_iterator& operator++() {
      ++It;
      return *this;
    }

    by_size_const_iterator operator++(int) {
      by_size_const_iterator old = *this;
      ++It;
      return old;
    }

    by_size_const_iterator& operator--() {
      --It;
      return *this;
    }

    by_size_const_iterator operator--(int) {
      by_size_const_iterator old = *this;
      --It;
      return old;
    }

    bool operator==(const by_size_const_iterator& rhs) const {
      return this->It == rhs.It;
    }

    bool operator!=(const by_size_const_iterator& rhs) const {
      return !operator==(rhs);
    }

  private:
    typename SizeMapT::const_iterator It;
    by_size_const_iterator(typename SizeMapT::const_iterator it) : It(it) {}
    friend class RangeSizeSet;
  };

  // can't copy this class cause we store iterators
  RangeSizeSet() = default;
  RangeSizeSet(const RangeSizeSet<T>&) = delete;
  RangeSizeSet(RangeSizeSet<T>&&) = default;
  RangeSizeSet<T>& operator=(const RangeSizeSet<T>&) = delete;
  RangeSizeSet<T>& operator=(RangeSizeSet<T>&&) = default;

  void insert(T from, T to) {
    if (from >= to)
      return;

    // find the closest range
    // this will return the closest range whose starting position is greater
    // than 'from'
    auto bound = Map.upper_bound(from);
    if (bound == Map.end()) {
      // there is no range that starts greater than the given one
      // this means we have three options:
      // - no range exists yet, this is the first range
      if (Map.empty()) {
        insert_range(from, to);
        return;
      }

      // - the given range does not overlap the last range
      --bound;
      if (from > get_to(bound)) {
        insert_range(from, to);
        return;
      }

      // - the given range does overlap the last range
      maybe_expand_to(bound, to);
      return;
    }

    if (bound == Map.begin()) {
      // given range starts before any of the existing ones
      // must insert this as a new range as we can't modify a key in a
      // std::map...
      auto inserted = insert_range(from, to);
      merge_from_iterator_to_value(inserted, bound, to);
      return;
    }

    auto abound = bound--;

    // bound now points at the first range in the map that could possibly be
    // affected

    // if bound overlaps with given range, update bounds object
    if (get_to(bound) >= from) {
      maybe_expand_to(bound, to);
      auto inserted = bound;
      ++bound;
      merge_from_iterator_to_value(inserted, bound, to);
      return;
    }

    // bound *doesn't* overlap with given range, check next range

    // if this range overlaps with given range
    if (get_from(abound) <= to) {
      // insert new range
      auto inserted = insert_range(from, to >= get_to(abound) ? to : get_to(abound));
      // and delete overlaps
      abound = erase_range(abound);
      merge_from_iterator_to_value(inserted, abound, to);
      return;
    }

    // if we come here then this new range overlaps nothing and must be inserted
    // as a new range
    insert_range(from, to);
  }

  void erase(T from, T to) {
    if (from >= to)
      return;

    // like insert, we use upper_bound to find the closest range
    auto bound = Map.upper_bound(from);
    if (bound == Map.end()) {
      // there is no range that starts greater than the given one
      if (Map.empty()) {
        // nothing to do
        return;
      }
      --bound;
      // bound now points at the last range
      if (from >= get_to(bound)) {
        // given range is larger than any that exists, nothing to do
        return;
      }

      if (to >= get_to(bound)) {
        if (from == get_from(bound)) {
          // given range fully overlaps last range, erase it
          erase_range(bound);
          return;
        } else {
          // given range overlaps end of last range, reduce it
          reduce_to(bound, from);
          return;
        }
      }

      if (from == get_from(bound)) {
        // given range overlaps begin of last range, reduce it
        reduce_from(bound, to);
        return;
      } else {
        // given range overlaps middle of last range, bisect it
        bisect_range(bound, from, to);
        return;
      }
    }

    if (bound == Map.begin()) {
      // if we found the first range that means 'from' is before any stored range
      // this means we can just erase from start until 'to' and be done with it
      erase_from_iterator_to_value(bound, to);
      return;
    }

    // check previous range
    auto abound = bound--;

    if (from == get_from(bound)) {
      // similarly, if the previous range starts with the given one, just erase until 'to'
      erase_from_iterator_to_value(bound, to);
      return;
    }

    // if we come here, the given range may or may not overlap part of the current 'bound'
    // (but never the full range), which means we may need to update the end position of it,
    // or possibly even split it into two
    if (from < get_to(bound)) {
      if (to < get_to(bound)) {
        // need to split in two
        bisect_range(bound, from, to);
        return;
      } else {
        // just update end
        reduce_to(bound, from);
      }
    }

    // and then just erase until to
    erase_from_iterator_to_value(abound, to);
    return;
  }

  const_iterator erase(const_iterator it) {
    return const_iterator(erase_range(it.It));
  }

  void clear() {
    Map.clear();
    Sizes.clear();
  }

  bool contains(T value) const {
    auto it = Map.upper_bound(value);
    if (it == Map.begin())
      return false;
    --it;
    return get_from(it) <= value && value < get_to(it);
  }

  size_t size() const {
    return Map.size();
  }

  bool empty() const {
    return Map.empty();
  }

  const_iterator begin() const {
    return const_iterator(Map.begin());
  }

  const_iterator end() const {
    return const_iterator(Map.end());
  }

  const_iterator cbegin() const {
    return const_iterator(Map.cbegin());
  }

  const_iterator cend() const {
    return const_iterator(Map.cend());
  }

  by_size_const_iterator by_size_begin() const {
    return by_size_const_iterator(Sizes.begin());
  }

  by_size_const_iterator by_size_end() const {
    return by_size_const_iterator(Sizes.end());
  }

  by_size_const_iterator by_size_cbegin() const {
    return by_size_const_iterator(Sizes.cbegin());
  }

  by_size_const_iterator by_size_cend() const {
    return by_size_const_iterator(Sizes.cend());
  }

  bool operator==(const RangeSizeSet<T>& other) const {
    return this->Map == other.Map;
  }

  bool operator!=(const RangeSizeSet<T>& other) const {
    return !(*this == other);
  }

private:
  static SizeT calc_size(T from, T to) {
    if constexpr (std::is_pointer_v<T>) {
      // for pointers we don't want pointer arithmetic here, else void* breaks
      static_assert(sizeof(T) <= sizeof(SizeT));
      return reinterpret_cast<SizeT>(to) - reinterpret_cast<SizeT>(from);
    } else {
      return static_cast<SizeT>(to - from);
    }
  }

  // Assumptions that can be made about the data:
  // - Range are stored in the form [from, to[
  //   That is, the starting value is inclusive, and the end value is exclusive.
  // - 'from' is the map key, 'to' is the map value
  // - 'from' is always smaller than 'to'
  // - Stored ranges never touch.
  // - Stored ranges never overlap.
  MapT Map;

  // The by-size multimap.
  // Key is the size of the range.
  // Value is a pointer to the range in the regular range map.
  // We use std::greater so that Sizes.begin() gives us the largest range.
  SizeMapT Sizes;

  T get_from(typename MapT::iterator it) const {
    return it->first;
  }

  T get_to(typename MapT::iterator it) const {
    return it->second.To;
  }

  T get_from(typename MapT::const_iterator it) const {
    return it->first;
  }

  T get_to(typename MapT::const_iterator it) const {
    return it->second.To;
  }

  typename MapT::iterator insert_range(T from, T to) {
    auto m = Map.emplace(from, to).first;
    m->second.SizeIt = Sizes.emplace(calc_size(from, to), m);
    return m;
  }

  typename MapT::iterator erase_range(typename MapT::iterator it) {
    Sizes.erase(it->second.SizeIt);
    return Map.erase(it);
  }

  typename MapT::const_iterator erase_range(typename MapT::const_iterator it) {
    Sizes.erase(it->second.SizeIt);
    return Map.erase(it);
  }

  void bisect_range(typename MapT::iterator it, T from, T to) {
    assert(get_from(it) < from);
    assert(get_from(it) < to);
    assert(get_to(it) > from);
    assert(get_to(it) > to);
    assert(from < to);
    T itto = get_to(it);
    reduce_to(it, from);
    insert_range(to, itto);
  }

  typename MapT::iterator reduce_from(typename MapT::iterator it, T from) {
    assert(get_from(it) < from);
    T itto = get_to(it);
    erase_range(it);
    return insert_range(from, itto);
  }

  void maybe_expand_to(typename MapT::iterator it, T to) {
    if (to <= get_to(it))
      return;

    expand_to(it, to);
  }

  void expand_to(typename MapT::iterator it, T to) {
    assert(get_to(it) < to);
    it->second.To = to;
    Sizes.erase(it->second.SizeIt);
    it->second.SizeIt = Sizes.emplace(calc_size(get_from(it), to), it);
  }

  void reduce_to(typename MapT::iterator it, T to) {
    assert(get_to(it) > to);
    it->second.To = to;
    Sizes.erase(it->second.SizeIt);
    it->second.SizeIt = Sizes.emplace(calc_size(get_from(it), to), it);
  }

  void merge_from_iterator_to_value(typename MapT::iterator inserted, typename MapT::iterator bound, T to) {
    // erase all ranges that overlap the inserted while updating the upper end
    while (bound != Map.end() && get_from(bound) <= to) {
      maybe_expand_to(inserted, get_to(bound));
      bound = erase_range(bound);
    }
  }

  void erase_from_iterator_to_value(typename MapT::iterator bound, T to) {
    // assumption: given bound starts at or after the 'from' value of the range to erase
    while (true) {
      // given range starts before stored range
      if (to <= get_from(bound)) {
        // range ends before this range too, nothing to do
        return;
      }

      if (to < get_to(bound)) {
        // range ends in the middle of current range
        reduce_from(bound, to);
        return;
      }

      if (to == get_to(bound)) {
        // range ends exactly with current range
        erase_range(bound);
        return;
      }

      // range ends later than current range, need to check the range(s) after this one too
      bound = erase_range(bound);
      if (bound == Map.end()) {
        return;
      }
    }
  }
};
} // namespace HyoutaUtilities
