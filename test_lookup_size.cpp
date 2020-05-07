#include <gtest/gtest.h>

#include "rangesizeset.h"

static void setup(HyoutaUtilities::RangeSizeSet<size_t>& rs) {
  rs.insert(10, 18);
  rs.insert(20, 29);
  rs.insert(30, 36);
  rs.insert(40, 41);
  rs.insert(50, 56);
  ASSERT_TRUE(rs.size() == 5);
}

TEST(LookupSizeTest, BySizeCount) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  EXPECT_TRUE(rs.by_size_count(0) == 0);
  EXPECT_TRUE(rs.by_size_count(1) == 1);
  EXPECT_TRUE(rs.by_size_count(2) == 0);
  EXPECT_TRUE(rs.by_size_count(3) == 0);
  EXPECT_TRUE(rs.by_size_count(4) == 0);
  EXPECT_TRUE(rs.by_size_count(5) == 0);
  EXPECT_TRUE(rs.by_size_count(6) == 2);
  EXPECT_TRUE(rs.by_size_count(7) == 0);
  EXPECT_TRUE(rs.by_size_count(8) == 1);
  EXPECT_TRUE(rs.by_size_count(9) == 1);
  EXPECT_TRUE(rs.by_size_count(10) == 0);
}
TEST(LookupSizeTest, BySizeFind) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.by_size_begin();
  ASSERT_TRUE(it != rs.by_size_end());
  auto it9 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it8 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6a = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6b = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it1 = it++;
  ASSERT_TRUE(it == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_find(0) == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_find(1) == it1);
  EXPECT_TRUE(rs.by_size_find(2) == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_find(3) == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_find(4) == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_find(5) == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_find(6) == it6a || rs.by_size_find(6) == it6b);
  EXPECT_TRUE(rs.by_size_find(7) == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_find(8) == it8);
  EXPECT_TRUE(rs.by_size_find(9) == it9);
  EXPECT_TRUE(rs.by_size_find(10) == rs.by_size_end());
}
TEST(LookupSizeTest, BySizeEqualRange) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.by_size_begin();
  ASSERT_TRUE(it != rs.by_size_end());
  auto it9 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it8 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6a = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6b = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it1 = it++;
  ASSERT_TRUE(it == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_equal_range(10) == std::make_pair(rs.by_size_begin(), rs.by_size_begin()));
  EXPECT_TRUE(rs.by_size_equal_range(9) == std::make_pair(it9, it8));
  EXPECT_TRUE(rs.by_size_equal_range(8) == std::make_pair(it8, it6a));
  EXPECT_TRUE(rs.by_size_equal_range(7) == std::make_pair(it6a, it6a));
  EXPECT_TRUE(rs.by_size_equal_range(6) == std::make_pair(it6a, it1));
  EXPECT_TRUE(rs.by_size_equal_range(5) == std::make_pair(it1, it1));
  EXPECT_TRUE(rs.by_size_equal_range(4) == std::make_pair(it1, it1));
  EXPECT_TRUE(rs.by_size_equal_range(3) == std::make_pair(it1, it1));
  EXPECT_TRUE(rs.by_size_equal_range(2) == std::make_pair(it1, it1));
  EXPECT_TRUE(rs.by_size_equal_range(1) == std::make_pair(it1, rs.by_size_end()));
  EXPECT_TRUE(rs.by_size_equal_range(0) == std::make_pair(rs.by_size_end(), rs.by_size_end()));
}
TEST(LookupSizeTest, BySizeLowerBound) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.by_size_begin();
  ASSERT_TRUE(it != rs.by_size_end());
  auto it9 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it8 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6a = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6b = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it1 = it++;
  ASSERT_TRUE(it == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_lower_bound(10) == rs.by_size_begin());
  EXPECT_TRUE(rs.by_size_lower_bound(9) == it9);
  EXPECT_TRUE(rs.by_size_lower_bound(8) == it8);
  EXPECT_TRUE(rs.by_size_lower_bound(7) == it6a);
  EXPECT_TRUE(rs.by_size_lower_bound(6) == it6a);
  EXPECT_TRUE(rs.by_size_lower_bound(5) == it1);
  EXPECT_TRUE(rs.by_size_lower_bound(4) == it1);
  EXPECT_TRUE(rs.by_size_lower_bound(3) == it1);
  EXPECT_TRUE(rs.by_size_lower_bound(2) == it1);
  EXPECT_TRUE(rs.by_size_lower_bound(1) == it1);
  EXPECT_TRUE(rs.by_size_lower_bound(0) == rs.by_size_end());
}
TEST(LookupSizeTest, BySizeUpperBound) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.by_size_begin();
  ASSERT_TRUE(it != rs.by_size_end());
  auto it9 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it8 = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6a = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it6b = it++;
  ASSERT_TRUE(it != rs.by_size_end());
  auto it1 = it++;
  ASSERT_TRUE(it == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_upper_bound(10) == it9);
  EXPECT_TRUE(rs.by_size_upper_bound(9) == it8);
  EXPECT_TRUE(rs.by_size_upper_bound(8) == it6a);
  EXPECT_TRUE(rs.by_size_upper_bound(7) == it6a);
  EXPECT_TRUE(rs.by_size_upper_bound(6) == it1);
  EXPECT_TRUE(rs.by_size_upper_bound(5) == it1);
  EXPECT_TRUE(rs.by_size_upper_bound(4) == it1);
  EXPECT_TRUE(rs.by_size_upper_bound(3) == it1);
  EXPECT_TRUE(rs.by_size_upper_bound(2) == it1);
  EXPECT_TRUE(rs.by_size_upper_bound(1) == rs.by_size_end());
  EXPECT_TRUE(rs.by_size_upper_bound(0) == rs.by_size_end());
}
