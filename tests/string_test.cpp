/*
    baseclasses2
    https://github.com/dblock/baseclasses2
*/

#include "string_test.hpp"

/* ─── Constructor / Assignment ─────────────────────────────────────────── */

void StringConstructorTest::testDefaultConstructor() {
    CString s;
    CPPUNIT_ASSERT_EQUAL(0u, s.length());
    CPPUNIT_ASSERT(s.c_str() != nullptr);
    CPPUNIT_ASSERT_EQUAL('\0', s.c_str()[0]);
}

void StringConstructorTest::testCStrConstructor() {
    CString s("hello");
    CPPUNIT_ASSERT_EQUAL(5u, s.length());
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
}

void StringConstructorTest::testCStrLenConstructor() {
    CString s("hello world", 5);
    CPPUNIT_ASSERT_EQUAL(5u, s.length());
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
}

void StringConstructorTest::testCopyConstructor() {
    CString a("copy me");
    CString b(a);
    CPPUNIT_ASSERT_EQUAL(std::string("copy me"), std::string(b.c_str()));
    a.clear();
    CPPUNIT_ASSERT_EQUAL(std::string("copy me"), std::string(b.c_str()));
}

void StringConstructorTest::testCharConstructor() {
    CString s('X');
    CPPUNIT_ASSERT_EQUAL(1u, s.length());
    CPPUNIT_ASSERT_EQUAL('X', s.at(0));
}

void StringConstructorTest::testAssignCStr() {
    CString s;
    s = "world";
    CPPUNIT_ASSERT_EQUAL(std::string("world"), std::string(s.c_str()));
}

void StringConstructorTest::testAssignChar() {
    CString s;
    s = 'Z';
    CPPUNIT_ASSERT_EQUAL(1u, s.length());
    CPPUNIT_ASSERT_EQUAL('Z', s.at(0));
}

void StringConstructorTest::testAssignString() {
    CString a("source");
    CString b;
    b = a;
    CPPUNIT_ASSERT_EQUAL(std::string("source"), std::string(b.c_str()));
}

/* ─── Comparison ────────────────────────────────────────────────────────── */

void StringComparisonTest::testEquals() {
    CString a("abc"), b("abc"), c("ABC");
    CPPUNIT_ASSERT(a.equals(b));
    CPPUNIT_ASSERT(!a.equals(c));
    CPPUNIT_ASSERT(a.equals("abc"));
    CPPUNIT_ASSERT(!a.equals("abcd"));
}

void StringComparisonTest::testNotEquals() {
    CString a("abc"), b("xyz");
    CPPUNIT_ASSERT(a.notEquals(b));
    CPPUNIT_ASSERT(!a.notEquals(a));
}

void StringComparisonTest::testEqualsIgnoreCase() {
    CString a("Hello");
    CPPUNIT_ASSERT(a.equalsIgnoreCase("HELLO"));
    CPPUNIT_ASSERT(a.equalsIgnoreCase("hello"));
    CPPUNIT_ASSERT(!a.equalsIgnoreCase("hell"));
}

void StringComparisonTest::testOperatorEquals() {
    CString a("foo"), b("foo"), c("bar");
    CPPUNIT_ASSERT(a == b);
    CPPUNIT_ASSERT(!(a == c));
    CPPUNIT_ASSERT(a != c);
    CPPUNIT_ASSERT(a == "foo");
    CPPUNIT_ASSERT("foo" == a);
}

void StringComparisonTest::testOperatorLessGreater() {
    CString a("apple"), b("banana");
    CPPUNIT_ASSERT(a < b);
    CPPUNIT_ASSERT(b > a);
    CPPUNIT_ASSERT(a <= b);
    CPPUNIT_ASSERT(b >= a);
    CPPUNIT_ASSERT(a <= a);
    CPPUNIT_ASSERT(a >= a);
}

void StringComparisonTest::testCompare() {
    CString s("abcdef");
    CPPUNIT_ASSERT_EQUAL(0, s.compare("abcdef", 6));
    CPPUNIT_ASSERT(s.compare("xyz", 3) < 0);
    CPPUNIT_ASSERT(s.compare("aaa", 3) > 0);
    /* start offset */
    CPPUNIT_ASSERT_EQUAL(0, s.compare("cde", 3, 2, false));
}

