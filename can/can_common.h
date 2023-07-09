// We have a bit of a mess with too many useful usages of CAN and too little documentation at https://github.com/rusefi/rusefi/wiki/CAN

// we use ExtID but only 16 bits in comms protocol from ECU to GDI4
#define GDI4_BASE_ADDRESS 0xBB20
