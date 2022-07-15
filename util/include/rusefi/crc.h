#pragma once

#include <cstdint>

uint8_t crc8(const uint8_t * buf, uint8_t len);
uint32_t crc32(const void *buf, uint32_t size);
uint32_t crc32inc(const void *buf, uint32_t crc, uint32_t size);