void StringComparisonTest::testCompareIgnoreCase() {
    CString s("Hello");
    CPPUNIT_ASSERT_EQUAL(0, s.compareIgnoreCase("HELLO", 5));
    CPPUNIT_ASSERT(s.compareIgnoreCase("WORLD", 5) < 0);
}

void StringComparisonTest::testStartsWith() {
    CString s("foobar");
    CPPUNIT_ASSERT(s.startsWith("foo"));
    CPPUNIT_ASSERT(!s.startsWith("bar"));
    CPPUNIT_ASSERT(!s.startsWith("foobarbaz"));
}

void StringComparisonTest::testStartsWithIgnoreCase() {
    CString s("FooBar");
    CPPUNIT_ASSERT(s.startsWithIgnoreCase("FOO"));
    CPPUNIT_ASSERT(s.startsWithIgnoreCase("foo"));
    CPPUNIT_ASSERT(!s.startsWithIgnoreCase("bar"));
}

void StringComparisonTest::testEndsWith() {
    CString s("foobar");
    CPPUNIT_ASSERT(s.endsWith("bar"));
    CPPUNIT_ASSERT(!s.endsWith("foo"));
    CPPUNIT_ASSERT(!s.endsWith("foobarbaz"));
}

void StringComparisonTest::testEndsWithIgnoreCase() {
    CString s("FooBar");
    CPPUNIT_ASSERT(s.endsWithIgnoreCase("BAR"));
    CPPUNIT_ASSERT(s.endsWithIgnoreCase("bar"));
    CPPUNIT_ASSERT(!s.endsWithIgnoreCase("foo"));
}

/* ─── Case ──────────────────────────────────────────────────────────────── */

void StringCaseTest::testToUpper() {
    CString s("Hello World");
    s.toUpper();
    CPPUNIT_ASSERT_EQUAL(std::string("HELLO WORLD"), std::string(s.c_str()));
}

void StringCaseTest::testToLower() {
    CString s("Hello World");
    s.toLower();
    CPPUNIT_ASSERT_EQUAL(std::string("hello world"), std::string(s.c_str()));
}

void StringCaseTest::testHasUpper() {
    CString a("Hello"), b("hello");
    CPPUNIT_ASSERT(a.hasUpper());
    CPPUNIT_ASSERT(!b.hasUpper());
    CPPUNIT_ASSERT(!a.hasUpper(1));
}

void StringCaseTest::testHasLower() {
    CString a("Hello"), b("HELLO");
    CPPUNIT_ASSERT(a.hasLower());
    CPPUNIT_ASSERT(!b.hasLower());
}

void StringCaseTest::testToUpperChar() {
    CPPUNIT_ASSERT_EQUAL('A', CString::toUpperChar('a'));
    CPPUNIT_ASSERT_EQUAL('Z', CString::toUpperChar('z'));
    CPPUNIT_ASSERT_EQUAL('A', CString::toUpperChar('A'));
    CPPUNIT_ASSERT_EQUAL('1', CString::toUpperChar('1'));
}

void StringCaseTest::testToLowerChar() {
    CPPUNIT_ASSERT_EQUAL('a', CString::toLowerChar('A'));
    CPPUNIT_ASSERT_EQUAL('z', CString::toLowerChar('Z'));
    CPPUNIT_ASSERT_EQUAL('a', CString::toLowerChar('a'));
    CPPUNIT_ASSERT_EQUAL('1', CString::toLowerChar('1'));
}

void StringCaseTest::testReverse() {
    CString s("abcde");
    s.reverse();
    CPPUNIT_ASSERT_EQUAL(std::string("edcba"), std::string(s.c_str()));
    CString even("abcd");
    even.reverse();
    CPPUNIT_ASSERT_EQUAL(std::string("dcba"), std::string(even.c_str()));
}

/* ─── Trim ──────────────────────────────────────────────────────────────── */

void StringTrimTest::testTrim() {
    CString s("  hello  ");
    s.trim();
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
    CString s2("***hi***");
    s2.trim('*');
    CPPUNIT_ASSERT_EQUAL(std::string("hi"), std::string(s2.c_str()));
}

void StringTrimTest::testTrimLeft() {
    CString s("   hello");
    s.trimLeft();
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
}

void StringTrimTest::testTrimRight() {
    CString s("hello   ");
    s.trimRight();
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
}

void StringTrimTest::testTrimSpace() {
    CString s("  hi  ");
    s.trimSpace();
    CPPUNIT_ASSERT_EQUAL(std::string("hi"), std::string(s.c_str()));
}

