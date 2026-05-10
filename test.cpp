#include <string/string.hpp>
#include <iostream>

int main() {
    CString s("Hello, World!");
    cout << s << endl;

    s.toUpper();
    cout << s << endl;

    s.toLower();
    cout << s << endl;

    CString trimmed("  hello  ");
    trimmed.trim();
    cout << "[" << trimmed << "]" << endl;

    cout << "length: " << s.length() << endl;
    cout << "startsWith 'hello': " << s.startsWith("hello") << endl;
    cout << "equalsIgnoreCase 'HELLO, WORLD!': " << s.equalsIgnoreCase("HELLO, WORLD!") << endl;
    cout << "indexOf('o'): " << s.indexOf('o') << endl;

    CString n = CString::fromInt(42);
    cout << "fromInt(42): " << n << endl;
    cout << "toInt: " << CString::toInt(n) << endl;

    return 0;
}
