#pragma once

#include <type_traits>

#include <rusefi/rusefi_time_types.h>

static_assert(
    std::is_same_v<decltype(US_TO_NT_MULTIPLIER), int>,
    "US_TO_NT_MULTIPLIER macro should be defined as a positive integer value"
);

constexpr int TICKS_IN_US = US_TO_NT_MULTIPLIER;

static_assert(0 < TICKS_IN_US, "US_TO_NT_MULTIPLIER macro should be defined as a positive integer value");

// microseconds to ticks, but floating point
// If converting a floating point time period, use this macro to avoid
// the expensive conversions from int64 <-> float
#define USF2NT(us_float) ((us_float) * TICKS_IN_US)
#define USF2MS(us_float) (0.001f * (us_float))

// And back
#define NT2US(x) ((x) / TICKS_IN_US)
#define NT2USF(x) (((float)(x)) / TICKS_IN_US)

#define NT_PER_SECOND (US2NT(US_PER_SECOND_LL))

#if EFI_UNIT_TEST
// In unit tests, we can time travel...
void setTimeNowUs(int us);
void advanceTimeUs(int us);
#endif