/* ─── Search ────────────────────────────────────────────────────────────── */

void StringSearchTest::testIndexOfChar() {
    CString s("hello world");
    CPPUNIT_ASSERT_EQUAL(4, s.indexOf('o'));
    CPPUNIT_ASSERT_EQUAL(7, s.indexOf('o', 5));
    CPPUNIT_ASSERT_EQUAL(-1, s.indexOf('z'));
}

void StringSearchTest::testIndexOfString() {
    CString s("foobar foobar");
    CPPUNIT_ASSERT_EQUAL(0, s.indexOf(CString("foo")));
    CPPUNIT_ASSERT_EQUAL(7, s.indexOf(CString("foo"), 1));
    CPPUNIT_ASSERT_EQUAL(-1, s.indexOf(CString("baz")));
}

void StringSearchTest::testIndexOfIgnoreCase() {
    CString s("Hello World");
    CPPUNIT_ASSERT_EQUAL(6, s.indexOfIgnoreCase(CString("WORLD")));
    CPPUNIT_ASSERT_EQUAL(0, s.indexOfIgnoreCase(CString("hello")));
    CPPUNIT_ASSERT_EQUAL(-1, s.indexOfIgnoreCase(CString("xyz")));
}

void StringSearchTest::testLastIndexOf() {
    CString s("abcabc");
    CPPUNIT_ASSERT_EQUAL(5, s.lastIndexOf('c'));
    CPPUNIT_ASSERT_EQUAL(2, s.lastIndexOf('c', 4));
    CPPUNIT_ASSERT_EQUAL(-1, s.lastIndexOf('z'));
}

/* ─── Substrings ────────────────────────────────────────────────────────── */

void StringSubstringTest::testMid() {
    CString s("hello world");
    CString r;
    s.mid(6, &r);
    CPPUNIT_ASSERT_EQUAL(std::string("world"), std::string(r.c_str()));
    s.mid(0, 5, &r);
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(r.c_str()));
}

void StringSubstringTest::testLeft() {
    CString s("hello world");
    CString r;
    s.left(5, &r);
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(r.c_str()));
}

void StringSubstringTest::testRight() {
    CString s("hello world");
    CString r;
    s.right(5, &r);
    CPPUNIT_ASSERT_EQUAL(std::string("world"), std::string(r.c_str()));
}

void StringSubstringTest::testGetLine() {
    CString s("line1\nline2\nline3");
    CString r;
    int pos = 0;
    CPPUNIT_ASSERT(s.getLine(&r, pos) > 0);
    CPPUNIT_ASSERT_EQUAL(std::string("line1"), std::string(r.c_str()));
    CPPUNIT_ASSERT(s.getLine(&r, pos) > 0);
    CPPUNIT_ASSERT_EQUAL(std::string("line2"), std::string(r.c_str()));
    CPPUNIT_ASSERT(s.getLine(&r, pos) > 0);
    CPPUNIT_ASSERT_EQUAL(std::string("line3"), std::string(r.c_str()));
    CPPUNIT_ASSERT_EQUAL(0, s.getLine(&r, pos));
}

void StringSubstringTest::testExtractLine() {
    CString s("first\nsecond");
    CString r;
    s.extractLine(&r);
    CPPUNIT_ASSERT_EQUAL(std::string("first"), std::string(r.c_str()));
    CPPUNIT_ASSERT_EQUAL(std::string("second"), std::string(s.c_str()));
}

/* ─── Mutation ──────────────────────────────────────────────────────────── */

void StringMutationTest::testAppend() {
    CString s("foo");
    s.append(CString("bar"));
    CPPUNIT_ASSERT_EQUAL(std::string("foobar"), std::string(s.c_str()));
}

void StringMutationTest::testAppendChar() {
    CString s("fo");
    s.append('o');
    CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(s.c_str()));
}

void StringMutationTest::testAppendOperator() {
    CString s("hello");
    s += " world";
    CPPUNIT_ASSERT_EQUAL(std::string("hello world"), std::string(s.c_str()));
    s += '!';
    CPPUNIT_ASSERT_EQUAL(std::string("hello world!"), std::string(s.c_str()));
}

void StringMutationTest::testInsert() {
    CString s("helo");
    s.insert(3, 'l');
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
    CString s2("world");
    s2.insert(0, CString("hello "));
    CPPUNIT_ASSERT_EQUAL(std::string("hello world"), std::string(s2.c_str()));
}

