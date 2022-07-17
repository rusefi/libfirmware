#pragma once

#include <cstddef>
#include <cstring>

#include "scaled_channel.h"

/**
 * Copies an array from src to dest.  The lengths of the arrays must match.
 */
template <typename DElement, typename SElement, size_t N>
constexpr void copyArray(DElement (&dest)[N], const SElement (&src)[N]) {
	for (size_t i = 0; i < N; i++) {
		dest[i] = src[i];
	}
}

// specialization that can use memcpy when src and dest types match
template <typename DElement, size_t N>
constexpr void copyArray(scaled_channel<DElement, 1, 1> (&dest)[N], const DElement (&src)[N]) {
	memcpy(dest, src, sizeof(DElement) * N);
}

template <typename DElement, size_t N>
constexpr void copyArray(DElement (&dest)[N], const DElement (&src)[N]) {
	memcpy(dest, src, sizeof(DElement) * N);
}

/**
 * Copies an array from src to the beginning of dst.  If dst is larger
 * than src, then only the elements copied from src will be touched.
 * Any remaining elements at the end will be untouched.
 */
template <typename TElement, size_t NSrc, size_t NDest>
constexpr void copyArrayPartial(TElement (&dest)[NDest], const TElement (&src)[NSrc]) {
	static_assert(NDest >= NSrc, "Source array must be larger than destination.");

	for (size_t i = 0; i < NSrc; i++) {
		dest[i] = src[i];
	}
}

namespace efi
{
template <typename T, size_t N>
constexpr size_t size(const T(&)[N]) {
    return N;
}

// Zero the passed object
template <typename T>
constexpr void clear(T* obj) {
	// The cast to void* is to prevent errors like:
	//    clearing an object of non-trivial type 'struct persistent_config_s'; use assignment or value-initialization instead
	// This is technically wrong, but we know config objects only ever actually
	// contain integral types, though they may be wrapped in a scaled_channel
	memset(reinterpret_cast<void*>(obj), 0, sizeof(T));
}

template <typename T>
constexpr void clear(T& obj) {
	clear(&obj);
}
} // namespace efi
