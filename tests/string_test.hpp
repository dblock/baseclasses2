/*
    baseclasses2
    https://github.com/dblock/baseclasses2
*/

#ifndef STRING_TEST_HPP
#define STRING_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.hpp>

class StringConstructorTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringConstructorTest);
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

class StringComparisonTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringComparisonTest);
    CPPUNIT_TEST(testEquals);
    CPPUNIT_TEST(testNotEquals);
    CPPUNIT_TEST(testEqualsIgnoreCase);
    CPPUNIT_TEST(testOperatorEquals);
    CPPUNIT_TEST(testOperatorLessGreater);
    CPPUNIT_TEST(testCompare);
    CPPUNIT_TEST(testCompareIgnoreCase);
    CPPUNIT_TEST(testStartsWith);
    CPPUNIT_TEST(testStartsWithIgnoreCase);
    CPPUNIT_TEST(testEndsWith);
    CPPUNIT_TEST(testEndsWithIgnoreCase);
    CPPUNIT_TEST_SUITE_END();
public:
    void testEquals();
    void testNotEquals();
    void testEqualsIgnoreCase();
    void testOperatorEquals();
    void testOperatorLessGreater();
    void testCompare();
    void testCompareIgnoreCase();
    void testStartsWith();
    void testStartsWithIgnoreCase();
    void testEndsWith();
    void testEndsWithIgnoreCase();
};

class StringCaseTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringCaseTest);
    CPPUNIT_TEST(testToUpper);
    CPPUNIT_TEST(testToLower);
    CPPUNIT_TEST(testHasUpper);
    CPPUNIT_TEST(testHasLower);
    CPPUNIT_TEST(testToUpperChar);
    CPPUNIT_TEST(testToLowerChar);
    CPPUNIT_TEST(testReverse);
    CPPUNIT_TEST_SUITE_END();
public:
    void testToUpper();
    void testToLower();
    void testHasUpper();
    void testHasLower();
    void testToUpperChar();
    void testToLowerChar();
    void testReverse();
};

class StringTrimTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringTrimTest);
    CPPUNIT_TEST(testTrim);
    CPPUNIT_TEST(testTrimLeft);
    CPPUNIT_TEST(testTrimRight);
    CPPUNIT_TEST(testTrimSpace);
    CPPUNIT_TEST_SUITE_END();
public:
    void testTrim();
    void testTrimLeft();
    void testTrimRight();
    void testTrimSpace();
};

class StringSearchTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringSearchTest);
    CPPUNIT_TEST(testIndexOfChar);
    CPPUNIT_TEST(testIndexOfString);
    CPPUNIT_TEST(testIndexOfIgnoreCase);
    CPPUNIT_TEST(testLastIndexOf);
    CPPUNIT_TEST_SUITE_END();
public:
    void testIndexOfChar();
    void testIndexOfString();
    void testIndexOfIgnoreCase();
    void testLastIndexOf();
};

class StringSubstringTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringSubstringTest);
    CPPUNIT_TEST(testMid);
    CPPUNIT_TEST(testLeft);
    CPPUNIT_TEST(testRight);
    CPPUNIT_TEST(testGetLine);
    CPPUNIT_TEST(testExtractLine);
    CPPUNIT_TEST_SUITE_END();
public:
    void testMid();
    void testLeft();
    void testRight();
    void testGetLine();
    void testExtractLine();
};

class StringMutationTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringMutationTest);
    CPPUNIT_TEST(testAppend);
    CPPUNIT_TEST(testAppendChar);
    CPPUNIT_TEST(testAppendOperator);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testErase);
    CPPUNIT_TEST(testReplaceChar);
    CPPUNIT_TEST(testReplaceString);
    CPPUNIT_TEST(testReplaceRange);
    CPPUNIT_TEST(testClear);
    CPPUNIT_TEST(testMoveFrom);
    CPPUNIT_TEST_SUITE_END();
public:
    void testAppend();
    void testAppendChar();
    void testAppendOperator();
    void testInsert();
    void testErase();
    void testReplaceChar();
    void testReplaceString();
    void testReplaceRange();
    void testClear();
    void testMoveFrom();
};

class StringNumericTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringNumericTest);
    CPPUNIT_TEST(testFromInt);
    CPPUNIT_TEST(testFromLong);
    CPPUNIT_TEST(testFromFloat);
    CPPUNIT_TEST(testFromDouble);
    CPPUNIT_TEST(testToInt);
    CPPUNIT_TEST(testToLong);
    CPPUNIT_TEST(testToFloat);
    CPPUNIT_TEST(testToHex);
    CPPUNIT_TEST(testIsInt);
    CPPUNIT_TEST(testIsFloat);
    CPPUNIT_TEST(testIsHex);
    CPPUNIT_TEST_SUITE_END();
public:
    void testFromInt();
    void testFromLong();
    void testFromFloat();
    void testFromDouble();
    void testToInt();
    void testToLong();
    void testToFloat();
    void testToHex();
    void testIsInt();
    void testIsFloat();
    void testIsHex();
};

class StringMiscTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringMiscTest);
    CPPUNIT_TEST(testCountChar);
    CPPUNIT_TEST(testCountRange);
    CPPUNIT_TEST(testQuote);
    CPPUNIT_TEST(testDequote);
    CPPUNIT_TEST(testTerminateWith);
    CPPUNIT_TEST(testRemoveDuplicate);
    CPPUNIT_TEST(testRemove);
    CPPUNIT_TEST(testReadDigit);
    CPPUNIT_TEST(testReadChar);
    CPPUNIT_TEST(testReadString);
    CPPUNIT_TEST_SUITE_END();
public:
    void testCountChar();
    void testCountRange();
    void testQuote();
    void testDequote();
    void testTerminateWith();
    void testRemoveDuplicate();
    void testRemove();
    void testReadDigit();
    void testReadChar();
    void testReadString();
};

#endif