void StringMutationTest::testErase() {
    CString s("hello world");
    s.erase(5, 6);
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
    s.erase(0, 3);
    CPPUNIT_ASSERT_EQUAL(std::string("lo"), std::string(s.c_str()));
}

void StringMutationTest::testReplaceChar() {
    CString s("hello");
    CPPUNIT_ASSERT(s.replace('l', 'r'));
    CPPUNIT_ASSERT_EQUAL(std::string("herro"), std::string(s.c_str()));
    CPPUNIT_ASSERT(!s.replace('z', 'x'));
}

void StringMutationTest::testReplaceString() {
    CString s("foo bar foo");
    CPPUNIT_ASSERT(s.replace(CString("foo"), CString("baz")));
    CPPUNIT_ASSERT_EQUAL(std::string("baz bar baz"), std::string(s.c_str()));
    /* case-insensitive replace */
    CString s2("Hello World");
    CPPUNIT_ASSERT(s2.replace(CString("hello"), CString("Hi"), false));
    CPPUNIT_ASSERT_EQUAL(std::string("Hi World"), std::string(s2.c_str()));
}

void StringMutationTest::testReplaceRange() {
    CString s("a1b2c3");
    s.replace('1', '3', '0');
    CPPUNIT_ASSERT_EQUAL(std::string("a0b0c0"), std::string(s.c_str()));
}

void StringMutationTest::testClear() {
    CString s("hello");
    s.clear();
    CPPUNIT_ASSERT_EQUAL(0u, s.length());
    CPPUNIT_ASSERT_EQUAL('\0', s.c_str()[0]);
}

void StringMutationTest::testMoveFrom() {
    CString a("moveable");
    CString b;
    b.moveFrom(a);
    CPPUNIT_ASSERT_EQUAL(std::string("moveable"), std::string(b.c_str()));
    CPPUNIT_ASSERT_EQUAL(0u, a.length());
}

/* ─── Numeric ───────────────────────────────────────────────────────────── */

void StringNumericTest::testFromInt() {
    CPPUNIT_ASSERT_EQUAL(std::string("0"),   std::string(CString::fromInt(0).c_str()));
    CPPUNIT_ASSERT_EQUAL(std::string("42"),  std::string(CString::fromInt(42).c_str()));
    CPPUNIT_ASSERT_EQUAL(std::string("-7"),  std::string(CString::fromInt(-7).c_str()));
    CPPUNIT_ASSERT_EQUAL(std::string("007"), std::string(CString::fromInt(7, 3).c_str()));
}

void StringNumericTest::testFromLong() {
    CPPUNIT_ASSERT_EQUAL(std::string("1000000"), std::string(CString::fromLong(1000000L).c_str()));
    CPPUNIT_ASSERT_EQUAL(std::string("-1"),      std::string(CString::fromLong(-1L).c_str()));
}

void StringNumericTest::testFromFloat() {
    CString s = CString::fromFloat(3.14f, 0, 2);
    CPPUNIT_ASSERT(s.startsWith("3.1"));
}

void StringNumericTest::testFromDouble() {
    CString s = CString::fromDouble(2.718, 0, 3);
    CPPUNIT_ASSERT(s.startsWith("2.71"));
}

void StringNumericTest::testToInt() {
    CPPUNIT_ASSERT_EQUAL(42,  CString::toInt(CString("42")));
    CPPUNIT_ASSERT_EQUAL(-7,  CString::toInt(CString("-7")));
    CPPUNIT_ASSERT_EQUAL(0,   CString::toInt(CString("")));
}

void StringNumericTest::testToLong() {
    CPPUNIT_ASSERT_EQUAL(1000000L, CString::toLong(CString("1000000")));
}

void StringNumericTest::testToFloat() {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14f, CString::toFloat(CString("3.14")), 0.001f);
}

void StringNumericTest::testToHex() {
    CPPUNIT_ASSERT_EQUAL(255, CString::toHex(CString("ff")));
    CPPUNIT_ASSERT_EQUAL(255, CString::toHex(CString("FF")));
}

void StringNumericTest::testIsInt() {
    int v = 0;
    CPPUNIT_ASSERT(CString("42").isInt(&v));
    CPPUNIT_ASSERT_EQUAL(42, v);
    CPPUNIT_ASSERT(CString("-1").isInt(&v));
    CPPUNIT_ASSERT_EQUAL(-1, v);
    CPPUNIT_ASSERT(!CString("3.14").isInt());
    CPPUNIT_ASSERT(!CString("abc").isInt());
    CPPUNIT_ASSERT(!CString("").isInt());
}

