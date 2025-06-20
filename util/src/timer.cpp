#include <rusefi/timer.h>
#include <rusefi/rusefi_time_math.h>

void Timer::reset() {
	m_lastReset = getTimeNowNt();
}

void Timer::init() {
	// Use not-quite-minimum value to avoid overflow
	m_lastReset = InitialState;
}

void Timer::reset(efitick_t const nowNt) {
	m_lastReset = nowNt;
}

bool Timer::hasElapsedSec(float const seconds) const {
	return hasElapsedMs(seconds * 1000);
}

bool Timer::hasElapsedMs(float const milliseconds) const {
	return hasElapsedUs(milliseconds * 1000);
}

bool Timer::hasElapsedUs(float const microseconds) const {
	// Like past has already passed...
	if (microseconds <= 0) {
		return true;;
	}

	efitick_t const delta{ getTimeNowNt() - m_lastReset };

	// If larger than 32 bits, timer has certainly expired
	if (delta >= UINT32_MAX) {
		return true;
	}

	constexpr float max_32_bit_fit_float{ 4294967295.f };

	if (microseconds >= max_32_bit_fit_float) {
		auto const ntDouble{ static_cast<double>(microseconds) * US_TO_NT_MULTIPLIER };
		return delta > static_cast<efitick_t>(ntDouble);
	}

	return static_cast<uint32_t>(delta) > static_cast<uint32_t>(USF2NT(microseconds));
}

float Timer::getElapsedSeconds() const {
	return getElapsedSeconds(getTimeNowNt());
}

float Timer::getElapsedSeconds(efitick_t nowNt) const {
	return 1.f / US_PER_SECOND_F * getElapsedUs(nowNt);
}

float Timer::getElapsedUs() const {
	return getElapsedUs(getTimeNowNt());
}

uint32_t Timer::getElapsedNt(efitick_t const nowNt) const {
	int64_t const deltaNt{ nowNt - m_lastReset };

	// Yes, things can happen slightly in the future if we get a lucky interrupt between
	// the timestamp and this subtraction, that updates m_lastReset to what's now "the future",
	// resulting in a negative delta.
	if (deltaNt < 0) {
		return 0;
	}

	return deltaNt >= static_cast<int64_t>(UINT32_MAX) ? UINT32_MAX : static_cast<uint32_t>(deltaNt);
}

float Timer::getElapsedUs(efitick_t const nowNt) const {
	// Wraparound is not considered
	auto const delta32{ getElapsedNt(nowNt) };

	// One second at 168mhz is 168 mil of ticks
	// float loses precision after 24bit ~ 16777216us;
	// 16777216us / 1mil ~ 16.8s. So after 16s we lose precision
	// On faster chips precision is lost proportionally
	constexpr uint32_t max_exact_float_int{ 16777216 };
	constexpr uint32_t max_exact_int{ max_exact_float_int * US_TO_NT_MULTIPLIER };

	// Waited too long, calculate in double to keep precision
	// It is not like someone will be unhappy seeing elapsed time being up to 250us higher/lower after 16s
	// It is to prevent error accumulation somewhere
	if (delta32 > max_exact_int) {
		auto const delta32f{ static_cast<double>(delta32) };
		return static_cast<float>(NT2US(delta32f));
	}

	// Ok less than 16s so can be float for faster calc while keeping precision
	auto const delta32f{ static_cast<float>(delta32) };
	return static_cast<float>(NT2US(delta32f));
}

float Timer::getElapsedSecondsAndReset(efitick_t const nowNt) {
	float const result{ getElapsedSeconds(nowNt) };

	reset(nowNt);

	return result;
}

[[nodiscard]] efitick_t Timer::get() const {
	return m_lastReset;
}
