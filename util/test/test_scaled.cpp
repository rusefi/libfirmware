#include <rusefi/scaled_channel.h>

#include <gtest/gtest.h>
#include <math.h>

TEST(Util_Scaled, float_equals) {

	float f1 = 3;
	float f2 = 3;
	EXPECT_TRUE(f1 == f2);

	scaled_channel<float, 1, 1> s1 = 3;
	EXPECT_TRUE(f1 == s1);

	scaled_channel<float, 1, 1> s3 = 3.1;
	EXPECT_FALSE(f1 == s3);
}
