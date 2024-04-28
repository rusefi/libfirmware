// file rusefi_time_types.h

#pragma once

#include <chrono>
#include <cstdint>
#include <sys/types.h>

/**
 * We use a signed type here so that subtraction result is a proper negative value.
 * A typical use-case negative result is when we do 'timeNow() - timeOfEvent' where timeOfEvent
 * is actually after timeNow() due to interrupt context switches
 *
 * See getTimeNowNt()
 * See US2NT
 * See MS2US
 */

/**
 * platform-dependent tick since boot
 * in case of stm32f4 that's 32-bit timer ticks (SCHEDULER_TIMER_DEVICE == TIM5) extended to 64 bits
 */
using efitick_t = int64_t;

using efidurus_t = std::chrono::duration<int64_t, std::micro>;
static_assert(sizeof(efidurus_t) == 8);

/**
 * 64 bit time in microseconds (1/1_000_000 of a second), since boot
 */
using efitimeus_t = std::chrono::time_point<std::chrono::steady_clock, efidurus_t>;
static_assert(sizeof(efitimeus_t) == 8);

// time in seconds
using efitimesec_t = time_t;

/**
 * 64-bit counter of microseconds (1/1 000 000 of a second) since MCU reset
 *
 * By using 64 bit, we can achieve a very precise timestamp which does not overflow.
 * The primary implementation counts the number of CPU cycles from MCU reset.
 *
 * WARNING: you should use getTimeNowNt where possible for performance reasons.
 * The heaviest part is '__aeabi_ildivmod' - non-native 64 bit division
 */
efitimeus_t getTimeNowUs();

/**
 * 64-bit counter CPU/timer cycles since MCU reset
 *
 * See getTimeNowLowerNt for a quicker version which returns only lower 32 bits
 * Lower 32 bits are enough if all we need is to measure relatively short time durations
 * (BTW 2^32 cpu cycles at 168MHz is 25.59 seconds)
 */
efitick_t getTimeNowNt();

#define MS_PER_SECOND 1000
#define US_PER_SECOND 1000000
#define US_PER_SECOND_F 1000000.0
#define US_PER_SECOND_LL 1000000LL

template<typename ms_type>
constexpr auto MS2US(ms_type ms_time) {
  static_assert(
    std::is_integral_v<ms_type> || std::is_floating_point_v<ms_type>,
    "MS2US expects numeric type as parameter"
  );
  return ms_time * 1000;
}

template<typename ms_type>
constexpr auto US2MS(ms_type timeus) {
  static_assert(
    std::is_integral_v<ms_type> || std::is_floating_point_v<ms_type>,
    "US2MS expects numeric type or efitimeus_t as parameter"
  );
  return timeus / 1000;
}

constexpr efitimeus_t::rep US2MS(const efitimeus_t& timeus) {
  return timeus.time_since_epoch().count() / 1000;
}

template<typename ms_type>
constexpr efitimeus_t USOF(ms_type us) {
    static_assert(std::is_integral_v<ms_type>, "US2MS expects integral type as parameter");
    return efitimeus_t(efidurus_t(us));
}

constexpr efitimeus_t::rep COUNTOF(const efitimeus_t& us) {
 return us.time_since_epoch().count();
}
