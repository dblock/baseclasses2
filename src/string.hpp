/*
    baseclasses2
    Originally: Vestris Inc., Geneva, Switzerland, 1994-1999
    https://github.com/dblock/baseclasses2
*/

#ifndef BASE_STRING_HPP
#define BASE_STRING_HPP

#include <platform/include.hpp>

#define CSTRING_CHARTYPE char

template <class C, int StackSize = 18>
class CStringTemplate {
private:
    C m_StackData[StackSize];
    C * m_RealAllocData;
protected:
    C * m_Data;
    unsigned int m_Length;
    unsigned int m_Size;
public:
    inline C * getData() const { return m_Data; }
    inline unsigned int length() const { return m_Length; }
    inline unsigned int getSize() const { return m_Size; }
public:
    static const CStringTemplate EmptyCString;

    /* size and length */
    void setSize(unsigned int size, bool preserve = true);
    void setLength(unsigned int length, C fillChar = 0, bool fill = true);
    void setLength(void);

    /* internal buffer management */
    void copyBuffer(const C * const buffer);
    void copyBuffer(const C * const buffer, int length);
    void initialize(void);

    /* constructors / destructor */
    CStringTemplate(void);
    CStringTemplate(const C * const);
    CStringTemplate(const C * const, int);
    CStringTemplate(const CStringTemplate&);
    CStringTemplate(const C);
    template <int OtherStackSize>
    CStringTemplate(const CStringTemplate<C, OtherStackSize>& other) : CStringTemplate() { copyBuffer(other.c_str(), (int)other.length()); }
    ~CStringTemplate(void);

    /* assignment */
    virtual void operator=(const CStringTemplate&);
    virtual void operator=(const C);
    virtual void operator=(const C * const);
    template <int OtherStackSize>
    void operator=(const CStringTemplate<C, OtherStackSize>& other) { copyBuffer(other.c_str(), (int)other.length()); }

    /* comparison operators */
    inline bool operator<(const CStringTemplate& s) const { return compare(s.m_Data, s.m_Length) < 0; }
    inline bool operator>(const CStringTemplate& s) const { return compare(s.m_Data, s.m_Length) > 0; }
    inline bool operator<=(const CStringTemplate& s) const { return compare(s.m_Data, s.m_Length) <= 0; }
    inline bool operator>=(const CStringTemplate& s) const { return compare(s.m_Data, s.m_Length) >= 0; }
    inline bool operator==(const CStringTemplate& s) const { return equals(s.m_Data, s.m_Length); }
    inline bool operator!=(const CStringTemplate& s) const { return notEquals(s.m_Data, s.m_Length); }
    inline bool operator<(const C * s) const { return compare(s, (int)std::char_traits<C>::length(s)) < 0; }
    inline bool operator>(const C * s) const { return compare(s, (int)std::char_traits<C>::length(s)) > 0; }
    inline bool operator<=(const C * s) const { return compare(s, (int)std::char_traits<C>::length(s)) <= 0; }
    inline bool operator>=(const C * s) const { return compare(s, (int)std::char_traits<C>::length(s)) >= 0; }
    inline bool operator==(const C * s) const { return equals(s, (int)std::char_traits<C>::length(s)); }
    inline bool operator!=(const C * s) const { return notEquals(s, (int)std::char_traits<C>::length(s)); }
    template <int OtherStackSize>
    inline bool operator==(const CStringTemplate<C, OtherStackSize>& s) const { return equals(s.c_str(), (int)s.length()); }
    template <int OtherStackSize>
    inline bool operator!=(const CStringTemplate<C, OtherStackSize>& s) const { return notEquals(s.c_str(), (int)s.length()); }

