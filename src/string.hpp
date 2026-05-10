/*
    baseclasses2
    Originally: Vestris Inc., Geneva, Switzerland, 1994-1999
    https://github.com/dblock/baseclasses2
*/

#ifndef BASE_STRING_HPP
#define BASE_STRING_HPP

#include <platform/include.hpp>

#define CSTRING_STACK_SIZE 18
#define CSTRING_CHARTYPE char

template <class C>
class CStringTemplate {
private:
    C m_StackData[CSTRING_STACK_SIZE];
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
    static const CStringTemplate<C> EmptyCString;

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
    CStringTemplate(const CStringTemplate<C>&);
    CStringTemplate(const C);
    ~CStringTemplate(void);

    /* assignment */
    virtual void operator=(const CStringTemplate<C>&);
    virtual void operator=(const C);
    virtual void operator=(const C * const);

    /* comparison operators */
    inline bool operator<(const CStringTemplate<C>& s) const { return compare(s.m_Data, s.m_Length) < 0; }
    inline bool operator>(const CStringTemplate<C>& s) const { return compare(s.m_Data, s.m_Length) > 0; }
    inline bool operator<=(const CStringTemplate<C>& s) const { return compare(s.m_Data, s.m_Length) <= 0; }
    inline bool operator>=(const CStringTemplate<C>& s) const { return compare(s.m_Data, s.m_Length) >= 0; }
    inline bool operator==(const CStringTemplate<C>& s) const { return equals(s.m_Data, s.m_Length); }
    inline bool operator!=(const CStringTemplate<C>& s) const { return notEquals(s.m_Data, s.m_Length); }
    inline bool operator<(const C * s) const { return compare(s, base_strlen(s)) < 0; }
    inline bool operator>(const C * s) const { return compare(s, base_strlen(s)) > 0; }
    inline bool operator<=(const C * s) const { return compare(s, base_strlen(s)) <= 0; }
    inline bool operator>=(const C * s) const { return compare(s, base_strlen(s)) >= 0; }
    inline bool operator==(const C * s) const { return equals(s, base_strlen(s)); }
    inline bool operator!=(const C * s) const { return notEquals(s, base_strlen(s)); }

    /* comparison methods */
    inline int compare(const CStringTemplate<C>& s, int start = 0, bool respectLength = true) const { return compare(s.m_Data, s.m_Length, start, respectLength); }
    int compare(const C * buf, int len, int start = 0, bool respectLength = true) const;
    inline int compareIgnoreCase(const CStringTemplate<C>& s, int start = 0, bool respectLength = true) const { return compareIgnoreCase(s.m_Data, s.m_Length, start, respectLength); }
    int compareIgnoreCase(const C * buf, int len, int start = 0, bool respectLength = true) const;
    inline bool equals(const CStringTemplate<C>& s) const { return equals(s.m_Data, s.m_Length); }
    bool equals(const C * buf, int len) const;
    inline bool equals(const C * buf) const { return equals(buf, base_strlen(buf)); }
    inline bool notEquals(const CStringTemplate<C>& s) const { return notEquals(s.m_Data, s.m_Length); }
    bool notEquals(const C * buf, int len) const;
    inline bool notEquals(const C * buf) const { return notEquals(buf, base_strlen(buf)); }
    inline bool equalsIgnoreCase(const CStringTemplate<C>& s) const { return equalsIgnoreCase(s.m_Data, s.m_Length); }
    bool equalsIgnoreCase(const C * buf, int len) const;
    inline bool equalsIgnoreCase(const C * buf) const { return equalsIgnoreCase(buf, base_strlen(buf)); }
    inline bool equalsIgnoreCase(const CStringTemplate<C>& s, bool caseSensitive) const { return caseSensitive ? equals(s) : equalsIgnoreCase(s); }
    inline bool startsWith(const CStringTemplate<C>& s) const { return startsWith(s.m_Data, s.m_Length); }
    bool startsWith(const C * buf, int len) const;
    inline bool startsWith(const C * buf) const { return startsWith(buf, base_strlen(buf)); }
    inline bool startsWith(const CStringTemplate<C>& s, bool caseSensitive) const { return caseSensitive ? startsWith(s) : startsWithIgnoreCase(s); }
    inline bool startsWithIgnoreCase(const CStringTemplate<C>& s) const { return startsWithIgnoreCase(s.m_Data, s.m_Length); }
    bool startsWithIgnoreCase(const C * buf, int len) const;
    inline bool startsWithIgnoreCase(const C * buf) const { return startsWithIgnoreCase(buf, base_strlen(buf)); }
    inline bool endsWith(const CStringTemplate<C>& s) const { return endsWith(s.m_Data, s.m_Length); }
    bool endsWith(const C * buf, int len) const;
    inline bool endsWith(const C * buf) const { return endsWith(buf, base_strlen(buf)); }
    inline bool endsWith(const CStringTemplate<C>& s, bool caseSensitive) const { return caseSensitive ? endsWith(s) : endsWithIgnoreCase(s); }
    inline bool endsWithIgnoreCase(const CStringTemplate<C>& s) const { return endsWithIgnoreCase(s.m_Data, s.m_Length); }
    bool endsWithIgnoreCase(const C * buf, int len) const;
    inline bool endsWithIgnoreCase(const C * buf) const { return endsWithIgnoreCase(buf, base_strlen(buf)); }

