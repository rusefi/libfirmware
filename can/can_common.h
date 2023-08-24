// We have a bit of a mess with too many useful usages of CAN and too little documentation at https://github.com/rusefi/rusefi/wiki/CAN

// we use ExtID but only 16 bits in comms protocol from ECU to GDI4
#define GDI4_BASE_ADDRESS 0xBB20

#define BENCH_TEST_BASE_ADDRESS 0x770000

// todo: convert these commands into C++ enum and leverage enum2string code generator?
// ECU output
#define BENCH_TEST_EVENT_COUNTERS BENCH_TEST_BASE_ADDRESS
// ECU output
#define BENCH_TEST_RAW_ANALOG (BENCH_TEST_BASE_ADDRESS + 1)
// ECU input
#define BENCH_TEST_IO_CONTROL (BENCH_TEST_BASE_ADDRESS + 2)
// ECU output
#define BENCH_TEST_BOARD_STATUS (BENCH_TEST_BASE_ADDRESS + 3)
// ECU output
#define BENCH_TEST_BUTTON_COUNTERS (BENCH_TEST_BASE_ADDRESS + 4)
// ECU output
#define BENCH_TEST_IO_META_INFO (BENCH_TEST_BASE_ADDRESS + 5)


// TEST_CONTROL_MAGIC_WORD

#define CAN_BENCH_HEADER 0x66
#define CAN_BENCH_GET_COUNT 0
#define CAN_BENCH_GET_SET 1
#define CAN_BENCH_GET_CLEAR 2
#define CAN_BENCH_SET_ENGINE_TYPE 3
