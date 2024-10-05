// This is part of overflow_ops.
// Free software published under the MIT license.

#if IOP_COMPILED_SEPARATE
#define IOP_IMPLEMENT(prefix, type, op) \
    IOP_IMPLEMENT_SEPARATE(prefix, type, op)
#else
#define IOP_IMPLEMENT(prefix, type, op) \
    IOP_IMPLEMENT_INLINE(prefix, type, op)
#endif

#define IOP_IMPLEMENT_SEPARATE(prefix, type, op) \
    bool IOP_CONCAT4(prefix, _, op, _overflow) \
        (type a, type b, type *r) IOP_NOEXCEPT \
    { \
        return IOP_CONCAT3(__builtin_, op, _overflow)(a, b, r); \
    }

#define IOP_IMPLEMENT_INLINE(prefix, type, op) \
    IOP_INLINE IOP_IMPLEMENT_SEPARATE(prefix, type, op)

IOP_IMPLEMENT(i32, int32_t, add)
IOP_IMPLEMENT(i32, int32_t, sub)
IOP_IMPLEMENT(i32, int32_t, mul)

IOP_IMPLEMENT(u32, uint32_t, add)
IOP_IMPLEMENT(u32, uint32_t, sub)
IOP_IMPLEMENT(u32, uint32_t, mul)

IOP_IMPLEMENT(i64, int64_t, add)
IOP_IMPLEMENT(i64, int64_t, sub)
IOP_IMPLEMENT(i64, int64_t, mul)

IOP_IMPLEMENT(u64, uint64_t, add)
IOP_IMPLEMENT(u64, uint64_t, sub)
IOP_IMPLEMENT(u64, uint64_t, mul)
