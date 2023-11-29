#pragma once

#include <rusefi/rusefi_time_types.h>

/**
 * Provide a 62-bit counter from a 32-bit counter source that wraps around.
 *
 * If you'd like it use it with a 16-bit counter, shift the source by 16 before passing it here.
 * This class is thread/interrupt-safe.
 */
struct WrapAround62 {
	uint64_t update(uint32_t source) {
		// Shift cannot be 31, as we wouldn't be able to tell if time is moving forward or
		// backward relative to m_upper.  We do need to handle both directions as our
		// "thread" can be racing with other "threads" in sampling stamp and updating
		// m_upper.
		constexpr unsigned shift = 30;

		uint32_t upper = m_upper;
		uint32_t relative_unsigned = source - (upper << shift);
		upper += int32_t(relative_unsigned) >> shift;
		m_upper = upper;

		// Yes we could just do upper<<shift, but then the result would span both halves of
		// the 64-bit result.  Doing it this way means we only operate on one half at a
		// time.  Source will supply those bits anyways, so we don't need them from
		// upper...
		return (efitick_t(upper >> (32 - shift)) << 32) | source;
	}

private:
	volatile uint32_t m_upper = 0;
};
