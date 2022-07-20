#include <gtest/gtest.h>

#include <rusefi/crc.h>

TEST(Util_CRC, crc8) {
	const uint8_t crc8_tab[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};

	ASSERT_EQ(0xB, crc8(crc8_tab, 8));
}

TEST(Util_CRC, crc) {
	const char * A = "A";

	uint32_t c = crc32(A, 1);
	printf("crc32(A)=%x\r\n", c);
	EXPECT_EQ(0xd3d99e8b, c);

	const char * line = "AbcDEFGF";
	c = crc32(line, 8);
	printf("crc32(line)=%x\r\n", c);
	EXPECT_EQ(0x4775a7b1, c);

	c = crc32(line, 1);
	c = crc32inc(line + 1, c, 8 - 1);
	EXPECT_EQ(0x4775a7b1, c);
}
