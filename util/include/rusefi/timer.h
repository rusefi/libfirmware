/**
 * @file timer.h
 */

#pragma once

#include <rusefi/rusefi_time_types.h>

/**
 * Helper class with "has X amount of time elapsed since most recent reset" methods
 * Brand new instances have most recent reset time far in the past, i.e. "hasElapse" is true for any reasonable range
 */
class Timer final {
public:
	Timer() = default;

	void reset();

	// Reset the timer to a known timestamp (don't take a timestamp internally)
	void reset(efitick_t nowNt);

	// returns timer to the most original-as-constructed state
	void init();

	[[nodiscard]] bool hasElapsedSec(float seconds) const;
	[[nodiscard]] bool hasElapsedMs(float ms) const;
	[[nodiscard]] bool hasElapsedUs(float us) const;

	// Return the elapsed time since the last reset.
	// If the elapsed time is longer than 2^32 timer tick counts,
	// then a time period representing 2^32 counts will be returned.
	[[nodiscard]] float getElapsedSeconds() const;
	[[nodiscard]] float getElapsedSeconds(efitick_t nowNt) const;
	[[nodiscard]] float getElapsedUs() const;
	// WOW yes returns US while parameter is NT
	[[nodiscard]] float getElapsedUs(efitick_t nowNt) const;
	// too many options for the API probably?
	[[nodiscard]] uint32_t getElapsedNt(efitick_t nowNt) const;

	// Perform an atomic update event based on the passed timestamp,
	// returning the delta between the last reset and the provided timestamp
	[[nodiscard]] float getElapsedSecondsAndReset(efitick_t nowNt);

	[[nodiscard]] efitick_t get() const;

	static constexpr efitick_t InitialState = INT64_MIN / 8;

private:
	efitick_t m_lastReset{InitialState};
};
