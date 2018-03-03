#pragma once

#include <cstdint>

// Explicit data types

using usize = size_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

static_assert((sizeof(f32) * 8) == 32, "f32 is not of 32 bit width");
static_assert((sizeof(f64) * 8) == 64, "f64 is not of 64 bit width");

// Graphics Related

using ProgramID = u32;
using UniformID = i32;

using VaoID = u32;
using VboID = u32;
using EboID = u32;

#define ARRAY_LENGTH(x)  (sizeof(x) / sizeof((x)[0]))