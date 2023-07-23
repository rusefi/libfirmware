// We have a bit of a mess with too many useful usages of CAN and too little documentation at https://github.com/rusefi/rusefi/wiki/CAN

// we use ExtID but only 16 bits in comms protocol from ECU to GDI4
#define GDI4_BASE_ADDRESS 0xBB20

#define BENCH_TEST_BASE_ADDRESS 0x770000

#define BENCH_TEST_EVENT_COUNTERS BENCH_TEST_BASE_ADDRESS
#define BENCH_TEST_RAW_ANALOG (BENCH_TEST_BASE_ADDRESS + 1)
