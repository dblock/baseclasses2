/*
    baseclasses2
    https://github.com/dblock/baseclasses2
*/

#ifndef WSTRING_TEST_HPP
#define WSTRING_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.hpp>

class WStringConstructorTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringConstructorTest);
    CPPUNIT_TEST(testDefaultConstructor);
    CPPUNIT_TEST(testCStrConstructor);
    CPPUNIT_TEST(testCStrLenConstructor);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testCharConstructor);
    CPPUNIT_TEST(testAssignCStr);
    CPPUNIT_TEST(testAssignChar);
    CPPUNIT_TEST(testAssignString);
    CPPUNIT_TEST_SUITE_END();
public:
    void testDefaultConstructor();
    void testCStrConstructor();
    void testCStrLenConstructor();
    void testCopyConstructor();
    void testCharConstructor();
    void testAssignCStr();
    void testAssignChar();
    void testAssignString();
};

class WStringComparisonTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringComparisonTest);
    CPPUNIT_TEST(testEquals);
    CPPUNIT_TEST(testNotEquals);
    CPPUNIT_TEST(testEqualsIgnoreCase);
    CPPUNIT_TEST(testOperatorEquals);
    CPPUNIT_TEST(testStartsWith);
    CPPUNIT_TEST(testEndsWith);
    CPPUNIT_TEST_SUITE_END();
public:
    void testEquals();
    void testNotEquals();
    void testEqualsIgnoreCase();
    void testOperatorEquals();
    void testStartsWith();
    void testEndsWith();
};

class WStringCaseTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringCaseTest);
    CPPUNIT_TEST(testToUpper);
    CPPUNIT_TEST(testToLower);
    CPPUNIT_TEST(testReverse);
    CPPUNIT_TEST_SUITE_END();
public:
    void testToUpper();
    void testToLower();
    void testReverse();
};

class WStringTrimTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringTrimTest);
    CPPUNIT_TEST(testTrim);
    CPPUNIT_TEST(testTrimLeft);
    CPPUNIT_TEST(testTrimRight);
    CPPUNIT_TEST_SUITE_END();
public:
    void testTrim();
    void testTrimLeft();
    void testTrimRight();
};

class WStringSearchTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringSearchTest);
    CPPUNIT_TEST(testIndexOfChar);
    CPPUNIT_TEST(testIndexOfString);
    CPPUNIT_TEST(testLastIndexOf);
    CPPUNIT_TEST_SUITE_END();
public:
    void testIndexOfChar();
    void testIndexOfString();
    void testLastIndexOf();
};

class WStringSubstringTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringSubstringTest);
    CPPUNIT_TEST(testMid);
    CPPUNIT_TEST(testLeft);
    CPPUNIT_TEST(testRight);
    CPPUNIT_TEST_SUITE_END();
public:
    void testMid();
    void testLeft();
    void testRight();
};

class WStringMutationTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringMutationTest);
    CPPUNIT_TEST(testAppend);
    CPPUNIT_TEST(testAppendChar);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testErase);
    CPPUNIT_TEST(testReplaceChar);
    CPPUNIT_TEST(testClear);
    CPPUNIT_TEST_SUITE_END();
public:
    void testAppend();
    void testAppendChar();
    void testInsert();
    void testErase();
    void testReplaceChar();
    void testClear();
};

class WStringNumericTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringNumericTest);
    CPPUNIT_TEST(testToInt);
    CPPUNIT_TEST(testToLong);
    CPPUNIT_TEST(testToFloat);
    CPPUNIT_TEST(testToDouble);
    CPPUNIT_TEST(testToHex);
    CPPUNIT_TEST(testIsInt);
    CPPUNIT_TEST(testIsFloat);
    CPPUNIT_TEST(testIsHex);
    CPPUNIT_TEST_SUITE_END();
public:
    void testToInt();
    void testToLong();
    void testToFloat();
    void testToDouble();
    void testToHex();
    void testIsInt();
    void testIsFloat();
    void testIsHex();
};

class WStringMiscTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WStringMiscTest);
    CPPUNIT_TEST(testCountChar);
    CPPUNIT_TEST(testTerminateWith);
    CPPUNIT_TEST_SUITE_END();
public:
    void testCountChar();
    void testTerminateWith();
};

#endif
