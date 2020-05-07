#include <gtest/gtest.h>

#include "rangeset.h"

TEST(SwapTest, Tests) {
  HyoutaUtilities::RangeSet<size_t> rs1;
  rs1.insert(10, 20);
  rs1.insert(30, 32);
  rs1.insert(45, 99);
  HyoutaUtilities::RangeSet<size_t> rs2;
  rs2.insert(20, 24);
  rs2.insert(70, 71);
  HyoutaUtilities::RangeSet<size_t> rs3;
  rs3.insert(10, 20);
  rs3.insert(30, 32);
  rs3.insert(45, 99);
  HyoutaUtilities::RangeSet<size_t> rs4;
  rs4.insert(20, 24);
  rs4.insert(70, 71);

  EXPECT_TRUE(rs1 != rs2);
  EXPECT_TRUE(rs1 == rs3);
  EXPECT_TRUE(rs1 != rs4);
  EXPECT_TRUE(rs2 != rs3);
  EXPECT_TRUE(rs2 == rs4);
  EXPECT_TRUE(rs3 != rs4);

  rs1.swap(rs2);

  EXPECT_TRUE(rs1 != rs2);
  EXPECT_TRUE(rs1 != rs3);
  EXPECT_TRUE(rs1 == rs4);
  EXPECT_TRUE(rs2 == rs3);
  EXPECT_TRUE(rs2 != rs4);
  EXPECT_TRUE(rs3 != rs4);
}