    /* comparison methods */
    inline int compare(const CStringTemplate& s, int start = 0, bool respectLength = true) const { return compare(s.m_Data, s.m_Length, start, respectLength); }
    int compare(const C * buf, int len, int start = 0, bool respectLength = true) const;
    inline int compareIgnoreCase(const CStringTemplate& s, int start = 0, bool respectLength = true) const { return compareIgnoreCase(s.m_Data, s.m_Length, start, respectLength); }
    int compareIgnoreCase(const C * buf, int len, int start = 0, bool respectLength = true) const;
    inline bool equals(const CStringTemplate& s) const { return equals(s.m_Data, s.m_Length); }
    bool equals(const C * buf, int len) const;
    inline bool equals(const C * buf) const { return equals(buf, (int)std::char_traits<C>::length(buf)); }
    inline bool notEquals(const CStringTemplate& s) const { return notEquals(s.m_Data, s.m_Length); }
    bool notEquals(const C * buf, int len) const;
    inline bool notEquals(const C * buf) const { return notEquals(buf, (int)std::char_traits<C>::length(buf)); }
    inline bool equalsIgnoreCase(const CStringTemplate& s) const { return equalsIgnoreCase(s.m_Data, s.m_Length); }
    bool equalsIgnoreCase(const C * buf, int len) const;
    inline bool equalsIgnoreCase(const C * buf) const { return equalsIgnoreCase(buf, (int)std::char_traits<C>::length(buf)); }
    inline bool equalsIgnoreCase(const CStringTemplate& s, bool caseSensitive) const { return caseSensitive ? equals(s) : equalsIgnoreCase(s); }
    inline bool startsWith(const CStringTemplate& s) const { return startsWith(s.m_Data, s.m_Length); }
    bool startsWith(const C * buf, int len) const;
    inline bool startsWith(const C * buf) const { return startsWith(buf, (int)std::char_traits<C>::length(buf)); }
    inline bool startsWith(const CStringTemplate& s, bool caseSensitive) const { return caseSensitive ? startsWith(s) : startsWithIgnoreCase(s); }
    inline bool startsWithIgnoreCase(const CStringTemplate& s) const { return startsWithIgnoreCase(s.m_Data, s.m_Length); }
    bool startsWithIgnoreCase(const C * buf, int len) const;
    inline bool startsWithIgnoreCase(const C * buf) const { return startsWithIgnoreCase(buf, (int)std::char_traits<C>::length(buf)); }
    inline bool endsWith(const CStringTemplate& s) const { return endsWith(s.m_Data, s.m_Length); }
    bool endsWith(const C * buf, int len) const;
    inline bool endsWith(const C * buf) const { return endsWith(buf, (int)std::char_traits<C>::length(buf)); }
    inline bool endsWith(const CStringTemplate& s, bool caseSensitive) const { return caseSensitive ? endsWith(s) : endsWithIgnoreCase(s); }
    inline bool endsWithIgnoreCase(const CStringTemplate& s) const { return endsWithIgnoreCase(s.m_Data, s.m_Length); }
    bool endsWithIgnoreCase(const C * buf, int len) const;
    inline bool endsWithIgnoreCase(const C * buf) const { return endsWithIgnoreCase(buf, (int)std::char_traits<C>::length(buf)); }

    /* streaming */
    inline basic_ostream<C>& operator<<(basic_ostream<C>& stream) const { stream << m_Data; return stream; }
    basic_istream<C>& operator>>(basic_istream<C>& stream);

    /* access */
    inline const C * const c_str(void) const { return (const C * const)m_Data; }
    inline const C& at(const unsigned int index) const { _S_DEBUG(assert(index < m_Length)); return m_Data[index]; }
    inline C& at(const unsigned int index) { _S_DEBUG(assert(index < m_Length)); return m_Data[index]; }
    inline C& operator[](const unsigned int index) const { _S_DEBUG(assert(index < m_Length)); return m_Data[index]; }
    inline void setAt(const unsigned int index, const C c) { _S_DEBUG(assert(index < m_Length)); m_Data[index] = c; }

    /* concatenation */
    void append(const CStringTemplate&);
    void append(const C);
    void append(const C * const, int);
    void append(const C * const);
    template <int OtherStackSize>
    void append(const CStringTemplate<C, OtherStackSize>& s) { append(s.c_str(), (int)s.length()); }
    template <int OtherStackSize>
    void operator+=(const CStringTemplate<C, OtherStackSize>& s) { append(s); }

