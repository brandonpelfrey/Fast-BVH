#pragma once

//! \file Config.h Compiler Configuration Header
//! \brief This file is for checking
//! compiler settings to make minor
//! adjustments when needed.

#if !defined(__SIZEOF_INT128__)

//! \brief This macro indicates that
//! GCC's __int128 is not available.
//! This is important when deciding
//! how to handle 128-bit floats in
//! some scenarios.
#define FASTBVH_NO_INT128

#endif // __SIZEOF_INT128__

#ifndef FASTBVH_CACHE_LINE_SIZE

//! \brief Used for various alignment specifiers.
//! This can be set by the caller to specifier a different
//! cache size, such as 32 or 128.
#define FASTBVH_CACHE_LINE_SIZE 64

#endif // FASTBVH_CACHE_LINE_SIZE

#ifndef FASTBVH_L1_CACHE_SIZE

//! \brief The number of bytes in the L1 cache.
//! This is used for agressive loop optimization.
//! It is set conservatively at 4K and may be adjusted
//! depending on the platform.
#define FASTBVH_L1_CACHE_SIZE 4096

#endif // FASTBVH_L1_CACHE_SIZE

#ifndef FASTBVH_L2_CACHE_SIZE

//! \brief The size of the L2 cache.
//! This is used for nested loop optimization.
//! By default, it is set to 4 times the size of the L1 cache.
#define FASTBVH_L2_CACHE_SIZE (FASTBVH_L1_CACHE_SIZE * 4)

#endif // FASTBVH_L2_CACHE_SIZE

#ifdef __GNUC__

#define FASTBVH_CLZ_U(n)   __builtin_clz(n)

#define FASTBVH_CLZ_UL(n)  __builtin_clzl(n)

#define FASTBVH_CLZ_ULL(n) __builtin_clzll(n)

#endif // __GNUC__

#ifdef _MSC_VER

#define FASTBVH_CLZ_U(n)    __lzcnt(n)

#define FASTBVH_CLZ_UL(n)   __lzcnt(n)

#define FASTBVH_CLZ_ULL(n)  __lzcnt64(n)

#endif // _MSC_VER

namespace FastBVH {

//! \brief This function is used for getting the compile-time cache
//! line size, without having to use an ugly macro.
//! \return The compile-time cache line size, in terms of bytes.
constexpr auto cacheLineSize() noexcept {
  return FASTBVH_CACHE_LINE_SIZE;
}

//! \brief This function is used for getting the compile-time L1 cache size.
//! It can be used to avoid using ugly macros.
//! \return The size of the L1 cache, in bytes.
constexpr auto l1CacheSize() noexcept {
  return FASTBVH_L1_CACHE_SIZE;
}

//! \brief This function is used for getting the compile-time L2 cache size.
//! It can be used to avoid using ugly macros.
//! \return The size of the L2 cache, in bytes.
constexpr auto l2CacheSize() noexcept {
  return FASTBVH_L2_CACHE_SIZE;
}

//! \brief Indicates the number of cache lines in the L1 cache.
//! \return The number of lines in the L1 cache.
constexpr auto cacheLinesPerL1() noexcept {
  return l1CacheSize() / cacheLineSize();
}

//! \brief The naive implementation of counting leading zeros.
//! Don't use this function directly, instead use @ref clz.
template <typename Integer>
constexpr auto naiveClz(Integer n) noexcept {
  constexpr auto bits = sizeof(Integer) * 8;
  for (auto i = bits; i > 0; i--) {
    if ((Integer(1) << (i - 1)) & n) {
      return bits - i;
    }
  }
  return bits - 1;
}

//! \brief The generic clz function.
//! If it's not specialized with a compiler builtin,
//! then it uses a naive brute force method of calculating
//! leading zeros (which is much slower.)
template <typename Integer>
constexpr auto clz(Integer n) noexcept {
  return naiveClz(n);
}

#ifdef FASTBVH_CLZ_U

//! \brief Counts leading zeros of integer types.
inline auto clz(unsigned int n) noexcept {
  return FASTBVH_CLZ_U(n);
}

#endif // FASTBVH_CLZ_U

#ifdef FASTBVH_CLZ_UL

//! \brief Counts leading zeros of long integer types.
inline auto clz(unsigned long int n) noexcept {
  return FASTBVH_CLZ_UL(n);
}

#endif // FASTBVH_CLZ_UL

#ifdef FASTBVH_CLZ_ULL

//! \brief Counts leading zeros of long long integer types.
inline auto clz(unsigned long long int n) noexcept {
  return FASTBVH_CLZ_ULL(n);
}

#endif // FASTBVH_CLZ_ULL

} // namespace FastBVH
