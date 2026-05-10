#ifndef BASE_DEBUG_HPP
#define BASE_DEBUG_HPP

#ifdef _DEBUG
#define BASE_DEBUG
#endif

#ifdef BASE_DEBUG
#define _S_DEBUG(x) x
#else
#define _S_DEBUG(x)
#endif

#endif
