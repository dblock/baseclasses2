/*
    baseclasses2
    https://github.com/dblock/baseclasses2
*/

#ifndef STACK_SIZE_TEST_HPP
#define STACK_SIZE_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.hpp>

/* Tests interoperability between CStringTemplate instances with different StackSizes.
   Uses StackSize=4 (forces heap allocation for any string >3 chars) and StackSize=32
   to exercise all cross-size paths. */

class StackSizeInteropTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StackSizeInteropTest);
    CPPUNIT_TEST(testConstructFromDifferentStackSize);
    CPPUNIT_TEST(testAssignFromDifferentStackSize);
    CPPUNIT_TEST(testEqualsAcrossStackSizes);
    CPPUNIT_TEST(testNotEqualsAcrossStackSizes);
    CPPUNIT_TEST(testOperatorEqAcrossStackSizes);
    CPPUNIT_TEST(testAppendAcrossStackSizes);
    CPPUNIT_TEST(testOperatorPlusAcrossStackSizes);
    CPPUNIT_TEST(testSmallStackForcesHeap);
    CPPUNIT_TEST(testSmallStackShortStringStaysOnStack);
    CPPUNIT_TEST(testCopySmallToLarge);
    CPPUNIT_TEST(testCopyLargeToSmall);
    CPPUNIT_TEST(testWideInterop);
    CPPUNIT_TEST_SUITE_END();
public:
    void testConstructFromDifferentStackSize();
    void testAssignFromDifferentStackSize();
    void testEqualsAcrossStackSizes();
    void testNotEqualsAcrossStackSizes();
    void testOperatorEqAcrossStackSizes();
    void testAppendAcrossStackSizes();
    void testOperatorPlusAcrossStackSizes();
    void testSmallStackForcesHeap();
    void testSmallStackShortStringStaysOnStack();
    void testCopySmallToLarge();
    void testCopyLargeToSmall();
    void testWideInterop();
};

#endif
