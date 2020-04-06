#include <FastBVH/impl/MortonCurve.h>

#include <gtest/gtest.h>

#include <list>

#include "Primitive.h"

using namespace FastBVH;
using namespace FastBVH::testing;

namespace {

//! \brief This is just boilerplate code for google test
//! to be able to run template tests.
template <typename T>
class MortonCurveTest : public ::testing::Test {
 public:
  using List = std::list<T>;
  static T shared_;
  T value_;
};

#ifndef FASTBVH_NO_INT128
//! \brief The floating point types to be tested, including 128-bit floats.
using FloatTypes = ::testing::Types<float, double, long double>;
#else
//! \brief The floating point types to be tested, not including 128-bit floats.
using FloatTypes = ::testing::Types<float, double>;
#endif

//! \brief this class, in its template
//! specializations, contains the expected
//! Morton codes for the test run.
template <Size float_size>
struct ExpectedCodes final {};

//! \brief Expected Morton codes for 32-bit float test.
template <>
struct ExpectedCodes<4> final {
  static constexpr U32 codes[3] = {
    0x0D349249,
    0x0360A6C8,
    0x36DB6DB6
  };
};

//! \brief Expected Morton codes for 64-bit float test.
template <>
struct ExpectedCodes<8> final {
  static constexpr U64 codes[3] = {
    0x1A6924934924D26D,
    0x06C14D9053409699,
    0x6DB6DB6DB6DB6DB6
  };
};

constexpr U32 ExpectedCodes<4>::codes[3];
constexpr U64 ExpectedCodes<8>::codes[3];

#ifndef FASTBVH_NO_INT128
//! \brief Expected Morton codes for 128-bit float test.
template <>
struct ExpectedCodes<16> final {
  static constexpr U128 codes[3] = {
    literal128U(0x0D349249A4926936ULL, 0x9249369B49A6934DULL),
    literal128U(0x0360A6C829A04B4CULL, 0x929A0024C02D2202ULL),
    literal128U(0x36DB6DB6DB6DB6DBULL, 0x6DB6DB6DB6DB6DB6ULL)
  };
};
constexpr U128 ExpectedCodes<16>::codes[3];
#endif

}  // namespace

TYPED_TEST_CASE(MortonCurveTest, FloatTypes);

// In this test, we're making sure that the code generator
// can take a series of primitives and use their bounding
// boxes to generate Morton codes for the centers of the
// bounding boxes.

