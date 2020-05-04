#include <gtest/gtest.h>

#include "rangeset.h"

static void setup(HyoutaUtilities::RangeSet<size_t>& rs) {
  rs.insert(10, 18);
  rs.insert(20, 29);
  rs.insert(30, 37);
  rs.insert(40, 41);
  rs.insert(50, 56);
  ASSERT_TRUE(rs.size() == 5);
}

TEST(ContainsTest, Tests) {
  HyoutaUtilities::RangeSet<size_t> rs;
  setup(rs);
  EXPECT_FALSE(rs.contains(0));
  EXPECT_FALSE(rs.contains(1));
  EXPECT_FALSE(rs.contains(2));
  EXPECT_FALSE(rs.contains(3));
  EXPECT_FALSE(rs.contains(4));
  EXPECT_FALSE(rs.contains(5));
  EXPECT_FALSE(rs.contains(6));
  EXPECT_FALSE(rs.contains(7));
  EXPECT_FALSE(rs.contains(8));
  EXPECT_FALSE(rs.contains(9));
  EXPECT_TRUE(rs.contains(10));
  EXPECT_TRUE(rs.contains(11));
  EXPECT_TRUE(rs.contains(12));
  EXPECT_TRUE(rs.contains(13));
  EXPECT_TRUE(rs.contains(14));
  EXPECT_TRUE(rs.contains(15));
  EXPECT_TRUE(rs.contains(16));
  EXPECT_TRUE(rs.contains(17));
  EXPECT_FALSE(rs.contains(18));
  EXPECT_FALSE(rs.contains(19));
  EXPECT_TRUE(rs.contains(20));
  EXPECT_TRUE(rs.contains(21));
  EXPECT_TRUE(rs.contains(22));
  EXPECT_TRUE(rs.contains(23));
  EXPECT_TRUE(rs.contains(24));
  EXPECT_TRUE(rs.contains(25));
  EXPECT_TRUE(rs.contains(26));
  EXPECT_TRUE(rs.contains(27));
  EXPECT_TRUE(rs.contains(28));
  EXPECT_FALSE(rs.contains(29));
  EXPECT_TRUE(rs.contains(30));
  EXPECT_TRUE(rs.contains(31));
  EXPECT_TRUE(rs.contains(32));
  EXPECT_TRUE(rs.contains(33));
  EXPECT_TRUE(rs.contains(34));
  EXPECT_TRUE(rs.contains(35));
  EXPECT_TRUE(rs.contains(36));
  EXPECT_FALSE(rs.contains(37));
  EXPECT_FALSE(rs.contains(38));
  EXPECT_FALSE(rs.contains(39));
  EXPECT_TRUE(rs.contains(40));
  EXPECT_FALSE(rs.contains(41));
  EXPECT_FALSE(rs.contains(42));
  EXPECT_FALSE(rs.contains(43));
  EXPECT_FALSE(rs.contains(44));
  EXPECT_FALSE(rs.contains(45));
  EXPECT_FALSE(rs.contains(46));
  EXPECT_FALSE(rs.contains(47));
  EXPECT_FALSE(rs.contains(48));
  EXPECT_FALSE(rs.contains(49));
  EXPECT_TRUE(rs.contains(50));
  EXPECT_TRUE(rs.contains(51));
  EXPECT_TRUE(rs.contains(52));
  EXPECT_TRUE(rs.contains(53));
  EXPECT_TRUE(rs.contains(54));
  EXPECT_TRUE(rs.contains(55));
  EXPECT_FALSE(rs.contains(56));
  EXPECT_FALSE(rs.contains(57));
  EXPECT_FALSE(rs.contains(58));
  EXPECT_FALSE(rs.contains(59));
  EXPECT_FALSE(rs.contains(60));
}
