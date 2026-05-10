/*
    baseclasses2
    Originally: Vestris Inc., Geneva, Switzerland, 1994-1999
    https://github.com/dblock/baseclasses2
*/

/* Template implementation file. Include this in a .cpp, then add explicit
   instantiations for the (char-type, StackSize) combinations you need:
     template class CStringTemplate<char>;          // StackSize defaults to 18
     template class CStringTemplate<char, 64>;
*/

#include "string.hpp"

template<class C> struct CStringCharTraits {};

template<> struct CStringCharTraits<char> {
    static bool isDigit(char c)  { return isdigit((unsigned char)c) != 0; }
    static bool isXDigit(char c) { return isxdigit((unsigned char)c) != 0; }
    static long   toLong(const char* s)   { return atol(s); }
    static double toDouble(const char* s) { return atof(s); }
    static int    toHex(const char* s)    { int r = 0; sscanf(s, "%x", &r); return r; }
};

template<> struct CStringCharTraits<wchar_t> {
    static bool isDigit(wchar_t c)  { return iswdigit(c) != 0; }
    static bool isXDigit(wchar_t c) { return iswxdigit(c) != 0; }
    static long   toLong(const wchar_t* s)   { return wcstol(s, nullptr, 10); }
    static double toDouble(const wchar_t* s) { return wcstod(s, nullptr); }
    static int    toHex(const wchar_t* s)    { return (int)wcstol(s, nullptr, 16); }
};

template <class C, int StackSize>
const CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::EmptyCString;

/* constructors / destructor */

template <class C, int StackSize>
CStringTemplate<C, StackSize>::CStringTemplate(void) {
    initialize();
}

template <class C, int StackSize>
CStringTemplate<C, StackSize>::~CStringTemplate(void) {
    if (m_RealAllocData) {
        delete[] m_RealAllocData;
    }
}

template <class C, int StackSize>
CStringTemplate<C, StackSize>::CStringTemplate(const C * const buffer) {
    initialize();
    if (buffer)
        copyBuffer(buffer, (int)std::char_traits<C>::length(buffer));
}

template <class C, int StackSize>
CStringTemplate<C, StackSize>::CStringTemplate(const C * const buffer, int len) {
    initialize();
    if (buffer)
        copyBuffer(buffer, len);
}

template <class C, int StackSize>
CStringTemplate<C, StackSize>::CStringTemplate(const CStringTemplate<C, StackSize>& refStr) {
    initialize();
    operator=(refStr);
}

template <class C, int StackSize>
CStringTemplate<C, StackSize>::CStringTemplate(const C c) {
    initialize();
    m_Data[0] = c;
    m_Data[1] = 0;
    m_Length = 1;
}

/* streaming */

template <class C, int StackSize>
std::basic_istream<C>& CStringTemplate<C, StackSize>::operator>>(std::basic_istream<C>& stream) {
    C buffer[32], c;
    while (1) {
        c = (C)'\n';
        while ((c == (C)'\n') || (c == (C)' ')) {
            c = (C)stream.get();
            if ((c != (C)'\n') && (c != (C)' ')) {
                stream.putback(c);
                break;
            }
        }
        stream.getline(buffer, 31);
    }
    (*this) = buffer;
    return stream;
}

/* substrings */

template <class C, int StackSize>
CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::mid(int first, int count) const {
    CStringTemplate<C, StackSize> result;
    if (first < 0) {
        count += first;
        first = 0;
    }
    if (first >= (int)m_Length)
        return result;
    if (count + first >= (int)m_Length)
        count = m_Length - first;
    if (count <= 0)
        return result;
    result.setLength(count);
    for (int i = 0; i < count; i++)
        result[i] = operator[](i + first);
    return result;
}

/* type conversions */

