// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "../edltestutils.h"

#include <openenclave/enclave.h>
#include <openenclave/internal/tests.h>
#include "all_t.h"

static uint64_t data[8] = {0x1112131415161718,
                           0x2122232425262728,
                           0x3132333435363738,
                           0x4142434445464748,
                           0x5152535455565758,
                           0x6162636465666768,
                           0x7172737475767778,
                           0x8182838485868788};

// Assert that the struct is copied by value, such that `s.ptr` is the
// address of `data[]` in the host (also passed via `ptr`).
void deepcopy_value(ShallowStruct s, uint64_t* ptr)
{
    OE_TEST(s.count == 7);
    OE_TEST(s.size == 64);
    OE_TEST(s.ptr == ptr);
    OE_TEST(oe_is_outside_enclave(s.ptr, sizeof(uint64_t)));
}

// Assert that the struct is shallow-copied (even though it is passed
// by pointer), such that `s->ptr` is the address of `data[]` in the
// host (also passed via `ptr`).
void deepcopy_shallow(ShallowStruct* s, uint64_t* ptr)
{
    OE_TEST(s->count == 7);
    OE_TEST(s->size == 64);
    OE_TEST(s->ptr == ptr);
    OE_TEST(oe_is_outside_enclave(s->ptr, sizeof(uint64_t)));
}

// Assert that the struct is deep-copied such that `s->ptr` has a copy
// of three elements of `data` in enclave memory.
void deepcopy_count(CountStruct* s)
{
    OE_TEST(s->count == 7);
    OE_TEST(s->size == 64);
    for (size_t i = 0; i < 3; ++i)
        OE_TEST(s->ptr[i] == data[i]);
    OE_TEST(oe_is_within_enclave(s->ptr, 3 * sizeof(uint64_t)));
}

// Assert that the struct is deep-copied such that `s->ptr` has a copy
// of `s->count` elements of `data` in enclave memory.
void deepcopy_countparam(CountParamStruct* s)
{
    OE_TEST(s->count == 7);
    OE_TEST(s->size == 64);
    for (size_t i = 0; i < s->count; ++i)
        OE_TEST(s->ptr[i] == data[i]);
    OE_TEST(oe_is_within_enclave(s->ptr, s->count * sizeof(uint64_t)));
}

// Assert that the struct is deep-copied such that `s->ptr` has a copy
// of `s->size` bytes of `data` in enclave memory.
void deepcopy_sizeparam(SizeParamStruct* s)
{
    OE_TEST(s->count == 7);
    OE_TEST(s->size == 64);
    for (size_t i = 0; i < s->size / sizeof(uint64_t); ++i)
        OE_TEST(s->ptr[i] == data[i]);
    OE_TEST(oe_is_within_enclave(s->ptr, s->size));
}

// Assert that the struct is deep-copied such that `s->ptr` has a copy
// of `s->count * s->size` bytes of `data` in enclave memory.
void deepcopy_countsizeparam(CountSizeParamStruct* s)
{
    OE_TEST(s->count == 8);
    OE_TEST(s->size == 4);
    for (size_t i = 0; i < (s->count * s->size) / sizeof(uint64_t); ++i)
        OE_TEST(s->ptr[i] == data[i]);
    OE_TEST(oe_is_within_enclave(s->ptr, s->count * s->size));
}

// Assert that the struct array is deep-copied such that each
// element's `ptr` has a copy of its `count` elements of `data` in
// enclave memory.
void deepcopy_countparamarray(CountParamStruct* s)
{
    OE_TEST(s[0].count == 7);
    OE_TEST(s[0].size == 64);
    for (size_t i = 0; i < s[0].count; ++i)
        OE_TEST(s[0].ptr[i] == data[i]);
    OE_TEST(oe_is_within_enclave(s[0].ptr, s[0].count * sizeof(uint64_t)));

    OE_TEST(s[1].count == 3);
    OE_TEST(s[1].size == 32);
    for (size_t i = 0; i < s[1].count; ++i)
        OE_TEST(s[1].ptr[i] == data[4 + i]);
    OE_TEST(oe_is_within_enclave(s[1].ptr, s[1].count * sizeof(uint64_t)));
}

// Assert that the struct array is deep-copied such that each
// element's `ptr` has a copy of its `size` bytes of `data` in enclave
// memory.
void deepcopy_sizeparamarray(SizeParamStruct* s)
{
    OE_TEST(s[0].count == 7);
    OE_TEST(s[0].size == 64);
    for (size_t i = 0; i < s[0].size / sizeof(uint64_t); ++i)
        OE_TEST(s[0].ptr[i] == data[i]);
    OE_TEST(oe_is_within_enclave(s[0].ptr, s[0].size));

    OE_TEST(s[1].count == 3);
    OE_TEST(s[1].size == 32);
    for (size_t i = 0; i < s[1].size / sizeof(uint64_t); ++i)
        OE_TEST(s[1].ptr[i] == data[4 + i]);
    OE_TEST(oe_is_within_enclave(s[1].ptr, s[1].size));
}

// Assert that the struct array is deep-copied such that each
// element's `ptr` has a copy of its `count * size` bytes of `data` in
// enclave memory.
void deepcopy_countsizeparamarray(CountSizeParamStruct* s)
{
    OE_TEST(s[0].count == 8);
    OE_TEST(s[0].size == 4);
    for (size_t i = 0; i < (s[0].count * s[0].size) / sizeof(uint64_t); ++i)
        OE_TEST(s[0].ptr[i] == data[i]);
    OE_TEST(oe_is_within_enclave(s[0].ptr, s[0].count * s[0].size));

    OE_TEST(s[1].count == 3);
    OE_TEST(s[1].size == 8);
    for (size_t i = 0; i < (s[1].count * s[1].size) / sizeof(uint64_t); ++i)
        OE_TEST(s[1].ptr[i] == data[4 + i]);
    OE_TEST(oe_is_within_enclave(s[1].ptr, s[1].count * s[1].size));
}

void deepcopy_nested(NestedStruct* n)
{
    OE_TEST(oe_is_within_enclave(n, sizeof(NestedStruct)));

    OE_TEST(n->plain_int == 13);

    OE_TEST(oe_is_within_enclave(n->array_of_int, 4 * sizeof(int)));
    for (int i = 0; i < 4; ++i)
        OE_TEST(n->array_of_int[i] == i);

    OE_TEST(oe_is_outside_enclave(n->shallow_struct, sizeof(ShallowStruct)));

    OE_TEST(oe_is_within_enclave(n->array_of_struct, 3 * sizeof(CountStruct)));
    for (size_t i = 0; i < 3; ++i)
        deepcopy_count(&(n->array_of_struct[i]));
}
