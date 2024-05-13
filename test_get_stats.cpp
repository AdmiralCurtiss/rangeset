#include <gtest/gtest.h>

#include "rangeset.h"
#include "rangesizeset.h"

TEST(GetStatsTest, RangeSet) {
  HyoutaUtilities::RangeSet<std::size_t> rs;
  rs.insert(0, 100);

  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{100}, 0.0}));
  rs.erase(10, 20);
  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{90}, 10.0 / 90}));
  rs.erase(40, 50);
  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{80}, (10.0 + 20.0) / 80}));
  rs.erase(20, 40);
  rs.erase(0, 10);
  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{50}, 0.0}));
}

TEST(GetStatsTest, RangeSizeSet) {
  HyoutaUtilities::RangeSizeSet<std::size_t> rs;
  rs.insert(0, 100);

  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{100}, 0.0}));
  rs.erase(10, 20);
  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{90}, 10.0 / 90}));
  rs.erase(40, 50);
  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{80}, (10.0 + 20.0) / 80}));
  rs.erase(20, 40);
  rs.erase(0, 10);
  ASSERT_TRUE((rs.get_stats() == std::pair{std::size_t{50}, 0.0}));
}
