// file rusefi_time_types.h

#pragma once

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

/**
 * 64 bit time in microseconds (1/1_000_000 of a second), since boot
 */
using efitimeus_t = int64_t;

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

#define MS2US(MS_TIME) ((MS_TIME) * 1000)
#define US2MS(US_TIME) ((US_TIME) / 1000)
