#include <rusefi/rusefi_time_math.h>

static efitick_t timeNowNt = 0;

efitick_t getTimeNowNt() {
	return timeNowNt;
}

efitimeus_t getTimeNowUs() {
	return NT2US(getTimeNowNt());
}

efitimesec_t getTimeNowS() {
	return getTimeNowUs() / 1000 / 1000;
}

void setTimeNowNt(efitick_t nt) {
	timeNowNt = nt;
}

void setTimeNowUs(int us) {
	setTimeNowNt(USF2NT((efitick_t)us));
}

void advanceTimeUs(int us) {
	timeNowNt += USF2NT((efitick_t)us);
}
