/*
    baseclasses2
    https://github.com/dblock/baseclasses2
*/

#include "wstring_test.hpp"
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(WStringConstructorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringComparisonTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringCaseTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringTrimTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringSearchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringSubstringTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringMutationTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringNumericTest);
CPPUNIT_TEST_SUITE_REGISTRATION(WStringMiscTest);

/* --- Constructor tests --- */

void WStringConstructorTest::testDefaultConstructor() {
    CStringW s;
    CPPUNIT_ASSERT_EQUAL(0u, s.length());
    CPPUNIT_ASSERT(s.c_str() != nullptr);
    CPPUNIT_ASSERT_EQUAL(L'\0', s.c_str()[0]);
}

void WStringConstructorTest::testCStrConstructor() {
    CStringW s(L"hello");
    CPPUNIT_ASSERT_EQUAL(5u, s.length());
    CPPUNIT_ASSERT(std::wstring(L"hello") == s.c_str());
}

void WStringConstructorTest::testCStrLenConstructor() {
    CStringW s(L"hello", 3);
    CPPUNIT_ASSERT_EQUAL(3u, s.length());
    CPPUNIT_ASSERT(std::wstring(L"hel") == s.c_str());
}

void WStringConstructorTest::testCopyConstructor() {
    CStringW a(L"world");
    CStringW b(a);
    CPPUNIT_ASSERT(std::wstring(L"world") == b.c_str());
}

void WStringConstructorTest::testCharConstructor() {
    CStringW s(L'X');
    CPPUNIT_ASSERT_EQUAL(1u, s.length());
    CPPUNIT_ASSERT_EQUAL(L'X', s.c_str()[0]);
}

void WStringConstructorTest::testAssignCStr() {
    CStringW s;
    s = L"test";
    CPPUNIT_ASSERT(std::wstring(L"test") == s.c_str());
}

void WStringConstructorTest::testAssignChar() {
    CStringW s;
    s = L'Z';
    CPPUNIT_ASSERT_EQUAL(1u, s.length());
    CPPUNIT_ASSERT_EQUAL(L'Z', s.c_str()[0]);
}

void WStringConstructorTest::testAssignString() {
    CStringW a(L"foo");
    CStringW b;
    b = a;
    CPPUNIT_ASSERT(std::wstring(L"foo") == b.c_str());
}

/* --- Comparison tests --- */

void WStringComparisonTest::testEquals() {
    CStringW a(L"abc"), b(L"abc"), c(L"xyz");
    CPPUNIT_ASSERT(a.equals(b));
    CPPUNIT_ASSERT(!a.equals(c));
}

void WStringComparisonTest::testNotEquals() {
    CStringW a(L"abc"), b(L"xyz");
    CPPUNIT_ASSERT(a.notEquals(b));
    CPPUNIT_ASSERT(!a.notEquals(a));
}

void WStringComparisonTest::testEqualsIgnoreCase() {
    CStringW a(L"hello");
    CPPUNIT_ASSERT(a.equalsIgnoreCase(L"HELLO"));
    CPPUNIT_ASSERT(!a.equalsIgnoreCase(L"world"));
}

void WStringComparisonTest::testOperatorEquals() {
    CStringW a(L"foo");
    CPPUNIT_ASSERT(a == L"foo");
    CPPUNIT_ASSERT(!(a == L"bar"));
}

void WStringComparisonTest::testStartsWith() {
    CStringW s(L"foobar");
    CPPUNIT_ASSERT(s.startsWith(L"foo"));
    CPPUNIT_ASSERT(!s.startsWith(L"bar"));
}

void WStringComparisonTest::testEndsWith() {
    CStringW s(L"foobar");
    CPPUNIT_ASSERT(s.endsWith(L"bar"));
    CPPUNIT_ASSERT(!s.endsWith(L"foo"));
}

/* --- Case tests --- */

void WStringCaseTest::testToUpper() {
    CStringW s(L"hello");
    s.toUpper();
    CPPUNIT_ASSERT(std::wstring(L"HELLO") == s.c_str());
}

void WStringCaseTest::testToLower() {
    CStringW s(L"WORLD");
    s.toLower();
    CPPUNIT_ASSERT(std::wstring(L"world") == s.c_str());
}

void WStringCaseTest::testReverse() {
    CStringW s(L"abcde");
    s.reverse();
    CPPUNIT_ASSERT(std::wstring(L"edcba") == s.c_str());
}

/* --- Trim tests --- */

void WStringTrimTest::testTrim() {
    CStringW s(L"  hello  ");
    s.trim();
    CPPUNIT_ASSERT(std::wstring(L"hello") == s.c_str());
}

void WStringTrimTest::testTrimLeft() {
    CStringW s(L"  hello");
    s.trimLeft();
    CPPUNIT_ASSERT(std::wstring(L"hello") == s.c_str());
}

void WStringTrimTest::testTrimRight() {
    CStringW s(L"hello  ");
    s.trimRight();
    CPPUNIT_ASSERT(std::wstring(L"hello") == s.c_str());
}

/* --- Search tests --- */

void WStringSearchTest::testIndexOfChar() {
    CStringW s(L"banana");
    CPPUNIT_ASSERT_EQUAL(1, s.indexOf(L'a'));
    CPPUNIT_ASSERT_EQUAL(-1, s.indexOf(L'z'));
}

void WStringSearchTest::testIndexOfString() {
    CStringW s(L"hello world");
    CPPUNIT_ASSERT_EQUAL(6, s.indexOf(L"world"));
    CPPUNIT_ASSERT_EQUAL(-1, s.indexOf(L"xyz"));
}

