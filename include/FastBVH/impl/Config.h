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