TYPED_TEST(MortonCurveTest, GenerateCodes) {

  // clang-format off
  //
  // These are just pseudo-random test points
  // to ensure that the test is robust.
  Primitive<TypeParam> p[3] = {
    { { -1.42, -2.69,  3.05 }, {  4.10,   5.32,  8.52 } },
    { { -9.59, -8.11, -4.49 }, { 11.09,  15.67,  9.86 } },
    { {  2.19,  6.98, -5.81 }, {  3.08,   7.89,  6.68 } }
  };
  // clang-format on

  // From above, the center points are:
  //
  //  Center Point 1:
  //    X: ( 4.10 + (-1.42)) / 2 = 1.34
  //    Y: ( 5.32 + (-2.69)) / 2 = 1.315
  //    Z: ( 8.52 + ( 3.05)) / 2 = 5.785
  //  Center Point 1:
  //    X: (11.09 + (-9.59)) / 2 = 0.75
  //    Y: (15.67 + (-8.11)) / 2 = 3.78
  //    Z: ( 9.86 + (-4.49)) / 2 = 2.685
  //  Center Point 1:
  //    X: ( 3.08 + ( 2.19)) / 2 = 2.635
  //    Y: ( 7.89 + ( 6.98)) / 2 = 7.435
  //    Z: ( 6.68 + (-5.81)) / 2 = 0.435

  // For each floating point type, the code resolutions are:
  //
  //   float  32-bit : ( 32 / 3) * 3 = 30 bits
  //   float  64-bit : ( 64 / 3) * 3 = 63 bits
  //   float 128-bit : (128 / 3) * 3 = 126 bits
  //
  // The maximum Morton code values for 3D vectors are (for each float):
  //
  //   float  32-bit : 2 ^ ( 30 / 3) = 1024
  //   float  64-bit : 2 ^ ( 63 / 3) = 2097152
  //   float 128-bit : 2 ^ (126 / 3) = 4.398046511×10^12
  //
  // The 128-bit float may not get used if
  // a 128-bit integer isn't available at compile time.

  // Each of the center points have to get scaled to
  // the appropriate maximum Morton code value before they're converted.
  // In order to do this, we'll have to calculate the maximum and minimum
  // values of each center point. Here they are for our current test values:
  //
  //   X: max(1.340, 0.750, 2.635) = 2.635
  //   Y: max(1.315, 3.780, 7.435) = 7.435
  //   Z: max(5.785, 2.685, 0.435) = 5.785
  //
  //   X: min(1.340, 0.750, 2.635) = 0.750
  //   Y: min(1.315, 3.780, 7.435) = 1.315
  //   Z: min(5.785, 2.685, 0.435) = 0.435
  //
  // Therefore, the domain of each axis:
  //
  //   X: 2.635 - 0.750 = 1.885
  //   Y: 7.435 - 1.315 = 6.120
  //   Z: 5.785 - 0.435 = 5.350

  // Having the min, max, and range of each axis, we
  // can finally convert each coordinate into "Morton space".
  // The formula to do this is:
  //
  //   value_in_morton_space = ((value_in_world_space - axis_min) / axis_range) * morton_resolution
  //
  // We'll use this to convert each of the three center points into Morton space.
  //
  // For 32-bit floats:
  //
  //   Center Point 1:
  //     X: ((1.340 - (0.750)) / 1.885) * 1024 = 0.312997347 * 1024 = 320
  //     Y: ((1.315 - (1.315)) / 6.120) * 1024 = 0
  //     Z: ((5.785 - (0.435)) / 5.350) * 1024 = 1024
  //   Center Point 2:
  //     X: ((0.750 - (0.750)) / 1.885) * 1024 = 0
  //     Y: ((3.780 - (1.315)) / 6.120) * 1024 = 0.402777778 * 1024 = 412
  //     Z: ((2.685 - (0.435)) / 5.350) * 1024 = 0.420560748 * 1024 = 430
  //   Center Point 3:
  //     X: ((2.635 - (0.750)) / 1.885) * 1024 = 1024
  //     Y: ((7.435 - (1.315)) / 6.120) * 1024 = 1024
  //     Z: ((0.435 - (0.435)) / 5.350) * 1024 = 0
  //
  // For 64-bit floats:
  //
  //   Center Point 1:
  //     X: ((1.340 - (0.750)) / 1.885) * 2097152 = 0.312997347 * 2097152 = 656403
  //     Y: ((1.315 - (1.315)) / 6.120) * 2097152 = 0
  //     Z: ((5.785 - (0.435)) / 5.350) * 2097152 = 2097152
  //   Center Point 2:
  //     X: ((0.750 - (0.750)) / 1.885) * 2097152 = 0
  //     Y: ((3.780 - (1.315)) / 6.120) * 2097152 = 0.402777778 * 2097152 = 844686
  //     Z: ((2.685 - (0.435)) / 5.350) * 2097152 = 0.420560748 * 2097152 = 881979
  //   Center Point 3:
  //     X: ((2.635 - (0.750)) / 1.885) * 2097152 = 2097152
  //     Y: ((7.435 - (1.315)) / 6.120) * 2097152 = 2097152
  //     Z: ((0.435 - (0.435)) / 5.350) * 2097152 = 0
  //
  // For 128-bit floats:
  //
  //   Center Point 1:
  //     X: ((1.340 - (0.750)) / 1.885) * 4.398e12 = 0.312997347 * 4.398e12 = 1376576892069
  //     Y: ((1.315 - (1.315)) / 6.120) * 4.398e12 = 0
  //     Z: ((5.785 - (0.435)) / 5.350) * 4.398e12 = 4.398e12
  //   Center Point 2:
  //     X: ((0.750 - (0.750)) / 1.885) * 4.398e12 = 0
  //     Y: ((3.780 - (1.315)) / 6.120) * 4.398e12 = 0.402777778 * 4.398e12 = 1771435400305
  //     Z: ((2.685 - (0.435)) / 5.350) * 4.398e12 = 0.420560748 * 4.398e12 = 1849645728968
  //   Center Point 3:
  //     X: ((2.635 - (0.750)) / 1.885) * 4.398e12 = 4.398e12
  //     Y: ((7.435 - (1.315)) / 6.120) * 4.398e12 = 4.398e12
  //     Z: ((0.435 - (0.435)) / 5.350) * 4.398e12 = 0

  // Now all the center points have each component in Morton space.
  // We need to convert them to Moser–de Bruijn sequences.
  // This will require some bit shuffling.
  // In order to make this easier, we'll break down each into its individual bits.
  //
  // For 32-bit floats:
  //
  //   Center Point 1:
  //     X: 0000 0000 0000 0000 0000 0001 0100 0000
  //     Y: 0000 0000 0000 0000 0000 0000 0000 0000
  //     Z: 0000 0000 0000 0000 0000 0011 1111 1111
  //   Center Point 2:
  //     X: 0000 0000 0000 0000 0000 0000 0000 0000
  //     Y: 0000 0000 0000 0000 0000 0001 1001 1100
  //     Z: 0000 0000 0000 0000 0000 0001 1010 1110
  //   Center Point 3:
  //     X: 0000 0000 0000 0000 0000 0011 1111 1111
  //     Y: 0000 0000 0000 0000 0000 0011 1111 1111
  //     Z: 0000 0000 0000 0000 0000 0000 0000 0000
  //
  // For 64-bit floats:
  //
  //   Center Point 1:
  //     X: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1010 0000 0100 0001 0011
  //     Y: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
  //     Z: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 1111 1111 1111 1111 1111
  //   Center Point 2:
  //     X: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
  //     Y: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1100 1110 0011 1000 1110
  //     Z: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 1101 0111 0101 0011 1011
  //   Center Point 3:
  //     X: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 1111 1111 1111 1111 1111
  //     Y: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 1111 1111 1111 1111 1111
  //     Z: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
  //
  // For 128-bit floats:
  //
  //   Center Point 1:
  //     X: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 0100 0000 1000 0010 0110 0000 0110 1100 1010 0101
  //     Y: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
  //     Z: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111
  //   Center Point 2:
  //     X: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
  //     Y: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 1001 1100 0111 0001 1100 0111 0010 0000 0100 0011
  //     Z: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 1010 1110 1010 0111 0111 1010 0000 0100 1100 1000
  //   Center Point 3:
  //     X: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111
  //     Y: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0011 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111
  //     Z: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000

  // Now that we have the binary encoding of each Morton code,
  // it's just a matter of shifting each bit into the right place.
  //
  // For 32-bit floats:
  //
  //   Center Point 1:
  //     X:   0  1  0  1  0  0  0  0  0  0
  //     Y:    0  0  0  0  0  0  0  0  0  0
  //     Z:     1  1  1  1  1  1  1  1  1  1
  //        --------------------------------
  //     W: 00001101001101001001001001001001 = 0x0D349249
  //   Center Point 2:
  //     X:   0  0  0  0  0  0  0  0  0  0
  //     Y:    0  1  1  0  0  1  1  1  0  0
  //     Z:     0  1  1  0  1  0  1  1  1  0
  //        --------------------------------
  //     W: 00000011011000001010011011001000 = 0x0360A6C8
  //   Center Point 3:
  //     X:   1  1  1  1  1  1  1  1  1  1
  //     Y:    1  1  1  1  1  1  1  1  1  1
  //     Z:     0  0  0  0  0  0  0  0  0  0
  //        --------------------------------
  //     W: 00110110110110110110110110110110 = 0x36DB6DB6
  //
  // For 64-bit floats:
  //
  //   Center Point 1:
  //     X:  0  1  0  1  0  0  0  0  0  0  1  0  0  0  0  0  1  0  0  1  1
  //     Y:   0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  //     Z:    1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
  //        ----------------------------------------------------------------
  //     W: 0001101001101001001001001001001101001001001001001101001001101101 = 1A6924934924D26D
  //   Center Point 2:
  //     X:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  //     Y:   0  1  1  0  0  1  1  1  0  0  0  1  1  1  0  0  0  1  1  1  0
  //     Z:    0  1  1  0  1  0  1  1  1  0  1  0  1  0  0  1  1  1  0  1  1
  //        ----------------------------------------------------------------
  //     W: 0000011011000001010011011001000001010011010000001001011010011001 = 6C14D9053409699
  //   Center Point 3:
  //     X:  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
  //     Y:   1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
  //     Z:    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  //        ----------------------------------------------------------------
  //     W: 0110110110110110110110110110110110110110110110110110110110110110 = 6DB6DB6DB6DB6DB6
  //
  // For 128-bit floats:
  //
  //   Center Point 1:
  //     X:   0  1  0  1  0  0  0  0  0  0  1  0  0  0  0  0  1  0  0  1  1  0  0  0  0  0  0  1  1  0  1  1  0  0  1  0  1  0  0  1  0  1
  //     Y:    0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  //     Z:     1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
  //        --------------------------------------------------------------------------------------------------------------------------------
  //     W:   001101001101001001001001001001101001001001001001101001001101101001001001001001001101101001101101001001101001101001001101001101 = D349249A49269369249369B49A6934D
  //   Center Point 2:
  //     X:   0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  //     Y:    0  1  1  0  0  1  1  1  0  0  0  1  1  1  0  0  0  1  1  1  0  0  0  1  1  1  0  0  0  1  1  1  0  0  0  1  1  1  0  0  0  1
  //     Z n:   0  1  1  0  1  0  1  1  1  0  1  0  1  0  0  1  1  1  0  1  1  1  1  0  1  0  0  0  0  0  0  1  0  0  1  1  0  0  1  0  0  0
  //        --------------------------------------------------------------------------------------------------------------------------------
  //     W: 00000011011000001010011011001000001010011010000001001011010011001001001010011010000000000010010011000000001011010010001000000010 = 360A6C829A04B4C929A0024C02D2202
  //   Center Point 3:
  //     X:   1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
  //     Y:    1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
  //     Z:     0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  //        --------------------------------------------------------------------------------------------------------------------------------
  //     W: 00110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110110 = 36DB6DB6DB6DB6DB6DB6DB6DB6DB6DB6

  BoxConverter<TypeParam> box_converter;

  impl::MortonCurve<TypeParam> morton_curve;

  auto code_array = morton_curve(ConstIterable<Primitive<TypeParam>>(p, 3), box_converter);

  ASSERT_EQ(code_array.size(), 3);
  EXPECT_EQ(ExpectedCodes<sizeof(TypeParam)>::codes[0], code_array[0]);
  EXPECT_EQ(ExpectedCodes<sizeof(TypeParam)>::codes[1], code_array[1]);
  EXPECT_EQ(ExpectedCodes<sizeof(TypeParam)>::codes[2], code_array[2]);
}
