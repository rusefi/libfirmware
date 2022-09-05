/**
 * @file scaled_channel.h
 */

#pragma once

#include <cmath>
#include <cstdint>
#include <type_traits>

struct scaled_channel_base { };

template <typename TTest>
static constexpr bool is_scaled_channel = std::is_base_of_v<scaled_channel_base, TTest>;

// This class lets us transparently store something at a ratio inside an integer type
// Just use it like a float - you can read and write to it, like this:
// scaled_channel<uint8_t, 10> myVar;
// myVar = 2.4f;	// converts to an int, stores 24
// float x = myVar; // converts back to float, returns 2.4f
template <typename T, int mul = 1, int div = 1>
class scaled_channel : scaled_channel_base {
	using TSelf = scaled_channel<T, mul, div>;

public:
	struct IncompleteType;

	constexpr scaled_channel() : m_value(static_cast<T>(0)) { }

	// Only allow conversion directly to T when mul/div are both 1, otherwise this constructor doesn't exist and the float conversion is used.
	constexpr scaled_channel(std::conditional_t<mul == 1 && div == 1, T, IncompleteType> val) {
		m_value = val;
	}

	// Scale the float in to our scaled channel
	constexpr scaled_channel(std::conditional_t<mul != 1 || div != 1, float, IncompleteType> val) {
		// If there are scale factors, it must NOT be a float. Why would you scale a float?
		static_assert(std::is_integral_v<T>);

		m_value = std::roundf(val * float(mul) / div);
	}

	// Only allow conversion directly to T when mul/div are both 1, otherwise this operator doesn't exist and the float conversion is used.
	constexpr operator typename std::conditional_t<mul == 1 && div == 1, T, IncompleteType>() const {
		return m_value;
	}

	// Allow reading back out as a float (note: this may be lossy!)
	constexpr operator typename std::conditional_t<mul != 1 || div != 1, float, IncompleteType>() const {
		return m_value * (float(div) / mul);
	}

	// Postfix increment operator
	// only enable if:
	//  - base type T is an integral type (integer)
	//  - multiplier is equal to 1
	void operator++(int) {
		static_assert(mul == 1 && div == 1,
			      "Increment operator only supported for non-scaled integer types");
		static_assert(std::is_integral_v<T>, "Increment operator only supported for non-scaled integer types");

		m_value++;
	}

	constexpr const char* getFirstByteAddr() const {
		return &m_firstByte;
	}

private:
	union {
		T m_value;
		char m_firstByte;
	};
};

// We need to guarantee that scaled values containing some type are the same size
// as that underlying type.  We rely on the class only having a single member for
// this trick to work.
static_assert(sizeof(scaled_channel<uint8_t>) == 1);
static_assert(sizeof(scaled_channel<uint16_t>) == 2);
static_assert(sizeof(scaled_channel<uint32_t>) == 4);
static_assert(sizeof(scaled_channel<float>) == 4);

// make sure the scaled channel detector works
static_assert(!is_scaled_channel<int>);
static_assert(is_scaled_channel<scaled_channel<int, 5>>);
