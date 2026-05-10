#ifndef BASE_DEFINES_HPP
#define BASE_DEFINES_HPP

#ifdef _UNIX
#define base_strlen(x)      ::strlen((const char *)(x))
#define base_snprintf       snprintf
#define base_vsnprintf      vsnprintf
#endif

#ifdef _WIN32
#define base_strlen(x)      ::strlen((const char *)(x))
#define base_snprintf       _snprintf
#define base_vsnprintf      _vsnprintf
#endif

#define KBYTE   1024
#define MBYTE   1048576L
#define GBYTE   1073741824L

#define BASE_MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define BASE_MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define BASE_DIM(X)    (int)(sizeof(X) / sizeof(X[0]))

#endif
