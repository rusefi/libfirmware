#include <rusefi/rusefi_time_math.h>

int timeNowUs = 0;

efitimeus_t getTimeNowUs() {
	return timeNowUs;
}

efitimesec_t getTimeNowS() {
	return static_cast<efitimeus_t::value_type>(getTimeNowUs()) / 1000 / 1000;
}

efitick_t getTimeNowNt() {
	return (static_cast<efitimeus_t::value_type>(getTimeNowUs())) * US_TO_NT_MULTIPLIER;
}
