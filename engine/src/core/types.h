#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* C/C++ bilingual helpers (dual-language policy, docs/Build_Guide.md):
 * compound literals and _Static_assert are C-only; C++20 spells them as
 * functional aggregate init and static_assert with identical semantics. */
#ifdef __cplusplus
#define BREAK_AGG(T) T
#define BREAK_STATIC_ASSERT static_assert
#else
#define BREAK_AGG(T) (T)
#define BREAK_STATIC_ASSERT _Static_assert
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* ---- Fixed-width aliases ---- */
typedef float  f32;
typedef double f64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t    usize;
typedef ptrdiff_t isize;

/* ---- Cross-compiler alignment macro ---- */
#if defined(_MSC_VER)
    #define ENGINE_ALIGN(x) __declspec(align(x))
#else
    #define ENGINE_ALIGN(x) __attribute__((aligned(x)))
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
