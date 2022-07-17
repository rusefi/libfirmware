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

	ASSERT_EQ(2,  efi::size(arr1));
	ASSERT_EQ(17, efi::size(arr2));
	ASSERT_EQ(21, efi::size(arr3));
}
