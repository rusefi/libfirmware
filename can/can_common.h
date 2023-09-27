// We have a bit of a mess with too many useful usages of CAN and too little documentation at https://github.com/rusefi/rusefi/wiki/CAN

// we use ExtID but only 16 bits in comms protocol from ECU to GDI4
#define GDI4_BASE_ADDRESS 0xBB20

#define BENCH_TEST_BASE_ADDRESS 0x770000

enum class bench_test_packet_ids_e : int32_t {
	// ECU output
	EVENT_COUNTERS = BENCH_TEST_BASE_ADDRESS,
	// ECU output
	RAW_ANALOG_1,
	// ECU input
	IO_CONTROL,
	// ECU output
	BOARD_STATUS,
	// ECU output
	BUTTON_COUNTERS,
	// ECU output
	IO_META_INFO,
	// ECU output
	RAW_ANALOG_2,
};


// TEST_CONTROL_MAGIC_WORD

#define CAN_BENCH_HEADER 0x66
#define CAN_BENCH_GET_COUNT 0
#define CAN_BENCH_GET_SET 1
#define CAN_BENCH_GET_CLEAR 2
#define CAN_BENCH_SET_ENGINE_TYPE 3
