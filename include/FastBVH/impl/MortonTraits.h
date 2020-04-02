#pragma once

namespace FastBVH {

namespace impl {

//! \brief this class is used to indicate
//! the traits of a morton curve for a
//! specified floating point type size.
template <Size float_size>
struct MortonTraits final {};

//! \brief Traits for Morton curve
//! for 32-bit floats.
template <>
struct MortonTraits<4> final {
  //! \brief This is the Morton curve
  //! resolution for 32-bit floats.
  static constexpr float domain() noexcept { return 1024; }
};

//! \brief Traits for Morton curve
//! for 64-bit floats.
template <>
struct MortonTraits<8> final {
  //! \brief This is the Morton curve
  //! resolution for 64-bit floats.
  //! If the size of "double" is not
  //! 8 bytes, then this is not instantiated.
  static constexpr double domain() noexcept { return 2097152; }
};

//! \brief Traits for Morton curve
//! for 128-bit floats.
template <>
struct MortonTraits<16> final {
  //! \brief This is the Morton curve
  //! resolution for 128-bit floats.
  //! If the size of "long double" is not
  //! 16 bytes, then this is not instantiated.
  static constexpr long double domain() noexcept { return 4.398046511104e12; }
};

} // namespace impl

}  // namespace FastBVH