    /* streaming */
    inline ostream& operator<<(ostream& stream) const { stream << m_Data; return stream; }
    istream& operator>>(istream& stream);

    /* access */
    inline const C * const c_str(void) const { return (const C * const)m_Data; }
    inline const C& at(const unsigned int index) const { _S_DEBUG(assert(index < m_Length)); return m_Data[index]; }
    inline C& at(const unsigned int index) { _S_DEBUG(assert(index < m_Length)); return m_Data[index]; }
    inline C& operator[](const unsigned int index) const { _S_DEBUG(assert(index < m_Length)); return m_Data[index]; }
    inline void setAt(const unsigned int index, const C c) { _S_DEBUG(assert(index < m_Length)); m_Data[index] = c; }

    /* concatenation */
    void append(const CStringTemplate<C>&);
    void append(const C);
    void append(const C * const, int);
    void append(const C * const);

    /* static char case ops */
    static inline C toUpperChar(const C ch) { if ((ch <= 'z') && (ch >= 'a')) return (C)(ch - ('a' - 'A')); else return ch; }
    static inline C toLowerChar(const C ch) { if ((ch <= 'Z') && (ch >= 'A')) return (C)(ch + ('a' - 'A')); else return ch; }

    /* move */
    void moveFrom(CStringTemplate<C>&);

    /* clear & erase */
    void clear(void);
    void erase(int start, int count);

    /* insert */
    void insert(const unsigned int pos, const CStringTemplate<C>&);
    void insert(const unsigned int pos, const C);
    void insert(const unsigned int pos, const C * const buffer, int bufferLen = -1);

    /* replace */
    bool replace(const C source, const C target);
    bool replace(const CStringTemplate<C>&, const CStringTemplate<C>&, bool caseSensitive = true);
    bool replace(const C chLeft, const C chRight, const C chTarget);

    /* count */
    int count(const C ch) const;
    int count(const C chLeft, const C chRight) const;

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
    int indexOf(const CStringTemplate<C>& str, const int start = 0) const;
    int indexOfIgnoreCase(const CStringTemplate<C>& str, const int start = 0) const;
    int indexOf(const C * const buffer, const int bufLen, const int start = 0) const;
    int indexOfIgnoreCase(const C * const buffer, const int bufLen, const int start = 0) const;
    inline int indexOf(const C * const buffer, const int start = 0) const { return indexOf(buffer, base_strlen(buffer), start); }
    inline int indexOfIgnoreCase(const C * const buffer, const int start = 0) const { return indexOfIgnoreCase(buffer, base_strlen(buffer), start); }

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
    void removeDuplicate(const C chLeft, const C chRight);
    void remove(const C chLeft, const C chRight);

    /* concatenation operators */
    inline void operator+=(const CStringTemplate<C>& s) { append(s); }
    inline void operator+=(const C c) { append(c); }
    inline void operator+=(const C * const buffer) { append(buffer); }
    inline void quote(void) { trim('\''); trim('\"'); operator=('\"' + (*this) + '\"'); }
    inline void dequote(void) { trim('\''); trim('\"'); }