template <class C, int StackSize>
CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::fromLong(long value, int leftPad, const int base) {
    CStringTemplate<C, StackSize> Result;
    Result.setSize(5);
    bool negativeSign = false;
    if (value < 0) {
        negativeSign = true;
        value = -value;
    }
    long digit;
    do {
        digit = value / base;
        Result.insert(0, (C)('0' + value - (digit * base)));
        value = digit;
    } while (value);
    if (leftPad) {
        leftPad -= ((int)negativeSign + Result.m_Length);
        while (leftPad--) Result.insert(0, '0');
    }
    if (negativeSign)
        Result.insert(0, '-');
    return Result;
}

template <class C, int StackSize>
CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::fromInt(int value, int leftPad, int base) {
    return fromLong(value, leftPad, base);
}

template <class C, int StackSize>
CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::fromDouble(double value, int leftPad, int fracPad, int base) {
    long truncated = (long)value;
    double fraction = value - truncated;
    if (fraction < 0) fraction = -fraction;

    CStringTemplate<C, StackSize> fractionString;
    fractionString.setSize(5);
    while (fraction) {
        fraction *= (double)base;
        fractionString += (C)('0' + (int)(long)fraction);
        fraction -= ((long)fraction);
    }

    if (fractionString.m_Length > 5)
        fractionString.erase(5, fractionString.m_Length);

    fractionString.trimRight('0', '0');

    int appendZeros = fracPad - (int)fractionString.m_Length;
    while (appendZeros-- > 0) fractionString += '0';

    if ((fracPad && ((int)fractionString.m_Length > fracPad)))
        fractionString.erase(fracPad, fractionString.m_Length);

    CStringTemplate<C, StackSize> Result = fromLong(truncated, leftPad, base);
    if (fractionString.m_Length) {
        Result += '.';
        Result += fractionString;
    }
    return Result;
}

template <class C, int StackSize>
CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::fromFloat(float value, int leftPad, int fracPad, int base) {
    return fromDouble(value, leftPad, fracPad, base);
}

/* line reading */

template <class C, int StackSize>
CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::getLine(int& pos) const {
    CStringTemplate<C, StackSize> result;
    if (pos >= (int)m_Length) return result;
    int start = pos;
    while (pos < (int)m_Length && m_Data[pos] != '\n') pos++;
    int len = pos - start;
    if (pos < (int)m_Length) pos++;
    if (len > 0) {
        result.setLength(len);
        for (int i = 0; i < len; i++)
            result[i] = m_Data[start + i];
        if (result.m_Length && result[result.m_Length - 1] == '\r')
            result.erase(result.m_Length - 1, 1);
    }
    return result;
}

template <class C, int StackSize>
CStringTemplate<C, StackSize> CStringTemplate<C, StackSize>::extractLine() {
    int pos = 0;
    CStringTemplate<C, StackSize> result = getLine(pos);
    if (pos > 0) erase(0, pos);
    return result;
}

/* scanners */

template <class C, int StackSize>
bool CStringTemplate<C, StackSize>::readDigit(int& pos, int * digit) const {
    if (pos >= (int)m_Length) return false;
    if (!CStringCharTraits<C>::isDigit(m_Data[pos])) return false;
    if (digit) *digit = m_Data[pos] - (C)'0';
    pos++;
    return true;
}

template <class C, int StackSize>
bool CStringTemplate<C, StackSize>::readChar(int& pos, C * c) const {
    if (pos >= (int)m_Length) return false;
    if (c) *c = m_Data[pos];
    pos++;
    return true;
}

template <class C, int StackSize>
bool CStringTemplate<C, StackSize>::readString(int& pos, CStringTemplate<C, StackSize> * pString) const {
    pString->clear();
    while (pos < (int)m_Length && m_Data[pos] != ' ' && m_Data[pos] != '\t') {
        pString->append(m_Data[pos]);
        pos++;
    }
    return pString->m_Length > 0;
}

/* replace */

