Implementation of a data structure to store ranges for C++.

I originally wrote this to have a quick way to query for large contiguous memory spaces in Dolphin.

`rangeset.h` is just a basic implementation using an std::map. Inserted and removed ranges are sorted and merged/split automatically. Start of the range is inclusive, end of the range is exclusive. Empty ranges are not allowed.

`rangesizeset.h` is the above, but also stores all ranges in a separate std::multimap using their size as the key, which can be iterated from the largest to the smallest range. The two maps are kept in sync automatically.
