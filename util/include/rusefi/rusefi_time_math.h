
#include <global.h>
#include <rusefi/rusefi_time_types.h>

// microseconds to ticks, but floating point
// If converting a floating point time period, use this macro to avoid
// the expensive conversions from int64 <-> float
#define USF2NT(us_float) ((us_float) * US_TO_NT_MULTIPLIER)
#define USF2MS(us_float) (0.001f * (us_float))

// And back
#define NT2US(x) ((x) / US_TO_NT_MULTIPLIER)
#define NT2USF(x) (((float)(x)) / US_TO_NT_MULTIPLIER)

#define NT_PER_SECOND (US2NT(US_PER_SECOND_LL))
