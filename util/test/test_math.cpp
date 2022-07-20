#include <rusefi/math.h>

#include <gtest/gtest.h>
#include <math.h>

TEST(Util_Math, ExpTaylor)
{
    // test from -2 < x < 0
    for(float x = -2; x < 0; x += 0.05)
    {
        // Compare taylor to libc implementation
        EXPECT_NEAR(expf_taylor(x), expf(x), 0.01f);
    }
}

TEST(Util_Math, clampf) {
	// off scale low
	EXPECT_EQ(clampF(10, 5, 20), 10);
	EXPECT_EQ(clampF(-10, -50, 10), -10);

	// in range (unclamped)
	EXPECT_EQ(clampF(10, 15, 20), 15);
	EXPECT_EQ(clampF(-10, -5, 10), -5);

	// off scale high
	EXPECT_EQ(clampF(10, 25, 20), 20);
	EXPECT_EQ(clampF(-10, 50, 10), 10);
}

TEST(Util_Math, tanf_taylor) {
	// Function is only specified from [0, pi/2) ish, so test that range
	for (float i = 0; i < 1.5; i += 0.1f)
	{
		// Compare to libc implementation
		EXPECT_NEAR(tanf_taylor(i), tanf(i), 0.05f) << "I = " << i;
	}
}
