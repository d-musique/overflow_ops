// This is part of overflow_ops.
// Free software published under the MIT license.

#pragma once
#if !defined(OVERFLOW_OPS_H_INCLUDED)
#define OVERFLOW_OPS_H_INCLUDED

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(IOP_NOEXCEPT)
#if __cplusplus >= 201103L
#define IOP_NOEXCEPT noexcept
#else
#define IOP_NOEXCEPT
#endif
#endif

bool i32_add_overflow(int32_t a, int32_t b, int32_t *r) IOP_NOEXCEPT;
bool i32_sub_overflow(int32_t a, int32_t b, int32_t *r) IOP_NOEXCEPT;
bool i32_mul_overflow(int32_t a, int32_t b, int32_t *r) IOP_NOEXCEPT;

bool u32_add_overflow(uint32_t a, uint32_t b, uint32_t *r) IOP_NOEXCEPT;
bool u32_sub_overflow(uint32_t a, uint32_t b, uint32_t *r) IOP_NOEXCEPT;
bool u32_mul_overflow(uint32_t a, uint32_t b, uint32_t *r) IOP_NOEXCEPT;

bool i64_add_overflow(int64_t a, int64_t b, int64_t *r) IOP_NOEXCEPT;
bool i64_sub_overflow(int64_t a, int64_t b, int64_t *r) IOP_NOEXCEPT;
bool i64_mul_overflow(int64_t a, int64_t b, int64_t *r) IOP_NOEXCEPT;

bool u64_add_overflow(uint64_t a, uint64_t b, uint64_t *r) IOP_NOEXCEPT;
bool u64_sub_overflow(uint64_t a, uint64_t b, uint64_t *r) IOP_NOEXCEPT;
bool u64_mul_overflow(uint64_t a, uint64_t b, uint64_t *r) IOP_NOEXCEPT;

bool int_add_overflow(int a, int b, int *r) IOP_NOEXCEPT;
bool int_sub_overflow(int a, int b, int *r) IOP_NOEXCEPT;
bool int_mul_overflow(int a, int b, int *r) IOP_NOEXCEPT;

bool uint_add_overflow(unsigned int a, unsigned int b, unsigned int *r) IOP_NOEXCEPT;
bool uint_sub_overflow(unsigned int a, unsigned int b, unsigned int *r) IOP_NOEXCEPT;
bool uint_mul_overflow(unsigned int a, unsigned int b, unsigned int *r) IOP_NOEXCEPT;

bool long_add_overflow(long a, long b, long *r) IOP_NOEXCEPT;
bool long_sub_overflow(long a, long b, long *r) IOP_NOEXCEPT;
bool long_mul_overflow(long a, long b, long *r) IOP_NOEXCEPT;

bool ulong_add_overflow(unsigned long a, unsigned long b, unsigned long *r) IOP_NOEXCEPT;
bool ulong_sub_overflow(unsigned long a, unsigned long b, unsigned long *r) IOP_NOEXCEPT;
bool ulong_mul_overflow(unsigned long a, unsigned long b, unsigned long *r) IOP_NOEXCEPT;

bool llong_add_overflow(long long a, long long b, long long *r) IOP_NOEXCEPT;
bool llong_sub_overflow(long long a, long long b, long long *r) IOP_NOEXCEPT;
bool llong_mul_overflow(long long a, long long b, long long *r) IOP_NOEXCEPT;

bool ullong_add_overflow(unsigned long long a, unsigned long long b, unsigned long long *r) IOP_NOEXCEPT;
bool ullong_sub_overflow(unsigned long long a, unsigned long long b, unsigned long long *r) IOP_NOEXCEPT;
bool ullong_mul_overflow(unsigned long long a, unsigned long long b, unsigned long long *r) IOP_NOEXCEPT;

bool ptrdiff_add_overflow(ptrdiff_t a, ptrdiff_t b, ptrdiff_t *r) IOP_NOEXCEPT;
bool ptrdiff_sub_overflow(ptrdiff_t a, ptrdiff_t b, ptrdiff_t *r) IOP_NOEXCEPT;
bool ptrdiff_mul_overflow(ptrdiff_t a, ptrdiff_t b, ptrdiff_t *r) IOP_NOEXCEPT;

bool size_add_overflow(size_t a, size_t b, size_t *r) IOP_NOEXCEPT;
bool size_sub_overflow(size_t a, size_t b, size_t *r) IOP_NOEXCEPT;
bool size_mul_overflow(size_t a, size_t b, size_t *r) IOP_NOEXCEPT;

