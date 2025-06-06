/**
 * @file interpolation.h
 */

#pragma once

#include <cstdint>

#include "scaled_channel.h"

namespace priv {
struct BinResult
{
	size_t Idx;
	float Frac;
};

/**
 * @brief Finds the location of a value in the bin array.
 *
 * @param value The value to find in the bins.
 * @return A result containing the index to the left of the value,
 * and how far from (idx) to (idx + 1) the value is located.
 */
template<class TBin, int TSize>
BinResult getBin(float value, const TBin (&bins)[TSize]) {
	// Enforce numeric only (int, float, uintx_t, etc)
	static_assert(std::is_arithmetic_v<TBin>, "Table bins must be an arithmetic type");

	// Enforce that there are enough bins to make sense (what does one bin even mean?)
	static_assert(TSize >= 2);

	// Handle NaN
	if (std::isnan(value)) {
		return { 0, 0.0f };
	}

	// Handle off-scale low
	if (value <= bins[0]) {
		return { 0, 0.0f };
	}

	// Handle off-scale high
	if (value >= bins[TSize - 1]) {
		return { TSize - 2, 1.0f };
	}

	size_t idx = 0;

	// Find the last index less than the searched value
	// Linear search for now, maybe binary search in future
	// after collecting real perf data
	for (idx = 0; idx < TSize - 1; idx++) {
		if (bins[idx + 1] > value) {
			break;
		}
	}

	float low = bins[idx];
	float high = bins[idx + 1];

	// Compute how far along the bin we are
	// (0.0f = left side, 1.0f = right side)
	float fraction = (value - low) / (high - low);

	return { idx, fraction };
}

/**
 * @brief Finds the location of a closest value in the bin array.
 *
 * @param value The value to find in the bins.
 * @return A result containing the index of the closest to bin value,
 * and how far from (idx) to (idx + 1) or (idx - 1) the value is located.
 * If value is outside of bin - {0, <-1.0} or {Tsize - 1, >+1.0} is returned
 */
template<class TBin, int TSize>
struct BinResult getClosestBin(float value, const TBin (&bins)[TSize]) {
	// Enforce numeric only (int, float, uintx_t, etc)
	static_assert(std::is_arithmetic_v<TBin>, "Table bins must be an arithmetic type");

	// Enforce that there are enough bins to make sense (what does one bin even mean?)
	static_assert(TSize >= 2);

	// Handle NaN
	if (std::isnan(value)) {
		return { 0, -1.0f };
	}

	const size_t lastIdx = TSize - 1;
	size_t idx = 0;
	float closest;
	float step;

	if (value <= bins[0]) {
		// Handle off-scale low
		// virtual bins[-1] located at the same distance to the left from bins[0], as bins[1] from bins[0]
		step = bins[1] - bins[0];
		idx = 0;
	} else if (value >= bins[lastIdx]) {
		// Handle off-scale high
		// virtual bins[lastIdx + 1] located at the same distance to the right from bins[lastIdx], as bins[lastIdx - 1] from bins[lastIdx]
		step = bins[lastIdx] - bins[lastIdx - 1];
		idx = lastIdx;
	} else {
		// Find the closest bin. 50/50 divide distance between bins
		// Linear search for now, maybe binary search in future
		// after collecting real perf data
		for (idx = 0; idx < lastIdx - 1; idx++) {
			// ( -0.5, 05 ]
			// if (bins[idx] + bins[idx + 1] / 2 >= value) {
			if (bins[idx] + bins[idx + 1] >= 2 * value) {
				break;
			}
		}

		step = bins[idx + 1] - bins[idx];
	}

	if (step <= 0) {
		// bins are not ascending or two bins are equal
		return { idx, 1.0f };
	}

	closest = bins[idx];

	// Compute how far from the closest bin we are:
	// 0.0f = rigft in the bin
	// -0.5f = half way to previous bin, 0.5f = half way to next bin
	// <= -1.0f = to far below zero bin
	// >=  1.0f = to far above last bin
	float distance = (value - closest) / step;

	return { idx, distance };
}

template<class TBin, int TSize, int TMult, int TDiv>
BinResult getBin(float value, const scaled_channel<TBin, TMult, TDiv> (&bins)[TSize]) {
	return getBin(value * (float(TMult) / TDiv), *reinterpret_cast<const TBin (*)[TSize]>(&bins));
}

static inline float linterp(float low, float high, float frac)
{
	return high * frac + low * (1 - frac);
}
} // namespace priv

template <class TBin, class TValue, int TSize>
float interpolate2d(const float value, const TBin (&bin)[TSize], const TValue (&values)[TSize]) {
	// Enforce numeric only (int, float, uintx_t, etc)
	static_assert(std::is_arithmetic_v<TBin> || is_scaled_channel<TBin>, "Table values must be an arithmetic type or scaled channel");

	auto b = priv::getBin(value, bin);

	// Convert to float as we read it out
	float low = static_cast<float>(values[b.Idx]);
	float high = static_cast<float>(values[b.Idx + 1]);
	float frac = b.Frac;

	return priv::linterp(low, high, frac);
}

// TS defines tables as [y_row_count x x_column_count] and we follow that weird Y, X order of arguments here
// todo: add support for scaled_channel to match Map3D flexibility?
template<typename VType, unsigned RNum, typename RType, unsigned X_ColumnNum, typename X_CType>
float interpolate3d(const VType (&table)[RNum][X_ColumnNum],
                    const RType (&rowBins)[RNum], float yRowValue,
                    const X_CType (&colBins)[X_ColumnNum], float xColValue)
{
    auto row = priv::getBin(yRowValue, rowBins);
    auto col = priv::getBin(xColValue, colBins);

    // Orient the table such that (0, 0) is the bottom left corner,
    // then the following variable names will make sense
    float lowerLeft  = table[row.Idx    ][col.Idx    ];
    float upperLeft  = table[row.Idx + 1][col.Idx    ];
    float lowerRight = table[row.Idx    ][col.Idx + 1];
    float upperRight = table[row.Idx + 1][col.Idx + 1];

    // Interpolate each side by itself
    float left  = priv::linterp(lowerLeft, upperLeft, row.Frac);
    float right = priv::linterp(lowerRight, upperRight, row.Frac);

    // Then interpolate between those
    return priv::linterp(left, right, col.Frac);
}
