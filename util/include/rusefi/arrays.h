#pragma once

#include <cstddef>
#include <cstring>
#include <cmath>

#include "scaled_channel.h"
#include "critical_error.h"

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

/**
 * Copies an array from src to dest.  The lengths can be different
 * if dest is larger, the array is interpolated, otherwise, values are stepped to preserve the range
 * on interpolation we use float and then cast to DElement
 */
template <typename DElement, typename SElement, size_t NDest, size_t NSrc, int roundDigits = 2>
constexpr void copyArrayInterpolated(DElement (&dest)[NDest], const SElement (&src)[NSrc]) {
	if constexpr (NDest == NSrc) {
		// Same size - direct copy
		copyArray(dest, src);
	} else if constexpr (NDest > NSrc) {
		// Destination larger - interpolate
		const float roundScale = pow(10, roundDigits);
		constexpr float step = static_cast<float>(NSrc - 1) / (NDest - 1);

		for (size_t i = 0; i < NDest; i++) {
			const float currentSrcPos = static_cast<float>(i) * step;
			auto srcIdx = static_cast<size_t>(currentSrcPos);
			const float frac = currentSrcPos - static_cast<float>(srcIdx);

			if (srcIdx >= NSrc - 1) {
				dest[i] = src[NSrc - 1];
			} else {
				float interpolated = static_cast<float>(src[srcIdx]) * (1.0f - frac) + static_cast<float>(src[srcIdx + 1]) * frac;
				if constexpr (roundDigits >= 0) {
					// Round to specified decimal places
					float rounded = static_cast<float>(static_cast<int>(interpolated * roundScale + 0.5f)) / roundScale;
					dest[i] = static_cast<DElement>(rounded);
				} else {
					dest[i] = static_cast<DElement>(interpolated);
				}
			}
		}
	} else {
		// Destination smaller - step through source to preserve range
		for (size_t i = 0; i < NDest; i++) {
			size_t srcIdx = i * (NSrc - 1) / (NDest - 1);
			dest[i] = src[srcIdx];
		}
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
#ifdef WE_HAVE_CRITICAL_ERROR_METHOD
  if (obj == nullptr) {
    efiCriticalError("clear nullptr");
    return;
  }
#endif // WE_HAVE_CRITICAL_ERROR_METHOD
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
