/*
    baseclasses2
    https://github.com/dblock/baseclasses2
*/

#include "stack_size_test.hpp"
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(StackSizeInteropTest);

/* Aliases for readability in tests */
typedef CStringTemplate<char, 4>  CStringS;  /* small: heap-allocates after 3 chars */
typedef CStringTemplate<char, 32> CStringL;  /* large: 31 chars fit on stack */

/* --- Cross-size construction --- */

void StackSizeInteropTest::testConstructFromDifferentStackSize() {
    CStringS small("hello");               /* overflows to heap: 5 > 3 */
    CStringL from_small(small);            /* construct large from small */
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(from_small.c_str()));

    CStringL large("world");
    CStringS from_large(large);            /* construct small from large, goes to heap */
    CPPUNIT_ASSERT_EQUAL(std::string("world"), std::string(from_large.c_str()));
}

/* --- Cross-size assignment --- */

void StackSizeInteropTest::testAssignFromDifferentStackSize() {
    CStringS small("abc");
    CStringL large;
    large = small;
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), std::string(large.c_str()));

    CStringL large2("xyz");
    CStringS small2;
    small2 = large2;
    CPPUNIT_ASSERT_EQUAL(std::string("xyz"), std::string(small2.c_str()));
}

/* --- Cross-size equality --- */

void StackSizeInteropTest::testEqualsAcrossStackSizes() {
    CStringS small("hello");
    CStringL large("hello");
    CPPUNIT_ASSERT(small.equals(large));
    CPPUNIT_ASSERT(large.equals(small));

    CStringS small2("world");
    CPPUNIT_ASSERT(!small.equals(small2));
}

void StackSizeInteropTest::testNotEqualsAcrossStackSizes() {
    CStringS small("foo");
    CStringL large("bar");
    CPPUNIT_ASSERT(small.notEquals(large));
    CPPUNIT_ASSERT(large.notEquals(small));

    CStringL same("foo");
    CPPUNIT_ASSERT(!small.notEquals(same));
}

void StackSizeInteropTest::testOperatorEqAcrossStackSizes() {
    CStringS small("test");
    CStringL large("test");
    CPPUNIT_ASSERT(small == large);
    CPPUNIT_ASSERT(large == small);
    CPPUNIT_ASSERT(!(small != large));

    CStringL diff("other");
    CPPUNIT_ASSERT(small != diff);
    CPPUNIT_ASSERT(diff != small);
}

/* --- Cross-size concatenation --- */

void StackSizeInteropTest::testAppendAcrossStackSizes() {
    CStringS small("foo");
    CStringL large("bar");

    /* append large into small (result goes to heap) */
    CStringS result("foo");
    result.append(large);
    CPPUNIT_ASSERT_EQUAL(std::string("foobar"), std::string(result.c_str()));

    /* append small into large */
    CStringL result2("bar");
    result2.append(small);
    CPPUNIT_ASSERT_EQUAL(std::string("barfoo"), std::string(result2.c_str()));
}

void StackSizeInteropTest::testOperatorPlusAcrossStackSizes() {
    CStringS small("hello");
    CStringL large(" world");
    /* result type is that of the left operand */
    CStringS r1 = small + large;
    CPPUNIT_ASSERT_EQUAL(std::string("hello world"), std::string(r1.c_str()));

    CStringL r2 = large + small;
    CPPUNIT_ASSERT_EQUAL(std::string(" worldhello"), std::string(r2.c_str()));
}

/* --- Stack vs heap allocation --- */

void StackSizeInteropTest::testSmallStackForcesHeap() {
    /* StackSize=4 means the on-stack buffer holds 3 chars + NUL.
       A 4-char string must allocate from the heap. */
    CStringS s("abcd");  /* 4 chars, must heap-allocate */
    CPPUNIT_ASSERT_EQUAL(4u, s.length());
    CPPUNIT_ASSERT_EQUAL(std::string("abcd"), std::string(s.c_str()));
    /* Extend well beyond stack to confirm heap path works */
    s.append("efghijklmnop");
    CPPUNIT_ASSERT_EQUAL(std::string("abcdefghijklmnop"), std::string(s.c_str()));
}

void StackSizeInteropTest::testSmallStackShortStringStaysOnStack() {
    /* Strings of 3 chars or fewer should stay in the on-stack buffer */
    CStringS s("hi");
    CPPUNIT_ASSERT_EQUAL(2u, s.length());
    CPPUNIT_ASSERT_EQUAL(std::string("hi"), std::string(s.c_str()));
}

/* --- Copying content across sizes --- */

void StackSizeInteropTest::testCopySmallToLarge() {
    /* Build a long string in a small-stack string (heap-allocated),
       then copy to a large-stack one and verify content is preserved. */
    CStringS small("this string is longer than four chars");
    CStringL large(small);
    CPPUNIT_ASSERT(small == large);
    CPPUNIT_ASSERT_EQUAL((unsigned int)small.length(), large.length());
}

void StackSizeInteropTest::testCopyLargeToSmall() {
    /* Build a string that fits on the large stack, copy to small (forces heap). */
    CStringL large("short");
    CStringS small(large);
    CPPUNIT_ASSERT(small == large);
    CPPUNIT_ASSERT_EQUAL(5u, small.length());
}

/* --- Wide char interop across stack sizes --- */

void StackSizeInteropTest::testWideInterop() {
    typedef CStringTemplate<wchar_t, 4>  CStringWS;
    typedef CStringTemplate<wchar_t, 32> CStringWL;

    CStringWS ws(L"hello");
    CStringWL wl(ws);
    CPPUNIT_ASSERT(ws == wl);

    wl = CStringWL(L"world");
    ws = wl;
    CPPUNIT_ASSERT(std::wstring(L"world") == ws.c_str());
}