void WStringSearchTest::testLastIndexOf() {
    CStringW s(L"banana");
    CPPUNIT_ASSERT_EQUAL(5, s.lastIndexOf(L'a'));
}

/* --- Substring tests --- */

void WStringSubstringTest::testMid() {
    CStringW s(L"hello world");
    CPPUNIT_ASSERT(std::wstring(L"world") == s.mid(6, 5).c_str());
}

void WStringSubstringTest::testLeft() {
    CStringW s(L"hello");
    CPPUNIT_ASSERT(std::wstring(L"hel") == s.left(3).c_str());
}

void WStringSubstringTest::testRight() {
    CStringW s(L"hello");
    CPPUNIT_ASSERT(std::wstring(L"llo") == s.right(3).c_str());
}

/* --- Mutation tests --- */

void WStringMutationTest::testAppend() {
    CStringW s(L"hello");
    s.append(L" world");
    CPPUNIT_ASSERT(std::wstring(L"hello world") == s.c_str());
}

void WStringMutationTest::testAppendChar() {
    CStringW s(L"hello");
    s.append(L'!');
    CPPUNIT_ASSERT(std::wstring(L"hello!") == s.c_str());
}

void WStringMutationTest::testInsert() {
    CStringW s(L"helo");
    s.insert(3, L'l');
    CPPUNIT_ASSERT(std::wstring(L"hello") == s.c_str());
}

void WStringMutationTest::testErase() {
    CStringW s(L"hello");
    s.erase(1, 3);
    CPPUNIT_ASSERT(std::wstring(L"ho") == s.c_str());
}

void WStringMutationTest::testReplaceChar() {
    CStringW s(L"hello");
    CPPUNIT_ASSERT(s.replace(L'l', L'r'));
    CPPUNIT_ASSERT(std::wstring(L"herro") == s.c_str());
    CPPUNIT_ASSERT(!s.replace(L'z', L'x'));
}

void WStringMutationTest::testClear() {
    CStringW s(L"hello");
    s.clear();
    CPPUNIT_ASSERT_EQUAL(0u, s.length());
    CPPUNIT_ASSERT_EQUAL(L'\0', s.c_str()[0]);
}

/* --- Numeric tests --- */

void WStringNumericTest::testToInt() {
    CPPUNIT_ASSERT_EQUAL(42,  CStringW::toInt(CStringW(L"42")));
    CPPUNIT_ASSERT_EQUAL(-7, CStringW::toInt(CStringW(L"-7")));
    CPPUNIT_ASSERT_EQUAL(0,  CStringW::toInt(CStringW(L"")));
}

void WStringNumericTest::testToLong() {
    CPPUNIT_ASSERT_EQUAL(1000000L, CStringW::toLong(CStringW(L"1000000")));
    CPPUNIT_ASSERT_EQUAL(0L,       CStringW::toLong(CStringW(L"")));
}

void WStringNumericTest::testToFloat() {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14f, CStringW::toFloat(CStringW(L"3.14")), 0.001f);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f,  CStringW::toFloat(CStringW(L"")),     0.001f);
}

void WStringNumericTest::testToDouble() {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.718, CStringW::toDouble(CStringW(L"2.718")), 0.001);
}

void WStringNumericTest::testToHex() {
    CPPUNIT_ASSERT_EQUAL(255, CStringW::toHex(CStringW(L"ff")));
    CPPUNIT_ASSERT_EQUAL(0,   CStringW::toHex(CStringW(L"")));
}

void WStringNumericTest::testIsInt() {
    int v = 0;
    CPPUNIT_ASSERT(CStringW(L"42").isInt(&v));
    CPPUNIT_ASSERT_EQUAL(42, v);
    CPPUNIT_ASSERT(CStringW(L"-1").isInt(&v));
    CPPUNIT_ASSERT_EQUAL(-1, v);
    CPPUNIT_ASSERT(!CStringW(L"3.14").isInt());
    CPPUNIT_ASSERT(!CStringW(L"abc").isInt());
    CPPUNIT_ASSERT(!CStringW(L"").isInt());
}

void WStringNumericTest::testIsFloat() {
    float f = 0;
    CPPUNIT_ASSERT(CStringW(L"3.14").isFloat(&f));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14f, f, 0.001f);
    CPPUNIT_ASSERT(CStringW(L"42").isFloat());
    CPPUNIT_ASSERT(!CStringW(L"abc").isFloat());
}

void WStringNumericTest::testIsHex() {
    int v = 0;
    CPPUNIT_ASSERT(CStringW(L"ff").isHex(&v));
    CPPUNIT_ASSERT_EQUAL(255, v);
    CPPUNIT_ASSERT(!CStringW(L"xyz").isHex());
}

/* --- Misc tests --- */

void WStringMiscTest::testCountChar() {
    CStringW s(L"banana");
    CPPUNIT_ASSERT_EQUAL(3, s.count(L'a'));
    CPPUNIT_ASSERT_EQUAL(0, s.count(L'z'));
}

void WStringMiscTest::testTerminateWith() {
    CStringW s(L"hello");
    CPPUNIT_ASSERT(s.terminateWith(L'/'));
    CPPUNIT_ASSERT(std::wstring(L"hello/") == s.c_str());
    CPPUNIT_ASSERT(!s.terminateWith(L'/'));
    CPPUNIT_ASSERT(std::wstring(L"hello/") == s.c_str());
}
