#include <FastBVH/impl/Config.h>

#include <gtest/gtest.h>

using namespace FastBVH;

TEST(Clz, NaiveClz32) {
  EXPECT_EQ(naiveClz(uint32_t(0x01ffffff)), 7);
  EXPECT_EQ(naiveClz(uint32_t(1)), 31);
  EXPECT_EQ(naiveClz(uint32_t(0)), 31);
}

TEST(Clz, NaiveClz64) {
  EXPECT_EQ(naiveClz(uint64_t(0x373101f0f1f0f4ff)), 2);
  EXPECT_EQ(naiveClz(uint64_t(0x01ffffff)), 39);
  EXPECT_EQ(naiveClz(uint64_t(1)), 63);
  EXPECT_EQ(naiveClz(uint64_t(0)), 63);
}

TEST(Clz, Clz32) {
  EXPECT_EQ(clz(uint32_t(0x01ffffff)), 7);
  EXPECT_EQ(clz(uint32_t(1)), 31);
  EXPECT_EQ(clz(uint32_t(0)), 31);
}

TEST(Clz, Clz64) {
  EXPECT_EQ(clz(uint64_t(0x373101f0f1f0f4ff)), 2);
  EXPECT_EQ(clz(uint64_t(0x01ffffff)), 39);
  EXPECT_EQ(clz(uint64_t(1)), 63);
  EXPECT_EQ(clz(uint64_t(0)), 63);
}
