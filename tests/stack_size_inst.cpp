/*
    baseclasses2
    https://github.com/dblock/baseclasses2
    Explicit instantiations for non-default StackSizes used in tests.
*/

#include <string_impl.hpp>

template class CStringTemplate<char,    4>;
template class CStringTemplate<char,   32>;
template class CStringTemplate<wchar_t, 4>;
template class CStringTemplate<wchar_t, 32>;
