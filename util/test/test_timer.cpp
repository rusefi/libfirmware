/**
 * @file test_timer.cpp
 *
 */

#include <rusefi/timer.h>
#include <rusefi/rusefi_time_math.h>

#include <gtest/gtest.h>

// see mock/lib-time-mocks.cpp
void setTimeNowNt(efitick_t nt);

TEST(util, timerResetStampedInTheFuture) {
	Timer timer;

	efitick_t nowNt = USF2NT((efitick_t)10'000'000); // 10 seconds of uptime
	setTimeNowNt(nowNt);

	// sanity: reset stamped 100us in the past, nothing has elapsed yet
	timer.reset(nowNt - USF2NT((efitick_t)100));
	EXPECT_FALSE(timer.hasElapsedMs(250));

	// ISR stamps the reset 100us AFTER the checking thread sampled "now"
	timer.reset(nowNt + USF2NT((efitick_t)100));

	// getElapsedNt() has a negative-delta guard and correctly clamps to zero
	EXPECT_EQ(0u, timer.getElapsedNt(nowNt));

	// hasElapsedUs() must not wrap the negative delta into "elapsed": a freshly-reset
	// timer has not elapsed, no matter which side of the reset "now" was sampled on
	EXPECT_FALSE(timer.hasElapsedMs(250));

	setTimeNowNt(0);
}

/**
 * US_TO_NT_MULTIPLIER is 100 in this test build, so 32 bits of ticks is just under 43 seconds.
 * On real ports the horizon ranges from ~25 seconds (kinetis/cypress, multiplier 168) to
 * ~1073 seconds (stm32, multiplier 4). Timeouts longer than the horizon used to be reported
 * as elapsed the moment the delta crossed it, because the "delta larger than 32 bits" shortcut
 * ran before the long-timeout path.
 */
TEST(util, timerTimeoutLongerThan32BitsOfTicks) {
	Timer timer;
	timer.reset(0);

	// well inside the fast path: nothing surprising
	setTimeNowNt(USF2NT((efitick_t)20'000'000)); // 20 seconds
	EXPECT_FALSE(timer.hasElapsedSec(60));

	// past the 32-bit tick horizon but before the requested timeout: NOT elapsed
	setTimeNowNt(USF2NT((efitick_t)50'000'000)); // 50 seconds
	EXPECT_FALSE(timer.hasElapsedSec(60));

	setTimeNowNt(USF2NT((efitick_t)61'000'000)); // 61 seconds
	EXPECT_TRUE(timer.hasElapsedSec(60));

	setTimeNowNt(0);
}

TEST(util, timerHourLongTimeoutStaysExact) {
	Timer timer;
	timer.reset(0);

	setTimeNowNt(USF2NT((efitick_t)3'599'000'000)); // 3599 seconds
	EXPECT_FALSE(timer.hasElapsedSec(3600));

	setTimeNowNt(USF2NT((efitick_t)3'601'000'000)); // 3601 seconds
	EXPECT_TRUE(timer.hasElapsedSec(3600));

	setTimeNowNt(0);
}

TEST(util, brandNewTimerHasElapsedEvenForLongTimeouts) {
	// "Brand new instances have most recent reset time far in the past" - that promise from the
	// header must survive the long-timeout path too
	Timer timer;

	setTimeNowNt(0);
	EXPECT_TRUE(timer.hasElapsedSec(3600));
}
