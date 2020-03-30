#include <FastBVH.h>
#include <gtest/gtest.h>

#include <list>

#include "Primitive.h"

using namespace FastBVH;

namespace {

//! \brief This is just boilerplate code for google test
//! to be able to run template tests.
template <typename T>
class BuildStrategyTest : public ::testing::Test {
 public:
  using List = std::list<T>;
  static T shared_;
  T value_;
};

//! \brief The floating point types to be tested.
using FloatTypes = ::testing::Types<float, double, long double>;

}  // namespace

TYPED_TEST_CASE(BuildStrategyTest, FloatTypes);

TYPED_TEST(BuildStrategyTest, build) {
  Testing::Primitive<TypeParam> p[3] = {{{1, 2, 3}, {4, 5, 8}}, {{9, 8, 4}, {11, 15, 9}}, {{2, 6, 5}, {3, 7, 6}}};

  std::vector<Testing::Primitive<TypeParam>> primitives;
  primitives.emplace_back(p[0]);
  primitives.emplace_back(p[1]);
  primitives.emplace_back(p[2]);

  Testing::BoxConverter<TypeParam> box_converter;

  BuildStrategy<TypeParam, 0> build_strategy;

  auto bvh = build_strategy(primitives, box_converter);

  auto nodes = bvh.getNodes();

  constexpr TypeParam cmp_bias = 0.001;

  EXPECT_EQ(bvh.countLeafs(), 1);
  ASSERT_EQ(nodes.size(), 1);
  EXPECT_EQ(nodes[0].primitive_count, 3);
  EXPECT_NEAR(nodes[0].bbox.min.x, 1, cmp_bias);
  EXPECT_NEAR(nodes[0].bbox.min.y, 2, cmp_bias);
  EXPECT_NEAR(nodes[0].bbox.min.z, 3, cmp_bias);
  EXPECT_NEAR(nodes[0].bbox.max.x, 11, cmp_bias);
  EXPECT_NEAR(nodes[0].bbox.max.y, 15, cmp_bias);
  EXPECT_NEAR(nodes[0].bbox.max.z, 9, cmp_bias);
}
