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
