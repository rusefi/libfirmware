#include <gtest/gtest.h>
#include <rusefi/rusefi_time_types.h>
#include <rusefi/rusefi_time_wraparound.h>

TEST(util, WrapAround62) {
	// Random test
	{
		WrapAround62 t;
		uint32_t source = 0;
		uint64_t actual = 0;

		// Test random progression, positive and negative.
		uint32_t seed = time(NULL);
		printf("Testing with seed 0x%08x\n", seed);
		srand(seed);
		for (unsigned i = 0; i < 10000; i++) {
			int32_t delta = rand();
			if (delta < 0) {
				delta = ~delta;
			}
			delta -= RAND_MAX >> 1;

			// Cap negative test
			if (delta < 0 && -delta > actual) {
				delta = -actual;
			}

			source += delta;
			actual += delta;

			uint64_t next = t.update(source);
			EXPECT_EQ(actual, next);
		}
	}

	// More pointed test for expected edge conditions
	{
		WrapAround62 t;

		EXPECT_EQ(t.update(0x03453455), 0x003453455LL);
		EXPECT_EQ(t.update(0x42342323), 0x042342323LL);
		EXPECT_EQ(t.update(0x84356345), 0x084356345LL);
		EXPECT_EQ(t.update(0x42342323), 0x042342323LL);
		EXPECT_EQ(t.update(0x84356345), 0x084356345LL);
		EXPECT_EQ(t.update(0xC5656565), 0x0C5656565LL);
		EXPECT_EQ(t.update(0x01122112), 0x101122112LL); // Wrap around!
		EXPECT_EQ(t.update(0xC5656565), 0x0C5656565LL);
		EXPECT_EQ(t.update(0x84356345), 0x084356345LL);
		EXPECT_EQ(t.update(0xC5656565), 0x0C5656565LL);
		EXPECT_EQ(t.update(0x01122112), 0x101122112LL); // Wrap around!
		EXPECT_EQ(t.update(0x42342323), 0x142342323LL);
		EXPECT_EQ(t.update(0x84356345), 0x184356345LL);
		EXPECT_EQ(t.update(0x42342323), 0x142342323LL);
		EXPECT_EQ(t.update(0x84356345), 0x184356345LL);
		EXPECT_EQ(t.update(0xC5656565), 0x1C5656565LL);
		EXPECT_EQ(t.update(0x01122112), 0x201122112LL); // Wrap around!
		EXPECT_EQ(t.update(0xC5656565), 0x1C5656565LL);
		EXPECT_EQ(t.update(0x84356345), 0x184356345LL);
		EXPECT_EQ(t.update(0xC5656565), 0x1C5656565LL);
		EXPECT_EQ(t.update(0x01122112), 0x201122112LL); // Wrap around!
		EXPECT_EQ(t.update(0xC5656565), 0x1C5656565LL);
		EXPECT_EQ(t.update(0x84356345), 0x184356345LL);
		EXPECT_EQ(t.update(0x42342323), 0x142342323LL);
		EXPECT_EQ(t.update(0x01122112), 0x101122112LL);
		EXPECT_EQ(t.update(0x84356345), 0x084356345LL);
		EXPECT_EQ(t.update(0x42342323), 0x042342323LL);
		EXPECT_EQ(t.update(0x03453455), 0x003453455LL);
	}
}
