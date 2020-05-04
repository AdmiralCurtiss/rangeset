#include <gtest/gtest.h>

#include <array>
#include <cstdint>

#include "rangesizeset.h"

TEST(TypesSizeTest, VoidPointer) {
  HyoutaUtilities::RangeSizeSet<void*> rs;
  std::array<uint32_t, 20> arr;
  rs.insert(&arr[7], &arr[8]);
  rs.insert(&arr[0], &arr[2]);
  rs.insert(&arr[15], &arr[19]);
  rs.insert(&arr[11], &arr[14]);

  auto it = rs.begin();
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[0]);
  ASSERT_TRUE(it.to() == &arr[2]);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[7]);
  ASSERT_TRUE(it.to() == &arr[8]);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[11]);
  ASSERT_TRUE(it.to() == &arr[14]);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[15]);
  ASSERT_TRUE(it.to() == &arr[19]);
  ++it;
  ASSERT_TRUE(it == rs.end());

  auto sit = rs.by_size_begin();
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[15]);
  ASSERT_TRUE(sit.to() == &arr[19]);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[11]);
  ASSERT_TRUE(sit.to() == &arr[14]);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[0]);
  ASSERT_TRUE(sit.to() == &arr[2]);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[7]);
  ASSERT_TRUE(sit.to() == &arr[8]);
  ++sit;
  ASSERT_TRUE(sit == rs.by_size_end());

  return;
}

TEST(TypesSizeTest, IntPointer) {
  HyoutaUtilities::RangeSizeSet<int*> rs;
  std::array<int, 20> arr;
  rs.insert(&arr[7], &arr[8]);
  rs.insert(&arr[0], &arr[2]);
  rs.insert(&arr[15], &arr[19]);
  rs.insert(&arr[11], &arr[14]);

  auto it = rs.begin();
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[0]);
  ASSERT_TRUE(it.to() == &arr[2]);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[7]);
  ASSERT_TRUE(it.to() == &arr[8]);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[11]);
  ASSERT_TRUE(it.to() == &arr[14]);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == &arr[15]);
  ASSERT_TRUE(it.to() == &arr[19]);
  ++it;
  ASSERT_TRUE(it == rs.end());

  auto sit = rs.by_size_begin();
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[15]);
  ASSERT_TRUE(sit.to() == &arr[19]);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[11]);
  ASSERT_TRUE(sit.to() == &arr[14]);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[0]);
  ASSERT_TRUE(sit.to() == &arr[2]);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == &arr[7]);
  ASSERT_TRUE(sit.to() == &arr[8]);
  ++sit;
  ASSERT_TRUE(sit == rs.by_size_end());

  return;
}

TEST(TypesSizeTest, Int8) {
  HyoutaUtilities::RangeSizeSet<int8_t> rs;
  rs.insert(-121, -118);
  rs.insert(-117, -115);
  rs.insert(-110, 118);
  rs.insert(120, 127);
  rs.insert(-128, -123);

  auto it = rs.begin();
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == -128);
  ASSERT_TRUE(it.to() == -123);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == -121);
  ASSERT_TRUE(it.to() == -118);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == -117);
  ASSERT_TRUE(it.to() == -115);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == -110);
  ASSERT_TRUE(it.to() == 118);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == 120);
  ASSERT_TRUE(it.to() == 127);
  ++it;
  ASSERT_TRUE(it == rs.end());

  auto sit = rs.by_size_begin();
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == -110);
  ASSERT_TRUE(sit.to() == 118);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == 120);
  ASSERT_TRUE(sit.to() == 127);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == -128);
  ASSERT_TRUE(sit.to() == -123);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == -121);
  ASSERT_TRUE(sit.to() == -118);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == -117);
  ASSERT_TRUE(sit.to() == -115);
  ++sit;
  ASSERT_TRUE(sit == rs.by_size_end());

  return;
}

TEST(TypesSizeTest, Int64) {
  HyoutaUtilities::RangeSizeSet<int64_t> rs;
  rs.insert(9223372000000000050, 9223372000000000090);
  rs.insert(-9223372036854775808, 9223372000000000000);
  rs.insert(9223372000000019000, 9223372000000020000);
  rs.insert(9223372000000000100, 9223372000000000200);

  auto it = rs.begin();
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == -9223372036854775808);
  ASSERT_TRUE(it.to() == 9223372000000000000);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == 9223372000000000050);
  ASSERT_TRUE(it.to() == 9223372000000000090);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == 9223372000000000100);
  ASSERT_TRUE(it.to() == 9223372000000000200);
  ++it;
  ASSERT_TRUE(it != rs.end());
  ASSERT_TRUE(it.from() == 9223372000000019000);
  ASSERT_TRUE(it.to() == 9223372000000020000);
  ++it;
  ASSERT_TRUE(it == rs.end());

  auto sit = rs.by_size_begin();
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == -9223372036854775808);
  ASSERT_TRUE(sit.to() == 9223372000000000000);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == 9223372000000019000);
  ASSERT_TRUE(sit.to() == 9223372000000020000);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == 9223372000000000100);
  ASSERT_TRUE(sit.to() == 9223372000000000200);
  ++sit;
  ASSERT_TRUE(sit != rs.by_size_end());
  ASSERT_TRUE(sit.from() == 9223372000000000050);
  ASSERT_TRUE(sit.to() == 9223372000000000090);
  ++sit;
  ASSERT_TRUE(sit == rs.by_size_end());

  return;
}
