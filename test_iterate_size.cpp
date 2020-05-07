#include <gtest/gtest.h>

#include "rangesizeset.h"

static void setup(HyoutaUtilities::RangeSizeSet<size_t>& rs) {
  ASSERT_TRUE(rs.size() == 0);
  rs.insert(100, 180);
  ASSERT_TRUE(rs.size() == 1);
  rs.insert(900, 960);
  ASSERT_TRUE(rs.size() == 2);
  rs.insert(500, 570);
  ASSERT_TRUE(rs.size() == 3);
  rs.insert(700, 750);
  ASSERT_TRUE(rs.size() == 4);
  rs.insert(300, 390);
  ASSERT_TRUE(rs.size() == 5);
}

TEST(IterateSizeTest, ForwardIterationFromBegin) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.begin();
  ASSERT_TRUE(it.from() == 100);
  ASSERT_TRUE(it.to() == 180);
  ++it;
  ASSERT_TRUE(it.from() == 300);
  ASSERT_TRUE(it.to() == 390);
  ++it;
  ASSERT_TRUE(it.from() == 500);
  ASSERT_TRUE(it.to() == 570);
  ++it;
  ASSERT_TRUE(it.from() == 700);
  ASSERT_TRUE(it.to() == 750);
  ++it;
  ASSERT_TRUE(it.from() == 900);
  ASSERT_TRUE(it.to() == 960);
  ++it;
  ASSERT_TRUE(it == rs.end());
}

TEST(IterateSizeTest, BackwardIterationFromEnd) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.end();
  --it;
  ASSERT_TRUE(it.from() == 900);
  ASSERT_TRUE(it.to() == 960);
  --it;
  ASSERT_TRUE(it.from() == 700);
  ASSERT_TRUE(it.to() == 750);
  --it;
  ASSERT_TRUE(it.from() == 500);
  ASSERT_TRUE(it.to() == 570);
  --it;
  ASSERT_TRUE(it.from() == 300);
  ASSERT_TRUE(it.to() == 390);
  --it;
  ASSERT_TRUE(it.from() == 100);
  ASSERT_TRUE(it.to() == 180);
  ASSERT_TRUE(it == rs.begin());
}

TEST(IterateSizeTest, BySizeForwardIterationFromBegin) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.by_size_begin();
  ASSERT_TRUE(it.from() == 300);
  ASSERT_TRUE(it.to() == 390);
  ++it;
  ASSERT_TRUE(it.from() == 100);
  ASSERT_TRUE(it.to() == 180);
  ++it;
  ASSERT_TRUE(it.from() == 500);
  ASSERT_TRUE(it.to() == 570);
  ++it;
  ASSERT_TRUE(it.from() == 900);
  ASSERT_TRUE(it.to() == 960);
  ++it;
  ASSERT_TRUE(it.from() == 700);
  ASSERT_TRUE(it.to() == 750);
  ++it;
  ASSERT_TRUE(it == rs.by_size_end());
}

TEST(IterateSizeTest, BySizeBackwardIterationFromEnd) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto it = rs.by_size_end();
  --it;
  ASSERT_TRUE(it.from() == 700);
  ASSERT_TRUE(it.to() == 750);
  --it;
  ASSERT_TRUE(it.from() == 900);
  ASSERT_TRUE(it.to() == 960);
  --it;
  ASSERT_TRUE(it.from() == 500);
  ASSERT_TRUE(it.to() == 570);
  --it;
  ASSERT_TRUE(it.from() == 100);
  ASSERT_TRUE(it.to() == 180);
  --it;
  ASSERT_TRUE(it.from() == 300);
  ASSERT_TRUE(it.to() == 390);
  ASSERT_TRUE(it == rs.by_size_begin());
}

TEST(IterateSizeTest, IteratorConversion) {
  HyoutaUtilities::RangeSizeSet<size_t> rs;
  setup(rs);
  auto itR = rs.begin();
  auto itR100 = itR++;
  auto itR300 = itR++;
  auto itR500 = itR++;
  auto itR700 = itR++;
  auto itR900 = itR++;
  auto itS = rs.by_size_begin();
  auto itS300 = itS++;
  auto itS100 = itS++;
  auto itS500 = itS++;
  auto itS900 = itS++;
  auto itS700 = itS++;

  EXPECT_TRUE(itR100.to_size_iterator() == itS100);
  EXPECT_TRUE(itR300.to_size_iterator() == itS300);
  EXPECT_TRUE(itR500.to_size_iterator() == itS500);
  EXPECT_TRUE(itR700.to_size_iterator() == itS700);
  EXPECT_TRUE(itR900.to_size_iterator() == itS900);
  EXPECT_TRUE(itR100 == itS100.to_range_iterator());
  EXPECT_TRUE(itR300 == itS300.to_range_iterator());
  EXPECT_TRUE(itR500 == itS500.to_range_iterator());
  EXPECT_TRUE(itR700 == itS700.to_range_iterator());
  EXPECT_TRUE(itR900 == itS900.to_range_iterator());
}
