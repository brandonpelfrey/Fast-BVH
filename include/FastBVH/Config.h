#pragma once
//! \file Config.h Compiler Configuration Header
//! \brief This file is for checking
//! compiler settings to make minor
//! adjustments when needed.

// Unless manually turned off,
// let's see if we can include STL or not.
#ifndef FASTBVH_NO_STL
// CUDA compiler doesn't support STL.
// If we detect that we're compiling
// with the CUDA compiler, don't include STL headers.
#if defined(__NVCC__)
#define FASTBVH_NO_STL
#endif
#endif  // FASTBVH_NO_STL

#ifndef __SIZEOF_INT128__

//! \brief This macro indicates that
//! GCC's __int128 is not available.
//! This is important when deciding
//! how to handle 128-bit floats in
//! some scenarios.
#define FASTBVH_NO_INT128

#endif