#if !defined(__cplusplus)
#define add_overflow(a, b, r) IOP__XXX_OVERFLOW(add, +, a, b, r)
#define sub_overflow(a, b, r) IOP__XXX_OVERFLOW(sub, -, a, b, r)
#define mul_overflow(a, b, r) IOP__XXX_OVERFLOW(mul, *, a, b, r)
#else
} // extern "C"
template <class T> bool add_overflow(T a, T b, T *r) IOP_NOEXCEPT;
template <class T> bool sub_overflow(T a, T b, T *r) IOP_NOEXCEPT;
template <class T> bool mul_overflow(T a, T b, T *r) IOP_NOEXCEPT;
extern "C" {
#endif

//------------------------------------------------------------------------------

#define IOP_CONCAT2(a, b) IOP_CONCAT_(a, b)
#define IOP_CONCAT3(a, b, c) IOP_CONCAT2(a, IOP_CONCAT2(b, c))
#define IOP_CONCAT4(a, b, c, d) IOP_CONCAT2(a, IOP_CONCAT3(b, c, d))
#define IOP_CONCAT5(a, b, c, d, e) IOP_CONCAT2(a, IOP_CONCAT4(b, c, d, e))
#define IOP_CONCAT_(a, b) a##b

#if !defined(IOP_INLINE)
#if defined(__GNUC__)
#define IOP_INLINE __attribute__((__always_inline__)) inline
#elif defined(_MSC_VER)
#define IOP_INLINE __forceinline
#else
#define IOP_INLINE inline
#endif
#endif

#if !defined(IOP_STATIC_ASSERT)
#if __cplusplus >= 201103L
#define IOP_STATIC_ASSERT(a, b) static_assert(a, b)
#else
#define IOP_STATIC_ASSERT(a, b)
#endif
#endif

//------------------------------------------------------------------------------

#define IOP__XXX_OVERFLOW(op, o, a, b, r) (_Generic((a) o (b), \
   int: IOP_CONCAT4(int, _, op, _overflow), \
   long: IOP_CONCAT4(long, _, op, _overflow), \
   long long: IOP_CONCAT4(llong, _, op, _overflow), \
   unsigned int: IOP_CONCAT4(uint, _, op, _overflow), \
   unsigned long: IOP_CONCAT4(ulong, _, op, _overflow), \
   unsigned long long: IOP_CONCAT4(ullong, _, op, _overflow)) \
   ((a), (b), (r)))

#define IOP__XXX_OVERFLOW_TEMPLATE_SPECIALIZATION(op) \
   template <> IOP_INLINE bool IOP_CONCAT2(op, _overflow)(int a, int b, int *r) IOP_NOEXCEPT { return IOP_CONCAT3(int_, op, _overflow)(a, b, r); } \
   template <> IOP_INLINE bool IOP_CONCAT2(op, _overflow)(long a, long b, long *r) IOP_NOEXCEPT { return IOP_CONCAT3(long_, op, _overflow)(a, b, r); } \
   template <> IOP_INLINE bool IOP_CONCAT2(op, _overflow)(long long a, long long b, long long *r) IOP_NOEXCEPT { return IOP_CONCAT3(llong_, op, _overflow)(a, b, r); } \
   template <> IOP_INLINE bool IOP_CONCAT2(op, _overflow)(unsigned int a, unsigned int b, unsigned int *r) IOP_NOEXCEPT { return IOP_CONCAT3(uint_, op, _overflow)(a, b, r); } \
   template <> IOP_INLINE bool IOP_CONCAT2(op, _overflow)(unsigned long a, unsigned long b, unsigned long *r) IOP_NOEXCEPT { return IOP_CONCAT3(ulong_, op, _overflow)(a, b, r); } \
   template <> IOP_INLINE bool IOP_CONCAT2(op, _overflow)(unsigned long long a, unsigned long long b, unsigned long long *r) IOP_NOEXCEPT { return IOP_CONCAT3(ullong_, op, _overflow)(a, b, r); }