    /* static char case ops */
    static inline C toUpperChar(const C ch) { if ((ch <= 'z') && (ch >= 'a')) return (C)(ch - ('a' - 'A')); else return ch; }
    static inline C toLowerChar(const C ch) { if ((ch <= 'Z') && (ch >= 'A')) return (C)(ch + ('a' - 'A')); else return ch; }

    /* move */
    void moveFrom(CStringTemplate&);

    /* clear & erase */
    void clear(void);
    void erase(int start, int count);

    /* insert */
    void insert(const unsigned int pos, const CStringTemplate&);
    void insert(const unsigned int pos, const C);
    void insert(const unsigned int pos, const C * const buffer, int bufferLen = -1);

    /* replace */
    bool replace(const C source, const C target);
    bool replace(const CStringTemplate&, const CStringTemplate&, bool caseSensitive = true);

    /* count */
    int count(const C ch) const;

    /* case */
    void toUpper(void);
    void toLower(void);
    bool hasUpper(int start = 0) const;
    bool hasLower(int start = 0) const;
    void reverse(void);

    /* trim */
    void trimLeft(const C chL = ' ', const C chR = ' ');
    void trimRight(const C chL = ' ', const C chR = ' ');
    inline void trimSpace(void) { trimRight(0, ' '); trimLeft(0, ' '); }
    inline void trim(const C ch = ' ') { trimRight(ch, ch); trimLeft(ch, ch); }

    /* seek */
    int lastIndexOf(const C ch) const;
    int lastIndexOf(const C ch, const int start) const;
    int indexOf(const C ch, const int start = 0) const;
    int indexOf(const CStringTemplate& str, const int start = 0) const;
    int indexOfIgnoreCase(const CStringTemplate& str, const int start = 0) const;
    int indexOf(const C * const buffer, const int bufLen, const int start = 0) const;
    int indexOfIgnoreCase(const C * const buffer, const int bufLen, const int start = 0) const;
    inline int indexOf(const C * const buffer, const int start = 0) const { return indexOf(buffer, (int)std::char_traits<C>::length(buffer), start); }
    inline int indexOfIgnoreCase(const C * const buffer, const int start = 0) const { return indexOfIgnoreCase(buffer, (int)std::char_traits<C>::length(buffer), start); }

    /* numeric checks */
    int getInt(const int start, const int length) const;
    bool isInt(int * value = NULL) const;
    bool isLong(int start, int length, long * value) const;
    bool isInt(int start, int length, int * value) const;
    bool isFloat(float * value = NULL) const;
    bool isLong(long * value = NULL) const;
    bool isHex(int * value = NULL) const;

    /* misc */
    bool terminateWith(const C ch);

    /* concatenation operators */
    inline void operator+=(const CStringTemplate& s) { append(s); }
    inline void operator+=(const C c) { append(c); }
    inline void operator+=(const C * const buffer) { append(buffer); }
    inline void quote(void) { trim((C)'\''); trim((C)'\"'); operator=((C)'\"' + (*this) + (C)'\"'); }
    inline void dequote(void) { trim((C)'\''); trim((C)'\"'); }

    /* substrings */
    CStringTemplate mid(int first, int count) const;
    inline CStringTemplate mid(int first) const { return mid(first, m_Length); }
    inline CStringTemplate left(int count) const { return mid(0, count); }
    inline CStringTemplate right(int count) const { return mid(m_Length - count, count); }
    CStringTemplate extractLine();
    CStringTemplate getLine(int& pos) const;

    /* type conversions */
    static CStringTemplate fromLong(long value, int leftPad = 0, const int base = 10);
    static CStringTemplate fromInt(int value, int leftPad = 0, const int base = 10);
    static CStringTemplate fromFloat(float value, int leftPad = 0, int fracPad = 0, int base = 10);
    static CStringTemplate fromDouble(double value, int leftPad = 0, int fracPad = 0, int base = 10);
    static int toHex(const CStringTemplate& s);
    static int toInt(const CStringTemplate& s);
    static float toFloat(const CStringTemplate& s);
    static double toDouble(const CStringTemplate& s);
    static long toLong(const CStringTemplate& s);

