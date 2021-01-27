#include <gtest/gtest.h>

#include "rangeset.h"

class IterateTest : public ::testing::Test {
public:
  HyoutaUtilities::RangeSet<std::size_t> rs;

  void SetUp() override {
    ASSERT_TRUE(rs.size() == 0);
    rs.insert(100, 200);
    ASSERT_TRUE(rs.size() == 1);
    rs.insert(900, 1000);
    ASSERT_TRUE(rs.size() == 2);
    rs.insert(500, 600);
    ASSERT_TRUE(rs.size() == 3);
    rs.insert(700, 800);
    ASSERT_TRUE(rs.size() == 4);
    rs.insert(300, 400);
    ASSERT_TRUE(rs.size() == 5);
  }
};

TEST_F(IterateTest, ForwardIterationFromBegin) {
  auto it = rs.begin();
  ASSERT_TRUE(it.from() == 100);
  ASSERT_TRUE(it.to() == 200);
  ++it;
  ASSERT_TRUE(it.from() == 300);
  ASSERT_TRUE(it.to() == 400);
  ++it;
  ASSERT_TRUE(it.from() == 500);
  ASSERT_TRUE(it.to() == 600);
  ++it;
  ASSERT_TRUE(it.from() == 700);
  ASSERT_TRUE(it.to() == 800);
  ++it;
  ASSERT_TRUE(it.from() == 900);
  ASSERT_TRUE(it.to() == 1000);
  ++it;
  ASSERT_TRUE(it == rs.end());
}

TEST_F(IterateTest, BackwardIterationFromEnd) {
  auto it = rs.end();
  --it;
  ASSERT_TRUE(it.from() == 900);
  ASSERT_TRUE(it.to() == 1000);
  --it;
  ASSERT_TRUE(it.from() == 700);
  ASSERT_TRUE(it.to() == 800);
  --it;
  ASSERT_TRUE(it.from() == 500);
  ASSERT_TRUE(it.to() == 600);
  --it;
  ASSERT_TRUE(it.from() == 300);
  ASSERT_TRUE(it.to() == 400);
  --it;
  ASSERT_TRUE(it.from() == 100);
  ASSERT_TRUE(it.to() == 200);
  ASSERT_TRUE(it == rs.begin());
}
