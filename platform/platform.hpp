#ifndef BASE_PLATFORM_HPP
#define BASE_PLATFORM_HPP

#ifndef __cplusplus
#error C++ Compiler Required
#endif

#if !defined(_WIN32) && !defined(_MAC)
#define _UNIX
#else
#undef _UNIX
#endif

#ifdef HAVE_CONFIG_H
#include "config.hpp"
#endif

#endif