    /* substrings */
    inline int mid(int first, CStringTemplate<C> * result) const { return mid(first, m_Length, result); }
    int mid(int first, int count, CStringTemplate<C> * result) const;
    inline int left(int count, CStringTemplate<C> * result) const { return mid(0, count, result); }
    inline int right(int count, CStringTemplate<C> * result) const { return mid(m_Length - count, count, result); }
    int extractLine(CStringTemplate<C> * result);
    int getLine(CStringTemplate * result, int& pos) const;

    /* type conversions */
    static CStringTemplate fromLong(long value, int leftPad = 0, const int base = 10);
    static CStringTemplate fromInt(int value, int leftPad = 0, const int base = 10);
    static CStringTemplate fromFloat(float value, int leftPad = 0, int fracPad = 0, int base = 10);
    static CStringTemplate fromDouble(double value, int leftPad = 0, int fracPad = 0, int base = 10);
    inline static int toHex(const CStringTemplate<C>& s) { int r; sscanf((const C *)s.c_str(), "%x", &r); return r; }
    inline static int toInt(const CStringTemplate<C>& s) { return s.m_Length ? atoi((const C *)s.c_str()) : 0; }
    static float toFloat(const CStringTemplate<C>& s) { return s.m_Length ? (float)atof((const C *)s.c_str()) : 0; }
    static double toDouble(const CStringTemplate<C>& s) { return s.m_Length ? (double)atof((const C *)s.c_str()) : 0; }
    static long toLong(const CStringTemplate<C>& s) { return s.m_Length ? atol((const C *)s.c_str()) : 0; }

    /* scanners */
    bool readDigit(int& pos, int * digit) const;
    bool readChar(int& pos, C * c) const;
    bool readString(int& pos, CStringTemplate * str) const;
};

#define CSTRING_INTERVAL(_C, _L, _R) ((_C >= _L) && (_C <= _R))

template <class C> inline ostream& operator<<(ostream& stream, const CStringTemplate<C>& s) { return s.operator<<(stream); }
template <class C> inline istream& operator>>(istream& stream, CStringTemplate<C>& s) { return s.operator>>(stream); }

template <class C> inline bool operator==(const CStringTemplate<C>& L, const CStringTemplate<C>& R) { return L.operator==(R); }
template <class C> inline bool operator==(const CStringTemplate<C>& L, const C * const R) { return L.operator==(R); }
template <class C> inline bool operator==(const C * const L, const CStringTemplate<C>& R) { return R.operator==(L); }
template <class C> inline bool operator!=(const CStringTemplate<C>& L, const C * const R) { return L.operator!=(R); }
template <class C> inline bool operator!=(const C * const L, const CStringTemplate<C>& R) { return R.operator!=(L); }
template <class C> inline bool operator<=(const CStringTemplate<C>& L, const C * const R) { return L.operator<=(R); }
template <class C> inline bool operator<=(const C * const L, const CStringTemplate<C>& R) { return !(R.operator>(L)); }
template <class C> inline bool operator>=(const CStringTemplate<C>& L, const C * const R) { return L.operator>=(R); }
template <class C> inline bool operator>=(const C * const L, const CStringTemplate<C>& R) { return !(R.operator<(L)); }
template <class C> inline bool operator<(const CStringTemplate<C>& L, const C * const R) { return L.operator<(R); }
template <class C> inline bool operator<(const C * const L, const CStringTemplate<C>& R) { return !(R.operator>=(L)); }
template <class C> inline bool operator>(const CStringTemplate<C>& L, const C * const R) { return L.operator>(R); }
template <class C> inline bool operator>(const C * const L, const CStringTemplate<C>& R) { return !(R.operator<=(L)); }

template <class C> inline CStringTemplate<C> operator+(const CStringTemplate<C>& L, const CStringTemplate<C>& R) { CStringTemplate<C> r(L); r += R; return r; }
template <class C> inline CStringTemplate<C> operator+(const CStringTemplate<C>& L, const C R) { CStringTemplate<C> r(L); r += R; return r; }
template <class C> inline CStringTemplate<C> operator+(const C L, const CStringTemplate<C>& R) { CStringTemplate<C> r(L); r += R; return r; }
template <class C> inline CStringTemplate<C> operator+(const CStringTemplate<C>& L, const C * const R) { CStringTemplate<C> r(L); r += R; return r; }
template <class C> inline CStringTemplate<C> operator+(const C * const L, const CStringTemplate<C>& R) { CStringTemplate<C> r(L); r += R; return r; }

typedef CStringTemplate<CSTRING_CHARTYPE> CString;

#endif
