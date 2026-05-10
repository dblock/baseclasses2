# baseclasses2

A modernized C++ string library extracted from [baseclasses](https://github.com/dblock/baseclasses) (Vestris Inc., 1994–1999).

## What's included

- `src/string.hpp` + `src/string.cpp` — `CStringTemplate<C>` / `CString`
- `platform/` — lightweight platform detection headers
- `tests/` — CppUnit test suite

Removed from the original: Object, Vector, Internet (URL/HTML), EStrings, GStrings, StringTable, tracing, and property macros.

API uses modern camelCase conventions (`toUpper`, `trim`, `indexOf`, etc.).

## Requirements

- **C++ compiler**: `g++` or `clang++` (C++11 or later)
- **autoconf** 2.69+: to regenerate `configure` from `configure.ac`
- **GNU make**
- **CppUnit** 1.15+: for running tests

Install on macOS with Homebrew:

```sh
brew install autoconf cppunit
```

## Building

```sh
autoconf
./configure
make
```

This produces `lib/libbasecl.a`.

## Running tests

```sh
make check
```

Or directly:

```sh
g++ -std=c++11 -I. -Isrc $(pkg-config --cflags --libs cppunit) \
    -o tests/run_tests tests/main.cpp tests/string_test.cpp src/string.cpp
./tests/run_tests
```

## Quick compile (no autoconf)

```sh
g++ -std=c++11 -I. -Isrc -o myapp myapp.cpp src/string.cpp
```

## Usage

```cpp
#include <string.hpp>

CString s("Hello, World!");
s.toUpper();                              // "HELLO, WORLD!"
s.toLower();                              // "hello, world!"
s.trim();                                 // strip whitespace
bool b = s.equalsIgnoreCase("HELLO");     // case-insensitive compare
int i = s.indexOf('o');                   // find character
CString n = CString::fromInt(42);         // int → string
int v = CString::toInt(n);               // string → int
```

## API reference

### Construction
| Expression | Description |
|---|---|
| `CString s` | empty string |
| `CString s("hello")` | from C string |
| `CString s('x')` | from character |
| `CString s(other)` | copy |

### Case
| Method | Description |
|---|---|
| `toUpper()` | convert to uppercase in place |
| `toLower()` | convert to lowercase in place |
| `hasUpper()` | true if any uppercase character |
| `hasLower()` | true if any lowercase character |
| `toUpperChar(c)` | uppercase a single char (static) |
| `toLowerChar(c)` | lowercase a single char (static) |

### Searching
| Method | Description |
|---|---|
| `indexOf(ch)` | first index of character |
| `indexOf(str)` | first index of substring |
| `indexOfIgnoreCase(str)` | case-insensitive substring search |
| `lastIndexOf(ch)` | last index of character |

### Comparison
| Method | Description |
|---|---|
| `equals(s)` | case-sensitive equality |
| `equalsIgnoreCase(s)` | case-insensitive equality |
| `notEquals(s)` | inequality |
| `startsWith(s)` | prefix check |
| `startsWithIgnoreCase(s)` | case-insensitive prefix |
| `endsWith(s)` | suffix check |
| `endsWithIgnoreCase(s)` | case-insensitive suffix |
| `compare(s)` | lexicographic compare |
| `compareIgnoreCase(s)` | case-insensitive compare |
| Operators `==`, `!=`, `<`, `>`, `<=`, `>=` | standard comparisons |

### Modification
| Method | Description |
|---|---|
| `append(s)` / `+=` | concatenate |
| `insert(pos, s)` | insert at position |
| `erase(start, count)` | remove characters |
| `replace(src, tgt)` | replace substring |
| `trim(ch)` | strip character from both ends |
| `trimLeft()` / `trimRight()` | strip from one end |
| `trimSpace()` | strip all whitespace (0–space range) |
| `reverse()` | reverse in place |
| `clear()` | empty the string |
| `toUpper()` / `toLower()` | change case in place |

### Substrings
| Method | Description |
|---|---|
| `mid(first, count, &result)` | extract substring |
| `left(count, &result)` | left N characters |
| `right(count, &result)` | right N characters |

### Numeric conversions
| Method | Description |
|---|---|
| `CString::fromInt(n)` | int → CString |
| `CString::fromLong(n)` | long → CString |
| `CString::fromFloat(f)` | float → CString |
| `CString::fromDouble(d)` | double → CString |
| `CString::toInt(s)` | CString → int |
| `CString::toLong(s)` | CString → long |
| `CString::toFloat(s)` | CString → float |
| `CString::toDouble(s)` | CString → double |
| `CString::toHex(s)` | hex CString → int |
| `isInt()` / `isFloat()` / `isLong()` / `isHex()` | type checks |
