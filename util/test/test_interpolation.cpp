#include "gtest/gtest.h"

#include <rusefi/arrays.h>
#include <rusefi/interpolation.h>

TEST(Util_Interpolation, testInterpolate2d) {
	float bins4[] = { 1, 2, 3, 4 };
	float values4[] = { 1, 20, 30, 400 };

	int result;

	// Left size
	result = interpolate2d(0, bins4, values4);
	ASSERT_EQ(1, result);

	// Right size
	result = interpolate2d(10, bins4, values4);
	ASSERT_EQ(400, result);

	// Middle
	result = interpolate2d(3, bins4, values4);
	ASSERT_EQ(30, result);

	// Middle
	result = interpolate2d(3.5, bins4, values4);
	ASSERT_EQ(215, result);
}


class TestTable2dSmall : public ::testing::Test
{
protected:
	float bins[2];
	float values[2];

	void SetUp() override
	{
		// This test maps [20,30] -> [100,200]
		copyArray(bins, { 20.0f, 30.0f });
		copyArray(values, { 100.0f, 200.0f });
	}
};

TEST_F(TestTable2dSmall, OffScaleLow)
{
    EXPECT_FLOAT_EQ(interpolate2d(10, bins, values), 100);
}

TEST_F(TestTable2dSmall, OffScaleHigh)
{
    EXPECT_FLOAT_EQ(interpolate2d(40, bins, values), 200);
}

TEST_F(TestTable2dSmall, EdgeLeft)
{
    EXPECT_FLOAT_EQ(interpolate2d(20, bins, values), 100);
}

TEST_F(TestTable2dSmall, EdgeRight)
{
    EXPECT_FLOAT_EQ(interpolate2d(30, bins, values), 200);
}

TEST_F(TestTable2dSmall, Middle)
{
    EXPECT_FLOAT_EQ(interpolate2d(25, bins, values), 150);
}

TEST_F(TestTable2dSmall, NanInput)
{
    EXPECT_FLOAT_EQ(interpolate2d(NAN, bins, values), 100);
}

class Test2dTableMassive : public ::testing::Test
{
	static constexpr int Count = 2500;

protected:
	float bins[Count];
	float values[Count];

	void SetUp() override
	{
		float x = 0;

		for (size_t i = 0; i < std::size(bins); i++)
		{
			x += 0.1f;
			bins[i] = x;
			values[i] = x * x;
		}
	}
};

TEST_F(Test2dTableMassive, t)
{
    float x = 0;
    float maxErr = -1;

    for (size_t i = 0; i < 25000; i++)
    {
        x += 0.01f;

        float actual = x * x;
        float lookup = interpolate2d(x, bins, values);

        float err = std::abs(actual - lookup);

        if (err > maxErr)
        {
            maxErr = err;
        }
    }

    EXPECT_LT(maxErr, 0.01);
}

// Helper for BinResult type
#define EXPECT_BINRESULT(actual, expectedIdx, expectedFrac) \
	{ \
		auto ___temp___ = actual; \
		EXPECT_EQ(___temp___.Idx, expectedIdx); \
		EXPECT_NEAR(___temp___.Frac, expectedFrac, abs(expectedFrac / 1e4)); \
	}

// Test with small bins: only two values
static const float smallBins[] = { 10, 20 };

TEST(Util_Interpolation, GetBinSmallOffScaleLeft)
{
    EXPECT_BINRESULT(priv::getBin(5, smallBins), 0u, 0);
}

TEST(Util_Interpolation, GetBinSmallOffScaleRight)
{
    EXPECT_BINRESULT(priv::getBin(25, smallBins), 0u, 1);
}

TEST(Util_Interpolation, GetBinSmallEdgeLeft)
{
    EXPECT_BINRESULT(priv::getBin(10, smallBins), 0u, 0);
}

TEST(Util_Interpolation, GetBinSmallEdgeRight)
{
    EXPECT_BINRESULT(priv::getBin(10, smallBins), 0u, 0);
}

TEST(Util_Interpolation, GetBinSmallMiddle)
{
    EXPECT_BINRESULT(priv::getBin(15, smallBins), 0u, 0.5f);
}

TEST(Util_Interpolation, GetBinSmallNanInput)
{
	EXPECT_BINRESULT(priv::getBin(NAN, smallBins), 0u, 0);
}

// Test with medium bins, 3 items
static const float bigBins[] = { 10, 20, 30 };

TEST(Util_Interpolation, GetBinBigOffScaleLow)
{
    EXPECT_BINRESULT(priv::getBin(5, bigBins), 0u, 0);
}

TEST(Util_Interpolation, GetBinBigOffScaleHigh)
{
    EXPECT_BINRESULT(priv::getBin(35, bigBins), 1u, 1.0f);
}


TEST(Util_Interpolation, GetBinBigNearMiddleLow)
{
    EXPECT_BINRESULT(priv::getBin(19.99f, bigBins), 0u, 0.999f);
}

TEST(Util_Interpolation, GetBinBigNearMiddleExact)
{
    EXPECT_BINRESULT(priv::getBin(20.0f, bigBins), 1u, 0);
}

TEST(Util_Interpolation, GetBinBigNearMiddleHigh)
{
    EXPECT_BINRESULT(priv::getBin(20.01f, bigBins), 1u, 0.001f);
}

TEST(Util_Interpolation, GetBinBigLeftMiddle)
{
    EXPECT_BINRESULT(priv::getBin(15.0f, bigBins), 0u, 0.5f);
}

TEST(Util_Interpolation, GetBinBigRightMiddle)
{
    EXPECT_BINRESULT(priv::getBin(25.0f, bigBins), 1u, 0.5f);
}

// Test getClosestBin
static const float rpmBins[14] = {800, 1300, 1800, 2200, 2700, 3200, 3700, 4100, 4600, 5100, 5600, 6000, 6500, 7000};

TEST(Util_Interpolation, GetClosestBin)
{
	// Outside bins
    EXPECT_BINRESULT(priv::getClosestBin(0, rpmBins), 0u, -1.6f);
    EXPECT_BINRESULT(priv::getClosestBin(10000, rpmBins), 13u, 6.0f);

    // first and last
    EXPECT_BINRESULT(priv::getClosestBin(800, rpmBins), 0u, 0.0f);
    EXPECT_BINRESULT(priv::getClosestBin(7000, rpmBins), 13u, 0.0f);

    // middle
    EXPECT_BINRESULT(priv::getClosestBin(1050, rpmBins), 0u, 0.5f);
    EXPECT_BINRESULT(priv::getClosestBin(1550, rpmBins), 1u, 0.5f);

    // on edge
    EXPECT_BINRESULT(priv::getClosestBin(300, rpmBins), 0u, -1.0f);
    EXPECT_BINRESULT(priv::getClosestBin(7500, rpmBins), 13u, 1.0f);
}
