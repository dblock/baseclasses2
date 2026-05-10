/*
    baseclasses2
    Originally: Vestris Inc., Geneva, Switzerland, 1994-1999
    https://github.com/dblock/baseclasses2
*/

#include "string.hpp"

template <class C>
const CStringTemplate<C> CStringTemplate<C>::EmptyCString;

/* constructors / destructor */

template <class C>
CStringTemplate<C>::CStringTemplate(void) {
    initialize();
}

template <class C>
CStringTemplate<C>::~CStringTemplate(void) {
    if (m_RealAllocData) {
        delete[] m_RealAllocData;
    }
}

template <class C>
CStringTemplate<C>::CStringTemplate(const C * const buffer) {
    initialize();
    if (buffer)
        copyBuffer(buffer, base_strlen(buffer));
}

template <class C>
CStringTemplate<C>::CStringTemplate(const C * const buffer, int len) {
    initialize();
    if (buffer)
        copyBuffer(buffer, len);
}

template <class C>
CStringTemplate<C>::CStringTemplate(const CStringTemplate<C>& refStr) {
    initialize();
    operator=(refStr);
}

template <class C>
CStringTemplate<C>::CStringTemplate(const C c) {
    initialize();
    m_Data[0] = c;
    m_Data[1] = 0;
    m_Length = 1;
}

/* streaming */