    /* scanners */
    bool readDigit(int& pos, int * digit) const;
    bool readChar(int& pos, C * c) const;
    bool readString(int& pos, CStringTemplate * str) const;
};

template <class C, int StackSize> inline basic_ostream<C>& operator<<(basic_ostream<C>& stream, const CStringTemplate<C, StackSize>& s) { return s.operator<<(stream); }
template <class C, int StackSize> inline basic_istream<C>& operator>>(basic_istream<C>& stream, CStringTemplate<C, StackSize>& s) { return s.operator>>(stream); }

template <class C, int S1, int S2> inline bool operator==(const CStringTemplate<C, S1>& L, const CStringTemplate<C, S2>& R) { return L.equals(R.c_str(), (int)R.length()); }
template <class C, int StackSize> inline bool operator==(const CStringTemplate<C, StackSize>& L, const C * const R) { return L.operator==(R); }
template <class C, int StackSize> inline bool operator==(const C * const L, const CStringTemplate<C, StackSize>& R) { return R.operator==(L); }
template <class C, int S1, int S2> inline bool operator!=(const CStringTemplate<C, S1>& L, const CStringTemplate<C, S2>& R) { return !L.equals(R.c_str(), (int)R.length()); }
template <class C, int StackSize> inline bool operator!=(const CStringTemplate<C, StackSize>& L, const C * const R) { return L.operator!=(R); }
template <class C, int StackSize> inline bool operator!=(const C * const L, const CStringTemplate<C, StackSize>& R) { return R.operator!=(L); }
template <class C, int StackSize> inline bool operator<=(const CStringTemplate<C, StackSize>& L, const C * const R) { return L.operator<=(R); }
template <class C, int StackSize> inline bool operator<=(const C * const L, const CStringTemplate<C, StackSize>& R) { return !(R.operator>(L)); }
template <class C, int StackSize> inline bool operator>=(const CStringTemplate<C, StackSize>& L, const C * const R) { return L.operator>=(R); }
template <class C, int StackSize> inline bool operator>=(const C * const L, const CStringTemplate<C, StackSize>& R) { return !(R.operator<(L)); }
template <class C, int StackSize> inline bool operator<(const CStringTemplate<C, StackSize>& L, const C * const R) { return L.operator<(R); }
template <class C, int StackSize> inline bool operator<(const C * const L, const CStringTemplate<C, StackSize>& R) { return !(R.operator>=(L)); }
template <class C, int StackSize> inline bool operator>(const CStringTemplate<C, StackSize>& L, const C * const R) { return L.operator>(R); }
template <class C, int StackSize> inline bool operator>(const C * const L, const CStringTemplate<C, StackSize>& R) { return !(R.operator<=(L)); }

template <class C, int S1, int S2> inline CStringTemplate<C, S1> operator+(const CStringTemplate<C, S1>& L, const CStringTemplate<C, S2>& R) { CStringTemplate<C, S1> r(L); r += R; return r; }
template <class C, int StackSize> inline CStringTemplate<C, StackSize> operator+(const CStringTemplate<C, StackSize>& L, const C R) { CStringTemplate<C, StackSize> r(L); r += R; return r; }
template <class C, int StackSize> inline CStringTemplate<C, StackSize> operator+(const C L, const CStringTemplate<C, StackSize>& R) { CStringTemplate<C, StackSize> r(L); r += R; return r; }
template <class C, int StackSize> inline CStringTemplate<C, StackSize> operator+(const CStringTemplate<C, StackSize>& L, const C * const R) { CStringTemplate<C, StackSize> r(L); r += R; return r; }
template <class C, int StackSize> inline CStringTemplate<C, StackSize> operator+(const C * const L, const CStringTemplate<C, StackSize>& R) { CStringTemplate<C, StackSize> r(L); r += R; return r; }

typedef CStringTemplate<char>    CStringA;
typedef CStringTemplate<wchar_t> CStringW;
typedef CStringA CString;

#endif
