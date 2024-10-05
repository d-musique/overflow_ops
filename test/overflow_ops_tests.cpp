#include "overflow_ops.h"
#include <limits>
#include <type_traits>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

template <class T>
void iop_test(
    bool (&add)(T, T, T *),
    bool (&sub)(T, T, T *),
    bool (&mul)(T, T, T *))
{
    T r;
    constexpr T min = std::numeric_limits<T>::min();
    constexpr T max = std::numeric_limits<T>::max();

    REQUIRE(!add(1, 2, &r));
    REQUIRE(r == 3);
    REQUIRE(!sub(3, 2, &r));
    REQUIRE(r == 1);
    REQUIRE(!mul(4, 5, &r));
    REQUIRE(r == 20);

    REQUIRE(add(max, 1, &r));
    REQUIRE(!add(max - 1, 1, &r));
    REQUIRE(r == max);
    REQUIRE(sub(min, 1, &r));
    REQUIRE(!sub(min + 1, 1, &r));
    REQUIRE(r == min);
    REQUIRE(mul(max, max, &r));
    REQUIRE(mul(max, min, &r) == std::is_signed<T>::value);
    REQUIRE(mul(min, min, &r) == std::is_signed<T>::value);
}

#define IOP_CONCAT2(a, b) IOP_CONCAT_(a, b)
#define IOP_CONCAT3(a, b, c) IOP_CONCAT2(a, IOP_CONCAT2(b, c))
#define IOP_CONCAT_(a, b) a##b

#define IOP_TEST_CASE(prefix, type) \
    TEST_CASE("Overflow ops: " #prefix) \
    { \
        iop_test<type>( \
            IOP_CONCAT3(prefix, _, add_overflow), \
            IOP_CONCAT3(prefix, _, sub_overflow), \
            IOP_CONCAT3(prefix, _, mul_overflow)); \
    }

IOP_TEST_CASE(i32, int32_t);
IOP_TEST_CASE(u32, uint32_t);
IOP_TEST_CASE(i64, int64_t);
IOP_TEST_CASE(u64, uint64_t);
IOP_TEST_CASE(int, int);
IOP_TEST_CASE(uint, unsigned int);
IOP_TEST_CASE(long, long);
IOP_TEST_CASE(ulong, unsigned long);
IOP_TEST_CASE(llong, long long);
IOP_TEST_CASE(ullong, unsigned long long);
IOP_TEST_CASE(ptrdiff, ptrdiff_t);
IOP_TEST_CASE(size, size_t);