template <class C>
istream& CStringTemplate<C>::operator>>(istream& stream) {
    C buffer[32], c;
    while (1) {
        c = '\n';
        while ((c == '\n') || (c == ' ')) {
            c = (C)stream.get();
            if ((c != '\n') && (c != ' ')) {
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

template <class C>
int CStringTemplate<C>::mid(int first, int count, CStringTemplate<C> * result) const {
    result->clear();
    if (first < 0) {
        count += first;
        first = 0;
    }
    if (first >= (int)m_Length)
        return 0;
    if (count + first >= (int)m_Length)
        count = m_Length - first;
    if (count <= 0)
        return 0;
    result->setLength(count);
    for (int i = 0; i < count; i++)
        (*result)[i] = operator[](i + first);
    return result->m_Length;
}

/* type conversions */

template <class C>
CStringTemplate<C> CStringTemplate<C>::fromLong(long value, int leftPad, const int base) {
    CStringTemplate<C> Result;
    Result.setSize(5);
    bool negativeSign = false;
    if (value < 0) {
        negativeSign = true;
        value = -value;
    }
    long digit;
    do {
        digit = value / base;
        Result.insert(0, (char)('0' + value - (digit * base)));
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

template <class C>
CStringTemplate<C> CStringTemplate<C>::fromInt(int value, int leftPad, int base) {
    return fromLong(value, leftPad, base);
}

template <class C>
CStringTemplate<C> CStringTemplate<C>::fromDouble(double value, int leftPad, int fracPad, int base) {
    long truncated = (long)value;
    double fraction = value - truncated;
    if (fraction < 0) fraction = -fraction;

    CStringTemplate<C> fractionString;
    fractionString.setSize(5);
    while (fraction) {
        fraction *= (double)base;
        fractionString += ('0' + (char)(long)fraction);
        fraction -= ((long)fraction);
    }

    if (fractionString.m_Length > 5)
        fractionString.erase(5, fractionString.m_Length);

    fractionString.trimRight('0', '0');

    int appendZeros = fracPad - (int)fractionString.m_Length;
    while (appendZeros-- > 0) fractionString += '0';

    if ((fracPad && ((int)fractionString.m_Length > fracPad)))
        fractionString.erase(fracPad, fractionString.m_Length);

    CStringTemplate<C> Result = fromLong(truncated, leftPad, base);
    if (fractionString.m_Length) {
        Result += '.';
        Result += fractionString;
    }
    return Result;
}

template <class C>
CStringTemplate<C> CStringTemplate<C>::fromFloat(float value, int leftPad, int fracPad, int base) {
    return fromDouble(value, leftPad, fracPad, base);
}

/* line reading */

template <class C>
int CStringTemplate<C>::getLine(CStringTemplate<C> * result, int& pos) const {
    result->clear();
    if (pos >= (int)m_Length) return 0;
    int start = pos;
    while (pos < (int)m_Length && m_Data[pos] != '\n') pos++;
    int len = pos - start;
    if (pos < (int)m_Length) pos++;
    if (len > 0) {
        result->setLength(len);
        for (int i = 0; i < len; i++)
            (*result)[i] = m_Data[start + i];
        if (result->m_Length && (*result)[result->m_Length - 1] == '\r')
            result->erase(result->m_Length - 1, 1);
    }
    return result->m_Length;
}

template <class C>
int CStringTemplate<C>::extractLine(CStringTemplate<C> * result) {
    int pos = 0;
    int Result = getLine(result, pos);
    if (pos > 0) erase(0, pos);
    return Result;
}

/* scanners */

template <class C>
bool CStringTemplate<C>::readDigit(int& pos, int * digit) const {
    if (pos >= (int)m_Length) return false;
    if (!isdigit(m_Data[pos])) return false;
    if (digit) *digit = m_Data[pos] - '0';
    pos++;
    return true;
}

template <class C>
bool CStringTemplate<C>::readChar(int& pos, C * c) const {
    if (pos >= (int)m_Length) return false;
    if (c) *c = m_Data[pos];
    pos++;
    return true;
}

template <class C>
bool CStringTemplate<C>::readString(int& pos, CStringTemplate<C> * pString) const {
    pString->clear();
    while (pos < (int)m_Length && m_Data[pos] != ' ' && m_Data[pos] != '\t') {
        pString->append(m_Data[pos]);
        pos++;
    }
    return pString->m_Length > 0;
}

/* replace */

template <class C>
bool CStringTemplate<C>::replace(const CStringTemplate<C>& source, const CStringTemplate<C>& target, bool caseSensitive) {
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

template <class C>
inline bool CStringTemplate<C>::isInt(int start, int length, int * pValue) const {
    long lResult = 0;
    if (isLong(start, length, &lResult)) {
        if (pValue) *pValue = (int)lResult;
        return true;
    }
    return false;
}

template <class C>
inline bool CStringTemplate<C>::isLong(int pos, int length, long * pValue) const {
    int sign = 1;
    long newValue = 0;
    if (pos + length > (int)m_Length) length = (int)m_Length - pos;
    if (pos >= (int)m_Length) return false;
    if (m_Data[pos] == '-') { pos++; length--; sign = -1; }
    else if (m_Data[pos] == '+') { pos++; length--; }
    if (pos >= (int)m_Length) return false;
    while (length--) {
        if (!isdigit(m_Data[pos])) return false;
        newValue *= 10;
        newValue += (int)(m_Data[pos] - '0');
        pos++;
    }
    newValue *= sign;
    if (pValue) *pValue = newValue;
    return true;
}

template <class C>
inline void CStringTemplate<C>::removeDuplicate(const C chLeft, const C chRight) {
    if (m_Length <= 1) return;
    int l2 = 0;
    for (int l1 = 0; l1 < (int)m_Length - 1; l1++) {
        if (!(CSTRING_INTERVAL(m_Data[l1], chLeft, chRight) &&
              CSTRING_INTERVAL(m_Data[l1 + 1], chLeft, chRight))) {
            m_Data[l2] = m_Data[l1];
            l2++;
        }
    }
    m_Data[l2] = m_Data[m_Length - 1];
    m_Length = l2 + 1;
    m_Data[m_Length] = 0;
}

template <class C>
inline void CStringTemplate<C>::remove(const C chLeft, const C chRight) {
    int l2 = 0;
    for (int l1 = 0; l1 < (int)m_Length; l1++) {
        if (!CSTRING_INTERVAL(m_Data[l1], chLeft, chRight)) {
            m_Data[l2] = m_Data[l1];
            l2++;
        }
    }
    m_Length = l2;
    m_Data[m_Length] = 0;
}

template <class C>
inline bool CStringTemplate<C>::terminateWith(const C ch) {
    if (!m_Length || m_Data[m_Length - 1] != ch) {
        append(ch);
        return true;
    }
    return false;
}

template <class C>
inline int CStringTemplate<C>::getInt(const int start, const int length) const {
    int Result = 0;
    isInt(start, length, &Result);
    return Result;
}

template <class C>
inline void CStringTemplate<C>::toUpper(void) {
    for (int i = 0; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'z') && (m_Data[i] >= 'a'))
            m_Data[i] -= ('a' - 'A');
}

template <class C>
inline void CStringTemplate<C>::toLower(void) {
    for (int i = 0; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'Z') && (m_Data[i] >= 'A'))
            m_Data[i] += ('a' - 'A');
}

template <class C>
inline bool CStringTemplate<C>::hasUpper(int start) const {
    for (int i = start; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'Z') && (m_Data[i] >= 'A')) return true;
    return false;
}

template <class C>
inline bool CStringTemplate<C>::hasLower(int start) const {
    for (int i = start; i < (int)m_Length; i++)
        if ((m_Data[i] <= 'z') && (m_Data[i] >= 'a')) return true;
    return false;
}

template <class C>
inline void CStringTemplate<C>::reverse(void) {
    C ch;
    for (int i = 0; i < ((int)m_Length) / 2; i++) {
        ch = m_Data[i];
        m_Data[i] = m_Data[m_Length - 1 - i];
        m_Data[m_Length - 1 - i] = ch;
    }
}

template <class C>
inline int CStringTemplate<C>::lastIndexOf(const C ch) const {
    return lastIndexOf(ch, ((int)m_Length) - 1);
}

template <class C>
inline int CStringTemplate<C>::lastIndexOf(const C ch, const int start) const {
    for (int i = start; i >= 0; i--)
        if (m_Data[i] == ch) return i;
    return -1;
}

template <class C>
inline int CStringTemplate<C>::indexOf(const C ch, const int start) const {
    for (int i = start; i < (int)m_Length; i++)
        if (m_Data[i] == ch) return i;
    return -1;
}

template <class C>
inline int CStringTemplate<C>::indexOf(const CStringTemplate<C>& str, const int start) const {
    for (int i = start; i < (int)m_Length - (int)str.m_Length + 1; i++)
        if (!(memcmp(m_Data + i, str.m_Data, str.m_Length))) return i;
    return -1;
}

template <class C>
inline int CStringTemplate<C>::indexOfIgnoreCase(const CStringTemplate<C>& str, const int start) const {
    for (int i = start; i < ((int)m_Length) - ((int)str.m_Length) + 1; i++)
        if (compareIgnoreCase(str, i, false) == 0) return i;
    return -1;
}

template <class C>
inline bool CStringTemplate<C>::replace(const C chLeft, const C chRight, const C chTarget) {
    bool result = false;
    for (int i = 0; i < (int)m_Length; i++) {
        if (CSTRING_INTERVAL(m_Data[i], chLeft, chRight)) {
            m_Data[i] = chTarget;
            result = true;
        }
    }
    return result;
}

template <class C>
inline bool CStringTemplate<C>::replace(const C source, const C target) {
    bool result = false;
    for (int i = 0; i < (int)m_Length; i++) {
        if (m_Data[i] == source) {
            m_Data[i] = target;
            result = true;
        }
    }
    return result;
}

template <class C>
inline int CStringTemplate<C>::count(const C ch) const {
    int Result = 0;
    for (int i = 0; i < (int)m_Length; i++)
        if (m_Data[i] == ch) Result++;
    return Result;
}

template <class C>
inline int CStringTemplate<C>::count(const C chLeft, const C chRight) const {
    int Result = 0;
    for (int i = 0; i < (int)m_Length; i++)
        if (CSTRING_INTERVAL(m_Data[i], chLeft, chRight)) Result++;
    return Result;
}

template <class C>
inline bool CStringTemplate<C>::isInt(int * value) const {
    return isInt(0, m_Length, value);
}

template <class C>
inline bool CStringTemplate<C>::isHex(int * value) const {
    if (!m_Length) return false;
    for (int i = 0; i < (int)m_Length; i++) {
        if ((!isdigit(m_Data[i])) &&
            ((m_Data[i] > 'F') || (m_Data[i] < 'A')) &&
            ((m_Data[i] > 'f') || (m_Data[i] < 'a')))
            return false;
    }
    if (value) sscanf((const C *)m_Data, "%x", value);
    return true;
}

template <class C>
inline bool CStringTemplate<C>::isFloat(float * value) const {
    bool separator = false;
    int i = 0, sign = 1, displ = 0;
    if (m_Length && (m_Data[0] == '-')) { i++; displ++; sign = -1; }
    if (i == (int)m_Length) return false;
    for (; i < (int)m_Length; i++) {
        if (!isdigit(m_Data[i])) {
            if (separator) return false;
            else if (m_Data[i] == '.') separator = true;
            else return false;
        }
    }
    if (value) *value = (float)(atof((const C *)m_Data + displ) * sign);
    return true;
}

template <class C>
inline bool CStringTemplate<C>::isLong(long * value) const {
    return isLong(0, m_Length, value);
}

template <class C>
inline int CStringTemplate<C>::indexOf(const C * const buffer, const int len, const int start) const {
    int length = (int)m_Length - len + 1;
    for (int i = start; i < length; i++)
        if (compare(buffer, len, i, false) == 0) return i;
    return -1;
}

template <class C>
inline int CStringTemplate<C>::indexOfIgnoreCase(const C * const buffer, const int len, const int start) const {
    int length = (int)m_Length - len + 1;
    for (int i = start; i < length; i++)
        if (compareIgnoreCase(buffer, len, i, false) == 0) return i;
    return -1;
}

template <class C>
inline void CStringTemplate<C>::append(const C * const buffer) {
    if (buffer) append(buffer, base_strlen(buffer));
}

template <class C>
inline void CStringTemplate<C>::setSize(unsigned int desiredSize, bool preserve) {
    if (desiredSize <= m_Size) return;
    unsigned int size = desiredSize;
    if (size < (unsigned int)MBYTE) {
        size = (m_Size << 1) + 1;
        while (size < desiredSize) size <<= 1;
    } else {
        size = ((size + KBYTE - 1) / KBYTE) * KBYTE;
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

template <class C>
inline void CStringTemplate<C>::append(const CStringTemplate<C>& str) {
    setSize(m_Length + str.m_Length + 1, true);
    memcpy(m_Data + m_Length, str.m_Data, str.m_Length);
    m_Length += str.m_Length;
    m_Data[m_Length] = 0;
}

template <class C>
inline void CStringTemplate<C>::append(const C c) {
    setSize(m_Length + 2, true);
    m_Data[m_Length] = c;
    m_Length++;
    m_Data[m_Length] = 0;
}

template <class C>
inline void CStringTemplate<C>::append(const C * const buffer, int rightLength) {
    if (rightLength) {
        setSize(m_Length + (unsigned int)rightLength + 1, true);
        memcpy(m_Data + m_Length, buffer, (unsigned int)rightLength);
        m_Length += (unsigned int)rightLength;
        m_Data[m_Length] = 0;
    }
}

template <class C>
inline void CStringTemplate<C>::operator=(const C c) {
    setSize(2, false);
    m_Data[0] = c;
    m_Data[1] = 0;
    m_Length = 1;
}

template <class C>
inline void CStringTemplate<C>::operator=(const C * const buffer) {
    copyBuffer(buffer);
}

template <class C>
inline void CStringTemplate<C>::operator=(const CStringTemplate<C>& refStr) {
    copyBuffer(refStr.m_Data, refStr.m_Length);
}

template <class C>
inline void CStringTemplate<C>::moveFrom(CStringTemplate<C>& refStr) {
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
        refStr.m_Size = CSTRING_STACK_SIZE;
        refStr.m_Data = refStr.m_StackData;
        refStr.m_Data[0] = 0;
        refStr.m_Length = 0;
    }
}

template <class C>
inline void CStringTemplate<C>::setLength(void) {
    m_Length = 0;
    for (int i = 0; i < (int)m_Size; i++) {
        if (m_Data[i] == 0) { m_Length = i; break; }
    }
}

template <class C>
inline void CStringTemplate<C>::setLength(unsigned int length, C fillChar, bool fill) {
    setSize(length + 1, true);
    if (length != m_Length) {
        if ((length > m_Length) && fill)
            memset(m_Data + m_Length, fillChar, length - m_Length);
        m_Data[length] = 0;
        m_Length = length;
    }
}

template <class C>
inline bool CStringTemplate<C>::equalsIgnoreCase(const C * str, int len) const {
    if ((int)m_Length != len) return false;
    for (int i = 0; i < len; i++)
        if (toLowerChar(m_Data[i]) != toLowerChar(str[i])) return false;
    return true;
}

template <class C>
inline bool CStringTemplate<C>::equals(const C * str, int len) const {
    if ((int)m_Length != len) return false;
    for (int i = 0; i < len; i++)
        if (m_Data[i] != str[i]) return false;
    return true;
}

template <class C>
inline bool CStringTemplate<C>::notEquals(const C * str, int len) const {
    if ((int)m_Length != len) return true;
    for (int i = 0; i < len; i++)
        if (m_Data[i] != str[i]) return true;
    return false;
}

template <class C>
inline int CStringTemplate<C>::compare(const C * str, int len, int start, bool respectLength) const {
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

template <class C>
inline int CStringTemplate<C>::compareIgnoreCase(const C * str, int len, int start, bool respectLength) const {
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

template <class C>
inline bool CStringTemplate<C>::startsWithIgnoreCase(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (toLowerChar(m_Data[i]) != toLowerChar(str[i])) return false;
    return true;
}

template <class C>
inline bool CStringTemplate<C>::startsWith(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (m_Data[i] != str[i]) return false;
    return true;
}

template <class C>
inline bool CStringTemplate<C>::endsWithIgnoreCase(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (toLowerChar(m_Data[i + (m_Length - len)]) != toLowerChar(str[i])) return false;
    return true;
}

template <class C>
inline bool CStringTemplate<C>::endsWith(const C * str, int len) const {
    if ((int)m_Length < len) return false;
    for (int i = 0; i < len; i++)
        if (m_Data[i + (m_Length - len)] != str[i]) return false;
    return true;
}

template <class C>
inline void CStringTemplate<C>::insert(const unsigned int pos, const CStringTemplate<C>& str) {
    if (pos >= m_Length) append(str);
    else if (&str == this) {
        CStringTemplate<C> Tmp(str);
        insert(pos, Tmp);
    } else if (str.m_Length) {
        setSize(m_Length + str.m_Length + 1, true);
        for (int i = (int)m_Length; i >= (int)pos; i--)
            m_Data[i + str.m_Length] = m_Data[i];
        memcpy(m_Data + pos, str.m_Data, str.m_Length);
        m_Length += str.m_Length;
    }
}

template <class C>
inline void CStringTemplate<C>::insert(const unsigned int pos, const C c) {
    if (pos >= m_Length) append(c);
    else {
        setSize(m_Length + 2, true);
        for (int i = (int)m_Length; i >= (int)pos; i--)
            m_Data[i + 1] = m_Data[i];
        m_Data[pos] = c;
        m_Length++;
    }
}

template <class C>
inline void CStringTemplate<C>::insert(const unsigned int pos, const C * const buffer, int bufferLen) {
    if (pos >= m_Length) append(buffer, bufferLen);
    else if (buffer) {
        if (bufferLen < 0) bufferLen = base_strlen(buffer);
        if (bufferLen) {
            setSize(m_Length + (unsigned int)bufferLen + 1, true);
            for (int i = (int)m_Length; i >= (int)pos; i--)
                m_Data[i + (unsigned int)bufferLen] = m_Data[i];
            memcpy(m_Data + pos, buffer, bufferLen);
            m_Length += (unsigned int)bufferLen;
        }
    }
}

template <class C>
inline void CStringTemplate<C>::erase(int start, int count) {
    if (start < 0) { count += start; start = 0; }
    if (start >= (int)m_Length) return;
    if (count + start >= (int)m_Length) count = m_Length - start;
    if (count <= 0) return;
    for (int i = start; i < ((int)m_Length - count); i++)
        m_Data[i] = m_Data[i + count];
    m_Length -= count;
    m_Data[m_Length] = 0;
}

template <class C>
inline void CStringTemplate<C>::trimRight(const C LChar, const C RChar) {
    if (m_Length) {
        C * m_DataRight = m_Data + (int)m_Length - 1;
        while ((m_DataRight >= m_Data) && (m_DataRight[0] >= LChar) && (m_DataRight[0] <= RChar))
            m_DataRight--;
        if (m_DataRight != (m_Data + (int)m_Length - 1))
            erase(m_DataRight - m_Data + 1, (int)m_Length - (m_DataRight - m_Data) + 1);
    }
}

template <class C>
inline void CStringTemplate<C>::trimLeft(const C LChar, const C RChar) {
    if (m_Length) {
        C * m_DataLeft = m_Data;
        while (((m_DataLeft[0] >= LChar) && (m_DataLeft[0] <= RChar)) && (m_DataLeft < (m_Data + (int)m_Length)))
            m_DataLeft++;
        if (m_DataLeft != m_Data) erase(0, m_DataLeft - m_Data);
    }
}

template <class C>
inline void CStringTemplate<C>::clear(void) {
    if (m_Length) { m_Data[0] = 0; m_Length = 0; }
}

template <class C>
inline void CStringTemplate<C>::copyBuffer(const C * const buffer) {
    if (buffer) copyBuffer(buffer, base_strlen(buffer));
    else clear();
}

template <class C>
inline void CStringTemplate<C>::copyBuffer(const C * const buffer, int length) {
    setSize(length + 1, false);
    memcpy(m_Data, buffer, length);
    m_Data[length] = 0;
    m_Length = length;
}

template <class C>
inline void CStringTemplate<C>::initialize(void) {
    m_Data = m_StackData;
    m_RealAllocData = NULL;
    m_Length = 0;
    m_Size = CSTRING_STACK_SIZE;
    m_Data[0] = 0;
}

/* explicit instantiation for char */
template class CStringTemplate<char>;
