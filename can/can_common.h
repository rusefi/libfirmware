// We have a bit of a mess with too many useful usages of CAN and too little documentation at https://github.com/rusefi/rusefi/wiki/CAN

// we use ExtID but only 16 bits in comms protocol from ECU to GDI4
#define GDI4_BASE_ADDRESS 0xBB20

#define GDI4_MAGIC 0x67

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
	// ECU output
	PIN_STATE,
	// ECU output
	AUX_DIGITAL_COUNTERS,
};

enum class bench_test_magic_numbers_e : int32_t {
    BENCH_HEADER = 0x66,
};

enum class bench_test_io_control_e : int8_t {
	CAN_BENCH_GET_COUNT,
	CAN_QC_OUTPUT_CONTROL_SET,
	CAN_QC_OUTPUT_CONTROL_CLEAR,
	CAN_BENCH_SET_ENGINE_TYPE,
	CAN_BENCH_EXECUTE_BENCH_TEST,
	CAN_BENCH_QUERY_PIN_STATE,
	CAN_BENCH_START_PIN_TEST,
	CAN_BENCH_END_PIN_TEST,
	CAN_QC_ETB,
};
