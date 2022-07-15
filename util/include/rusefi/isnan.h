#pragma once

#if defined(__cplusplus) && defined(__OPTIMIZE__)
#include <type_traits>
// "g++ -O2" version, adds more strict type check and yet no "strict-aliasing" warnings!
#define cisnan(f) ({ \
	static_assert(sizeof(f) == sizeof(int32_t)); \
	union cisnanu_t { std::remove_reference_t<decltype(f)> __f; int32_t __i; } __cisnan_u = { f }; \
	__cisnan_u.__i == 0x7FC00000; \
})
#else
// "g++ -O0" or other C++/C compilers
#define cisnan(f) (*(((int*) (&f))) == 0x7FC00000)
#endif /* __cplusplus && __OPTIMIZE__ */
