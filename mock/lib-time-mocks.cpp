#include <rusefi/rusefi_time_math.h>

static int timeNowUs = 0;

efitimeus_t getTimeNowUs() {
	return USOF(timeNowUs);
}

efitimesec_t getTimeNowS() {
	return COUNTOF(getTimeNowUs()) / 1000 / 1000;
}

efitick_t getTimeNowNt() {
	return COUNTOF(getTimeNowUs()) * US_TO_NT_MULTIPLIER;
}

void setTimeNowUs(int us) {
	timeNowUs = us;
}

void advanceTimeUs(int us) {
	timeNowUs += us;
}
