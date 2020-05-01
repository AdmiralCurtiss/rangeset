#include <cassert>
#include <map>

namespace HyoutaUtilities {
template <typename T> class RangeSet {
public:
  struct const_iterator {
  public:
    const T& from() const {
      return it->first;
    }

    const T& to() const {
      return it->second;
    }

    const_iterator& operator++() {
      ++it;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old = *this;
      ++it;
      return old;
    }

    const_iterator& operator--() {
      --it;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator old = *this;
      --it;
      return old;
    }

    bool operator==(const const_iterator& rhs) const {
      return this->it == rhs.it;
    }

    bool operator!=(const const_iterator& rhs) const {
      return this->it != rhs.it;
    }

  private:
    typename std::map<T, T>::const_iterator it;
    const_iterator(typename std::map<T, T>::const_iterator it) : it(it) {}
    friend class RangeSet;
  };

  void insert(T from, T to) {
    if (!(from < to))
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
    if (!(from < to))
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
      } else {
        // just update end
        reduce_to(bound, from);
      }
    }

    // and then just erase until to
    erase_from_iterator_to_value(abound, to);
    return;
  }

  void clear() {
    Map.clear();
  }

  size_t size() const {
    return Map.size();
  }

  const_iterator begin() const {
    return const_iterator(Map.begin());
  }

  const_iterator end() const {
    return const_iterator(Map.end());
  }

  bool operator==(const RangeSet<T>& other) const {
    return this->Map == other.Map;
  }

  bool operator!=(const RangeSet<T>& other) const {
    return !(*this == other);
  }

private:
  // Assumptions that can be made about the data:
  // - Range are stored in the form [from, to[
  //   That is, the starting value is inclusive, and the end value is exclusive.
  // - 'from' is the map key, 'to' is the map value
  // - 'from' is always smaller than 'to'
  // - Stored ranges never touch.
  // - Stored ranges never overlap.
  std::map<T, T> Map;

  T get_from(typename std::map<T, T>::iterator it) {
    return it->first;
  }

  T get_to(typename std::map<T, T>::iterator it) {
    return it->second;
  }

  typename std::map<T, T>::iterator insert_range(T from, T to) {
    return Map.emplace(from, to).first;
  }

  typename std::map<T, T>::iterator erase_range(typename std::map<T, T>::iterator it) {
    return Map.erase(it);
  }

  void bisect_range(typename std::map<T, T>::iterator it, T from, T to) {
    assert(get_from(it) < from);
    assert(get_from(it) < to);
    assert(get_to(it) > from);
    assert(get_to(it) > to);
    assert(from < to);
    T itto = get_to(it);
    reduce_to(it, from);
    insert_range(to, itto);
  }

  typename std::map<T, T>::iterator reduce_from(typename std::map<T, T>::iterator it, T from) {
    assert(get_from(it) < from);
    T itto = get_to(it);
    erase_range(it);
    return insert_range(from, itto);
  }

  void maybe_expand_to(typename std::map<T, T>::iterator it, T to) {
    if (to > get_to(it)) {
      expand_to(it, to);
    }
  }

  void expand_to(typename std::map<T, T>::iterator it, T to) {
    assert(get_to(it) < to);
    it->second = to;
  }

  void reduce_to(typename std::map<T, T>::iterator it, T to) {
    assert(get_to(it) > to);
    it->second = to;
  }

  void merge_from_iterator_to_value(typename std::map<T, T>::iterator inserted, typename std::map<T, T>::iterator bound,
                                    T to) {
    // erase all ranges that overlap the inserted while updating the upper end
    while (bound != Map.end() && get_from(bound) <= to) {
      maybe_expand_to(inserted, get_to(bound));
      bound = erase_range(bound);
    }
  }

  void erase_from_iterator_to_value(typename std::map<T, T>::iterator bound, T to) {
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