template <class C, int StackSize>
bool CStringTemplate<C, StackSize>::replace(const CStringTemplate<C, StackSize>& source, const CStringTemplate<C, StackSize>& target, bool caseSensitive) {
    bool result = false;
    int curPos = 0;
    while ((curPos = caseSensitive ? indexOf(source, curPos) : indexOfIgnoreCase(source, curPos)) != -1) {
        erase(curPos, source.m_Length);
        insert(curPos, target);
        curPos += target.m_Length;
        result = true;
    }
    return result;
}

/* numeric checks */

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::isInt(int start, int length, int * pValue) const {
    long lResult = 0;
    if (isLong(start, length, &lResult)) {
        if (pValue) *pValue = (int)lResult;
        return true;
    }
    return false;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::isLong(int pos, int length, long * pValue) const {
    int sign = 1;
    long newValue = 0;
    if (pos + length > (int)m_Length) length = (int)m_Length - pos;
    if (pos >= (int)m_Length) return false;
    if (m_Data[pos] == '-') { pos++; length--; sign = -1; }
    else if (m_Data[pos] == '+') { pos++; length--; }
    if (pos >= (int)m_Length) return false;
    while (length--) {
        if (!CStringCharTraits<C>::isDigit(m_Data[pos])) return false;
        newValue = newValue * 10 + (int)(m_Data[pos] - '0');
        pos++;
    }
    newValue *= sign;
    if (pValue) *pValue = newValue;
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::terminateWith(const C ch) {
    if (!m_Length || m_Data[m_Length - 1] != ch) {
        append(ch);
        return true;
    }
    return false;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::getInt(const int start, const int length) const {
    int Result = 0;
    isInt(start, length, &Result);
    return Result;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::toUpper(void) {
    for (int i = 0; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'z') && (m_Data[i] >= 'a'))
            m_Data[i] -= ('a' - 'A');
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::toLower(void) {
    for (int i = 0; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'Z') && (m_Data[i] >= 'A'))
            m_Data[i] += ('a' - 'A');
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::hasUpper(int start) const {
    for (int i = start; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'Z') && (m_Data[i] >= 'A')) return true;
    return false;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::hasLower(int start) const {
    for (int i = start; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'z') && (m_Data[i] >= 'a')) return true;
    return false;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::reverse(void) {
    C ch;
    for (int i = 0; i < ((int)m_Length) / 2; i++) {
        ch = m_Data[i];
        m_Data[i] = m_Data[m_Length - 1 - i];
        m_Data[m_Length - 1 - i] = ch;
    }
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::lastIndexOf(const C ch) const {
    return lastIndexOf(ch, ((int)m_Length) - 1);
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::lastIndexOf(const C ch, const int start) const {
    for (int i = start; i >= 0; i--)
        if (m_Data[i] == ch) return i;
    return -1;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::indexOf(const C ch, const int start) const {
    for (int i = start; i < (int)m_Length; i++)
        if (m_Data[i] == ch) return i;
    return -1;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::indexOf(const CStringTemplate<C, StackSize>& str, const int start) const {
    for (int i = start; i < (int)m_Length - (int)str.m_Length + 1; i++)
        if (!(memcmp(m_Data + i, str.m_Data, str.m_Length * sizeof(C)))) return i;
    return -1;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::indexOfIgnoreCase(const CStringTemplate<C, StackSize>& str, const int start) const {
    for (int i = start; i < ((int)m_Length) - ((int)str.m_Length) + 1; i++)
        if (compareIgnoreCase(str, i, false) == 0) return i;
    return -1;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::replace(const C source, const C target) {
    bool result = false;
    for (int i = 0; i < (int)m_Length; i++) {
        if (m_Data[i] == source) {
            m_Data[i] = target;
            result = true;
        }
    }
    return result;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::count(const C ch) const {
    int Result = 0;
    for (int i = 0; i < (int)m_Length; i++)
        if (m_Data[i] == ch) Result++;
    return Result;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::isInt(int * value) const {
    return isInt(0, m_Length, value);
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::isHex(int * value) const {
    if (!m_Length) return false;
    for (int i = 0; i < (int)m_Length; i++)
        if (!CStringCharTraits<C>::isXDigit(m_Data[i])) return false;
    if (value) *value = CStringCharTraits<C>::toHex(m_Data);
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::isFloat(float * value) const {
    bool separator = false;
    int i = 0, sign = 1, displ = 0;
    if (m_Length && (m_Data[0] == (C)'-')) { i++; displ++; sign = -1; }
    if (i == (int)m_Length) return false;
    for (; i < (int)m_Length; i++) {
        if (!CStringCharTraits<C>::isDigit(m_Data[i])) {
            if (separator) return false;
            else if (m_Data[i] == (C)'.') separator = true;
            else return false;
        }
    }
    if (value) *value = (float)(CStringCharTraits<C>::toDouble(m_Data + displ) * sign);
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::isLong(long * value) const {
    return isLong(0, m_Length, value);
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::indexOf(const C * const buffer, const int len, const int start) const {
    int length = (int)m_Length - len + 1;
    for (int i = start; i < length; i++)
        if (compare(buffer, len, i, false) == 0) return i;
    return -1;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::indexOfIgnoreCase(const C * const buffer, const int len, const int start) const {
    int length = (int)m_Length - len + 1;
    for (int i = start; i < length; i++)
        if (compareIgnoreCase(buffer, len, i, false) == 0) return i;
    return -1;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::append(const C * const buffer) {
    if (buffer) append(buffer, (int)std::char_traits<C>::length(buffer));
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::setSize(unsigned int desiredSize, bool preserve) {
    if (desiredSize <= m_Size) return;
    unsigned int size = desiredSize;
    if (size < (unsigned int)1048576) {
        size = (m_Size << 1) + 1;
        while (size < desiredSize) size <<= 1;
    } else {
        size = ((size + 1024 - 1) / 1024) * 1024;
    }
    C * m_NewData = new C[size];
    if (preserve && m_Length) {
        memcpy(m_NewData, m_Data, m_Length * sizeof(C));
        m_NewData[m_Length] = 0;
    }
    if (m_RealAllocData) delete[] m_RealAllocData;
    m_RealAllocData = m_NewData;
    m_Data = m_NewData;
    m_Size = size;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::append(const CStringTemplate<C, StackSize>& str) {
    setSize(m_Length + str.m_Length + 1, true);
    memcpy(m_Data + m_Length, str.m_Data, str.m_Length * sizeof(C));
    m_Length += str.m_Length;
    m_Data[m_Length] = 0;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::append(const C c) {
    setSize(m_Length + 2, true);
    m_Data[m_Length] = c;
    m_Length++;
    m_Data[m_Length] = 0;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::append(const C * const buffer, int rightLength) {
    if (rightLength) {
        setSize(m_Length + (unsigned int)rightLength + 1, true);
        memcpy(m_Data + m_Length, buffer, (unsigned int)rightLength * sizeof(C));
        m_Length += (unsigned int)rightLength;
        m_Data[m_Length] = 0;
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::operator=(const C c) {
    setSize(2, false);
    m_Data[0] = c;
    m_Data[1] = 0;
    m_Length = 1;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::operator=(const C * const buffer) {
    copyBuffer(buffer);
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::operator=(const CStringTemplate<C, StackSize>& refStr) {
    copyBuffer(refStr.m_Data, refStr.m_Length);
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::moveFrom(CStringTemplate<C, StackSize>& refStr) {
    if (!refStr.m_RealAllocData) {
        operator=(refStr);
        refStr.clear();
    } else {
        if (m_RealAllocData) delete[] m_RealAllocData;
        m_RealAllocData = refStr.m_RealAllocData;
        m_Data = m_RealAllocData;
        m_Size = refStr.m_Size;
        m_Length = refStr.m_Length;
        refStr.m_RealAllocData = NULL;
        refStr.m_Size = StackSize;
        refStr.m_Data = refStr.m_StackData;
        refStr.m_Data[0] = 0;
        refStr.m_Length = 0;
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::setLength(void) {
    m_Length = 0;
    for (int i = 0; i < (int)m_Size; i++) {
        if (m_Data[i] == 0) { m_Length = i; break; }
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::setLength(unsigned int length, C fillChar, bool fill) {
    setSize(length + 1, true);
    if (length != m_Length) {
        if ((length > m_Length) && fill)
            for (unsigned int i = m_Length; i < length; i++) m_Data[i] = fillChar;
        m_Data[length] = 0;
        m_Length = length;
    }
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::equalsIgnoreCase(const C * str, int len) const {
    if ((int)m_Length != len) return false;
    for (int i = 0; i < len; i++)
        if (toLowerChar(m_Data[i]) != toLowerChar(str[i])) return false;
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::equals(const C * str, int len) const {
    if ((int)m_Length != len) return false;
    for (int i = 0; i < len; i++)
        if (m_Data[i] != str[i]) return false;
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::notEquals(const C * str, int len) const {
    if ((int)m_Length != len) return true;
    for (int i = 0; i < len; i++)
        if (m_Data[i] != str[i]) return true;
    return false;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::compare(const C * str, int len, int start, bool respectLength) const {
    int selfLength = (int)m_Length - start;
    int minLen = (selfLength < len) ? selfLength : len;
    char c1, c2;
    for (int i = 0; i < minLen; i++) {
        c1 = m_Data[i + start];
        c2 = str[i];
        if (c1 != c2) return c1 - c2;
    }
    if (!respectLength) return 0;
    if (selfLength == len) return 0;
    return (selfLength > len) ? 1 : -1;
}

template <class C, int StackSize>
inline int CStringTemplate<C, StackSize>::compareIgnoreCase(const C * str, int len, int start, bool respectLength) const {
    int selfLength = (int)m_Length - start;
    int minLen = (selfLength < len) ? selfLength : len;
    char c1, c2;
    for (int i = 0; i < minLen; i++) {
        c1 = toLowerChar(m_Data[i + start]);
        c2 = toLowerChar(str[i]);
        if (c1 != c2) return c1 - c2;
    }
    if (!respectLength) return 0;
    if (selfLength == len) return 0;
    return (selfLength > len) ? 1 : -1;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::startsWithIgnoreCase(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (toLowerChar(m_Data[i]) != toLowerChar(str[i])) return false;
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::startsWith(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (m_Data[i] != str[i]) return false;
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::endsWithIgnoreCase(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (toLowerChar(m_Data[i + (m_Length - len)]) != toLowerChar(str[i])) return false;
    return true;
}

template <class C, int StackSize>
inline bool CStringTemplate<C, StackSize>::endsWith(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (m_Data[i + (m_Length - len)] != str[i]) return false;
    return true;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::insert(const unsigned int pos, const CStringTemplate<C, StackSize>& str) {
    if (pos >= m_Length) append(str);
    else if (&str == this) {
        CStringTemplate<C, StackSize> Tmp(str);
        insert(pos, Tmp);
    } else if (str.m_Length) {
        setSize(m_Length + str.m_Length + 1, true);
        for (int i = (int)m_Length; i >= (int)pos; i--)
            m_Data[i + str.m_Length] = m_Data[i];
        memcpy(m_Data + pos, str.m_Data, str.m_Length * sizeof(C));
        m_Length += str.m_Length;
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::insert(const unsigned int pos, const C c) {
    if (pos >= m_Length) append(c);
    else {
        setSize(m_Length + 2, true);
        for (int i = (int)m_Length; i >= (int)pos; i--)
            m_Data[i + 1] = m_Data[i];
        m_Data[pos] = c;
        m_Length++;
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::insert(const unsigned int pos, const C * const buffer, int bufferLen) {
    if (pos >= m_Length) append(buffer, bufferLen);
    else if (buffer) {
        if (bufferLen < 0) bufferLen = (int)std::char_traits<C>::length(buffer);
        if (bufferLen) {
            setSize(m_Length + (unsigned int)bufferLen + 1, true);
            for (int i = (int)m_Length; i >= (int)pos; i--)
                m_Data[i + (unsigned int)bufferLen] = m_Data[i];
            memcpy(m_Data + pos, buffer, bufferLen * sizeof(C));
            m_Length += (unsigned int)bufferLen;
        }
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::erase(int start, int count) {
    if (start < 0) { count += start; start = 0; }
    if (start >= (int)m_Length) return;
    if (count + start >= (int)m_Length) count = m_Length - start;
    if (count <= 0) return;
    for (int i = start; i < ((int)m_Length - count); i++)
        m_Data[i] = m_Data[i + count];
    m_Length -= count;
    m_Data[m_Length] = 0;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::trimRight(const C LChar, const C RChar) {
    if (m_Length) {
        C * m_DataRight = m_Data + (int)m_Length - 1;
        while ((m_DataRight >= m_Data) && (m_DataRight[0] >= LChar) && (m_DataRight[0] <= RChar))
            m_DataRight--;
        if (m_DataRight != (m_Data + (int)m_Length - 1))
            erase(m_DataRight - m_Data + 1, (int)m_Length - (m_DataRight - m_Data) + 1);
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::trimLeft(const C LChar, const C RChar) {
    if (m_Length) {
        C * m_DataLeft = m_Data;
        while (((m_DataLeft[0] >= LChar) && (m_DataLeft[0] <= RChar)) && (m_DataLeft < (m_Data + (int)m_Length)))
            m_DataLeft++;
        if (m_DataLeft != m_Data) erase(0, m_DataLeft - m_Data);
    }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::clear(void) {
    if (m_Length) { m_Data[0] = 0; m_Length = 0; }
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::copyBuffer(const C * const buffer) {
    if (buffer) copyBuffer(buffer, (int)std::char_traits<C>::length(buffer));
    else clear();
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::copyBuffer(const C * const buffer, int length) {
    setSize(length + 1, false);
    memcpy(m_Data, buffer, length * sizeof(C));
    m_Data[length] = 0;
    m_Length = length;
}

template <class C, int StackSize>
inline void CStringTemplate<C, StackSize>::initialize(void) {
    m_Data = m_StackData;
    m_RealAllocData = NULL;
    m_Length = 0;
    m_Size = StackSize;
    m_Data[0] = 0;
}

/* numeric conversions using CStringCharTraits */

template <class C, int StackSize>
int CStringTemplate<C, StackSize>::toHex(const CStringTemplate<C, StackSize>& s) {
    return s.m_Length ? CStringCharTraits<C>::toHex(s.c_str()) : 0;
}

template <class C, int StackSize>
int CStringTemplate<C, StackSize>::toInt(const CStringTemplate<C, StackSize>& s) {
    return s.m_Length ? (int)CStringCharTraits<C>::toLong(s.c_str()) : 0;
}

template <class C, int StackSize>
float CStringTemplate<C, StackSize>::toFloat(const CStringTemplate<C, StackSize>& s) {
    return s.m_Length ? (float)CStringCharTraits<C>::toDouble(s.c_str()) : 0;
}

template <class C, int StackSize>
double CStringTemplate<C, StackSize>::toDouble(const CStringTemplate<C, StackSize>& s) {
    return s.m_Length ? CStringCharTraits<C>::toDouble(s.c_str()) : 0;
}

template <class C, int StackSize>
long CStringTemplate<C, StackSize>::toLong(const CStringTemplate<C, StackSize>& s) {
    return s.m_Length ? CStringCharTraits<C>::toLong(s.c_str()) : 0;
}