#if defined(__cplusplus)
} // extern "C"
IOP__XXX_OVERFLOW_TEMPLATE_SPECIALIZATION(add)
IOP__XXX_OVERFLOW_TEMPLATE_SPECIALIZATION(sub)
IOP__XXX_OVERFLOW_TEMPLATE_SPECIALIZATION(mul)
extern "C" {
#endif

//------------------------------------------------------------------------------

#if !defined(IOP_COMPILED_SEPARATE)
#if defined(_MSC_VER)
#define IOP_COMPILED_SEPARATE 1
#else
#define IOP_COMPILED_SEPARATE 0
#endif
#endif

#if !IOP_COMPILED_SEPARATE
#include "overflow_ops_impl.h"
#endif

#if (INT_MIN == INT32_MIN) && (INT_MAX == INT32_MAX)
#define IOP_INT_BITS 32
#elif (INT_MIN == INT64_MIN) && (INT_MAX == INT64_MAX)
#define IOP_INT_BITS 64
#else
#error Invalid size: int
#endif

#if (LONG_MIN == INT32_MIN) && (LONG_MAX == INT32_MAX)
#define IOP_LONG_BITS 32
#elif (LONG_MIN == INT64_MIN) && (LONG_MAX == INT64_MAX)
#define IOP_LONG_BITS 64
#else
#error Invalid size: long
#endif

#if (LLONG_MIN == INT32_MIN) && (LLONG_MAX == INT32_MAX)
#define IOP_LLONG_BITS 32
#elif (LLONG_MIN == INT64_MIN) && (LLONG_MAX == INT64_MAX)
#define IOP_LLONG_BITS 64
#else
#error Invalid size: long long
#endif

#if (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
#define IOP_PTRDIFF_BITS 32
#elif (PTRDIFF_MIN == INT64_MIN) && (PTRDIFF_MAX == INT64_MAX)
#define IOP_PTRDIFF_BITS 64
#else
#error Invalid ptrdiff: ptrdiff_t
#endif

#if (SIZE_MIN == UINT32_MIN) && (SIZE_MAX == UINT32_MAX)
#define IOP_SIZE_BITS 32
#elif (SIZE_MIN == UINT64_MIN) && (SIZE_MAX == UINT64_MAX)
#define IOP_SIZE_BITS 64
#else
#error Invalid size: size_t
#endif

#define IOP_IMPLEMENT_TYPEQUIV_SIGNED(prefix, type, bits, op) \
    IOP_INLINE bool IOP_CONCAT4(prefix, _, op, _overflow)(type a, type b, type *r) IOP_NOEXCEPT \
    { \
        IOP_STATIC_ASSERT(sizeof(type) == sizeof(IOP_CONCAT3(int, bits, _t)), "type size mismatch"); \
        return IOP_CONCAT5(i, bits, _, op, _overflow)((IOP_CONCAT3(int, bits, _t))a, (IOP_CONCAT3(int, bits, _t))b, (IOP_CONCAT3(int, bits, _t) *)r); \
    }

#define IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(prefix, type, bits, op) \
    IOP_INLINE bool IOP_CONCAT4(prefix, _, op, _overflow)(type a, type b, type *r) IOP_NOEXCEPT \
    { \
        IOP_STATIC_ASSERT(sizeof(type) == sizeof(IOP_CONCAT3(uint, bits, _t)), "type size mismatch"); \
        return IOP_CONCAT5(u, bits, _, op, _overflow)((IOP_CONCAT3(uint, bits, _t))a, (IOP_CONCAT3(uint, bits, _t))b, (IOP_CONCAT3(uint, bits, _t) *)r); \
    }

IOP_IMPLEMENT_TYPEQUIV_SIGNED(int, int, IOP_INT_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(int, int, IOP_INT_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(int, int, IOP_INT_BITS, mul)

IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(uint, unsigned int, IOP_INT_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(uint, unsigned int, IOP_INT_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(uint, unsigned int, IOP_INT_BITS, mul)

IOP_IMPLEMENT_TYPEQUIV_SIGNED(long, long, IOP_LONG_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(long, long, IOP_LONG_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(long, long, IOP_LONG_BITS, mul)

IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(ulong, unsigned long, IOP_LONG_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(ulong, unsigned long, IOP_LONG_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(ulong, unsigned long, IOP_LONG_BITS, mul)

IOP_IMPLEMENT_TYPEQUIV_SIGNED(llong, long long, IOP_LLONG_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(llong, long long, IOP_LLONG_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(llong, long long, IOP_LLONG_BITS, mul)

IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(ullong, unsigned long long, IOP_LLONG_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(ullong, unsigned long long, IOP_LLONG_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(ullong, unsigned long long, IOP_LLONG_BITS, mul)

IOP_IMPLEMENT_TYPEQUIV_SIGNED(ptrdiff, ptrdiff_t, IOP_PTRDIFF_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(ptrdiff, ptrdiff_t, IOP_PTRDIFF_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_SIGNED(ptrdiff, ptrdiff_t, IOP_PTRDIFF_BITS, mul)

IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(size, size_t, IOP_SIZE_BITS, add)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(size, size_t, IOP_SIZE_BITS, sub)
IOP_IMPLEMENT_TYPEQUIV_UNSIGNED(size, size_t, IOP_SIZE_BITS, mul)

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // !defined(OVERFLOW_OPS_H_INCLUDED)
