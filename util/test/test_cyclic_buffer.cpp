#include <gtest/gtest.h>

#include "cyclic_buffer.h"
#include "rusefi/true_false.h"

TEST(util, cyclicBufferContains) {
	cyclic_buffer<int> sb;
	sb.add(10);
	ASSERT_EQ(TRUE, sb.contains(10));
	ASSERT_EQ(FALSE, sb.contains(11));
}

TEST(util, cyclicBuffer) {
	cyclic_buffer<int> sb;

	{
		sb.add(10);

		ASSERT_EQ(10, sb.sum(3));

		sb.add(2);
		ASSERT_EQ(12, sb.sum(2));
	}
	{
		sb.clear();

		sb.add(1);
		sb.add(2);
		sb.add(3);
		sb.add(4);

		ASSERT_EQ(4, sb.maxValue(3));
		ASSERT_EQ(4, sb.maxValue(113));
		ASSERT_EQ( 2,  sb.minValue(3)) << "minValue(3)";
		ASSERT_EQ(1, sb.minValue(113));
	}
}
