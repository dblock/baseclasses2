# baseclasses2

A modernized C++ string library extracted from [baseclasses](https://github.com/dblock/baseclasses) (Vestris Inc., 1994–1999).

## What's included

- `src/string.hpp` — `CStringTemplate<C, StackSize>` class template + `CStringA`, `CStringW`, `CString` typedefs
- `src/string_impl.hpp` — all template implementations (include to instantiate custom StackSizes)
- `src/string.cpp` — explicit instantiations for `char` and `wchar_t` at default StackSize
- `platform/` — lightweight platform headers
- `tests/` — CppUnit test suite (120 tests)

Removed from the original: Object, Vector, Internet (URL/HTML), EStrings, GStrings, StringTable, tracing, and property macros.

API uses modern camelCase conventions (`toUpper`, `trim`, `indexOf`, etc.).

## Types

| Type | Character | Default stack buffer |
|---|---|---|
| `CString` / `CStringA` | `char` | 18 chars |
| `CStringW` | `wchar_t` | 18 wide chars |
| `CStringTemplate<C, StackSize>` | any | custom |

Strings up to `StackSize - 1` characters are stored on the stack with no heap allocation. Longer strings spill to the heap transparently.

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
    -o tests/run_tests \
    tests/main.cpp tests/string_test.cpp tests/wstring_test.cpp \
    tests/stack_size_test.cpp tests/stack_size_inst.cpp \
    src/string.cpp
./tests/run_tests
```

## Quick compile (no autoconf)

```sh
g++ -std=c++11 -I. -Isrc -o myapp myapp.cpp src/string.cpp
```

## Usage

```cpp
#include <string.hpp>

// char strings
CString a("Hello, World!");
a.toUpper();                              // "HELLO, WORLD!"
a.trim();                                 // strip whitespace
bool b = a.equalsIgnoreCase("hello");     // case-insensitive compare
int  i = a.indexOf('o');                  // find character
CString n = CString::fromInt(42);         // int → string
int  v = CString::toInt(n);              // string → int

// wide strings
CStringW w(L"héllo");
w.toLower();

// custom stack size (no heap allocation for strings ≤ 63 chars)
CStringTemplate<char, 64> s("short");
```

### Interoperability across StackSizes

Strings with different `StackSize` values freely interoperate:

```cpp
CStringTemplate<char, 4>  small("hi");
CStringTemplate<char, 32> large("hi");

large = small;          // assign across sizes
bool eq = (small == large);  // compare across sizes
large.append(small);    // concatenate across sizes
CStringTemplate<char, 4> copy(large);  // construct across sizes
```

To use a non-default `StackSize` in your own code, include the implementation
header and add an explicit instantiation in one `.cpp` file:

```cpp
// mystring_inst.cpp
#include <string_impl.hpp>
template class CStringTemplate<char, 64>;
```

## API reference

### Construction
| Expression | Description |
|---|---|
| `CString s` | empty string |
| `CString s("hello")` | from C string |
| `CString s('x')` | from character |
| `CString s(other)` | copy (same or different StackSize) |
| `s = other` | assign (same or different StackSize) |

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
| Operators `==`, `!=`, `<`, `>`, `<=`, `>=` | standard comparisons (works across StackSizes) |

### Modification
| Method | Description |
|---|---|
| `append(s)` / `+=` | concatenate (works across StackSizes) |
| `insert(pos, s)` | insert at position |
| `erase(start, count)` | remove characters |
| `replace(src, tgt)` | replace substring |
| `trim(ch)` | strip character from both ends |
| `trimLeft()` / `trimRight()` | strip from one end |
| `trimSpace()` | strip all whitespace (0–space range) |
| `reverse()` | reverse in place |
| `clear()` | empty the string |

### Substrings
| Method | Description |
|---|---|
| `mid(first, count)` | extract substring |
| `left(count)` | left N characters |
| `right(count)` | right N characters |
| `getLine(pos)` | extract next line (advances pos) |
| `extractLine()` | remove and return first line |

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

