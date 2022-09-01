/**
 * @file interpolation.h
 */

#pragma once

#include <cstdint>

#include "isnan.h"
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
	if (cisnan(value)) {
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

template<typename VType, unsigned RNum, typename RType, unsigned CNum, typename CType>
float interpolate3d(const VType (&table)[RNum][CNum],
                    const RType (&rowBins)[RNum], float rowValue,
                    const CType (&colBins)[CNum], float colValue)
{
    auto row = priv::getBin(rowValue, rowBins);
    auto col = priv::getBin(colValue, colBins);

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
