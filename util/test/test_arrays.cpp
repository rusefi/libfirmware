#include <rusefi/arrays.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::ElementsAre;

TEST(Util_Arrays, CopyArray) {
	int arr[2];

	// Copy from an initializer list
	copyArray(arr, { 10, 20 });
	ASSERT_THAT(arr, ElementsAre(10, 20));

	// Copy from another array
	int arr2[] = { 30, 40 };
	copyArray(arr, arr2);
	ASSERT_THAT(arr, ElementsAre(30, 40));

	// Copy to a scaled channel
	scaled_channel<int, 10, 1> arr3[2];
	copyArray(arr3, { 100, 200 });
	ASSERT_THAT(arr3, ElementsAre(100, 200));
}

TEST(Util_Arrays, CopyArrayPartial) {
	int arr[4];
	copyArray(arr, { 1, 2, 3, 4 });
	ASSERT_THAT(arr, ElementsAre(1, 2, 3, 4));

	// Copy a smaller array over the beginning of arr
	copyArrayPartial(arr, { 100, 200 });
	ASSERT_THAT(arr, ElementsAre(100, 200, 3, 4));
}

TEST(Util_Arrays, Size) {
	int arr1[2];
	uint8_t arr2[17];
	scaled_channel<uint16_t, 3, 1> arr3[21];

	ASSERT_EQ(2u,  efi::size(arr1));
	ASSERT_EQ(17u, efi::size(arr2));
	ASSERT_EQ(21u, efi::size(arr3));
}

#define ARRAY_INTERPOLATION_ERROR 0.01f

TEST(Util_Arrays, copyArrayInterpolated){
	// direct copy
	{
		float src[] = { 1.0f, 2.0f, 3.0f };
		float dest[3];
		copyArrayInterpolated(dest, src);
		ASSERT_THAT(dest, ElementsAre(1.0f, 2.0f, 3.0f));
	}

	// Test upscaling with interpolation (2 -> 5)
	{
		float src[] = { 0.0f, 10.0f };
		float dest[5];
		copyArrayInterpolated(dest, src);
		ASSERT_NEAR(dest[0], 0.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[1], 2.5f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[2], 5.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[3], 7.5f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[4], 10.0f, ARRAY_INTERPOLATION_ERROR);
	}

	// Test upscaling with interpolation (3 -> 7)
	{
		float src[] = { 0.0f, 6.0f, 12.0f };
		float dest[7];
		copyArrayInterpolated(dest, src);
		ASSERT_NEAR(dest[0], 0.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[1], 2.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[2], 4.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[3], 6.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[4], 8.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[5], 10.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[6], 12.0f, ARRAY_INTERPOLATION_ERROR);
	}

	// Test downscaling (5 -> 3)
	{
		float src[] = { 0.0f, 2.5f, 5.0f, 7.5f, 10.0f };
		float dest[3];
		copyArrayInterpolated(dest, src);
		ASSERT_THAT(dest, ElementsAre(0.0f, 5.0f, 10.0f));
	}

	// Test rounding with default (2 digits)
	{
		float src[] = { 0.0f, 1.0f };
		float dest[3];
		copyArrayInterpolated(dest, src);
		// Middle value should be 0.5, rounded to 2 digits
		EXPECT_FLOAT_EQ(dest[0], 0.0f);
		EXPECT_FLOAT_EQ(dest[1], 0.5f);
		EXPECT_FLOAT_EQ(dest[2], 1.0f);
	}

	// Test rounding with 1 digit
	{
		float src[] = { 0.0f, 1.0f };
		float dest[4];
		copyArrayInterpolated<float, float, 4, 2, 1>(dest, src);
		EXPECT_FLOAT_EQ(dest[0], 0.0f);
		EXPECT_NEAR(dest[1], 0.3f, 0.05f);
		EXPECT_NEAR(dest[2], 0.7f, 0.05f);
		EXPECT_FLOAT_EQ(dest[3], 1.0f);
	}

	// Test with integer types
	{
		int src[] = { 0, 100 };
		int dest[5];
		copyArrayInterpolated(dest, src);
		ASSERT_THAT(dest, ElementsAre(0, 25, 50, 75, 100));
	}

	// Test different src/dest types
	{
		int src[] = { 0, 10, 20 };
		float dest[5];
		copyArrayInterpolated(dest, src);
		ASSERT_NEAR(dest[0], 0.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[1], 5.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[2], 10.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[3], 15.0f, ARRAY_INTERPOLATION_ERROR);
		ASSERT_NEAR(dest[4], 20.0f, ARRAY_INTERPOLATION_ERROR);
	}
}