void StringNumericTest::testIsFloat() {
    float f = 0;
    CPPUNIT_ASSERT(CString("3.14").isFloat(&f));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.14f, f, 0.001f);
    CPPUNIT_ASSERT(CString("42").isFloat());
    CPPUNIT_ASSERT(!CString("abc").isFloat());
}

void StringNumericTest::testIsHex() {
    int v = 0;
    CPPUNIT_ASSERT(CString("ff").isHex(&v));
    CPPUNIT_ASSERT_EQUAL(255, v);
    CPPUNIT_ASSERT(CString("FF").isHex());
    CPPUNIT_ASSERT(!CString("xyz").isHex());
    CPPUNIT_ASSERT(!CString("").isHex());
}

/* ─── Misc ──────────────────────────────────────────────────────────────── */

void StringMiscTest::testCountChar() {
    CString s("banana");
    CPPUNIT_ASSERT_EQUAL(3, s.count('a'));
    CPPUNIT_ASSERT_EQUAL(0, s.count('z'));
}

void StringMiscTest::testCountRange() {
    CString s("abc123");
    CPPUNIT_ASSERT_EQUAL(3, s.count('0', '9'));
    CPPUNIT_ASSERT_EQUAL(3, s.count('a', 'c'));
}

void StringMiscTest::testQuote() {
    CString s("hello");
    s.quote();
    CPPUNIT_ASSERT_EQUAL(std::string("\"hello\""), std::string(s.c_str()));
}

void StringMiscTest::testDequote() {
    CString s("\"hello\"");
    s.dequote();
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(s.c_str()));
    CString s2("'world'");
    s2.dequote();
    CPPUNIT_ASSERT_EQUAL(std::string("world"), std::string(s2.c_str()));
}

void StringMiscTest::testTerminateWith() {
    CString s("hello");
    CPPUNIT_ASSERT(s.terminateWith('/'));
    CPPUNIT_ASSERT_EQUAL(std::string("hello/"), std::string(s.c_str()));
    CPPUNIT_ASSERT(!s.terminateWith('/'));
    CPPUNIT_ASSERT_EQUAL(std::string("hello/"), std::string(s.c_str()));
}

void StringMiscTest::testRemoveDuplicate() {
    /* collapses consecutive pairs where both chars fall within [chLeft, chRight] */
    CString s("foo//bar");
    s.removeDuplicate('/', '/');
    CPPUNIT_ASSERT_EQUAL(std::string("foo/bar"), std::string(s.c_str()));
    CString s2("a  b");
    s2.removeDuplicate(' ', ' ');
    CPPUNIT_ASSERT_EQUAL(std::string("a b"), std::string(s2.c_str()));
}

void StringMiscTest::testRemove() {
    CString s("abc123");
    s.remove('0', '9');
    CPPUNIT_ASSERT_EQUAL(std::string("abc"), std::string(s.c_str()));
}

void StringMiscTest::testReadDigit() {
    CString s("3abc");
    int pos = 0, d = -1;
    CPPUNIT_ASSERT(s.readDigit(pos, &d));
    CPPUNIT_ASSERT_EQUAL(3, d);
    CPPUNIT_ASSERT_EQUAL(1, pos);
    CPPUNIT_ASSERT(!s.readDigit(pos, &d));
}

void StringMiscTest::testReadChar() {
    CString s("hi");
    int pos = 0;
    char c = 0;
    CPPUNIT_ASSERT(s.readChar(pos, &c));
    CPPUNIT_ASSERT_EQUAL('h', c);
    CPPUNIT_ASSERT(s.readChar(pos, &c));
    CPPUNIT_ASSERT_EQUAL('i', c);
    CPPUNIT_ASSERT(!s.readChar(pos, &c));
}

void StringMiscTest::testReadString() {
    CString s("hello world");
    int pos = 0;
    CString token;
    CPPUNIT_ASSERT(s.readString(pos, &token));
    CPPUNIT_ASSERT_EQUAL(std::string("hello"), std::string(token.c_str()));
    pos++;
    CPPUNIT_ASSERT(s.readString(pos, &token));
    CPPUNIT_ASSERT_EQUAL(std::string("world"), std::string(token.c_str()));
}
