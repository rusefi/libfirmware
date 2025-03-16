#pragma once

// http://en.wikipedia.org/wiki/Endianness

#ifndef __BYTE_ORDER__
	#error __BYTE_ORDER__ is not defined
#endif

#if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
	#define bigEndianHost true
#endif
#if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	#define bigEndianHost false
#endif

/* TODO: already defined in efilib.h
 * TODO: move here? */
#if 0
static inline uint16_t SWAP_UINT16(uint16_t x)
{
	return ((x << 8) | (x >> 8));
}

static inline uint32_t SWAP_UINT32(uint32_t x)
{
	return (((x >> 24) & 0x000000ff) | ((x <<  8) & 0x00ff0000) |
			((x >>  8) & 0x0000ff00) | ((x << 24) & 0xff000000));
}
#endif

template <typename T>
class SwapEndian
{
	public:
		struct IncompleteType;
		SwapEndian() { }

		constexpr operator typename std::conditional_t<sizeof(T) == 4, T, IncompleteType>() const {
			return SWAP_UINT32(rep);
		}

		constexpr SwapEndian(std::conditional_t<sizeof(T) == 4, T, IncompleteType> val) {
			rep = SWAP_UINT32(val);
		}

		constexpr operator typename std::conditional_t<sizeof(T) == 2, T, IncompleteType>() const {
			return SWAP_UINT16(rep);
		}

		constexpr SwapEndian(std::conditional_t<sizeof(T) == 2, T, IncompleteType> val) {
			rep = SWAP_UINT16(val);
		}
	private:
		T rep;
} __attribute__ ((packed));

#if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
// Big endian storage types
using beint16_t = SwapEndian<int16_t>;
using beint32_t = SwapEndian<int32_t>;
using beuint16_t = SwapEndian<uint16_t>;
using beuint32_t = SwapEndian<uint32_t>;

// Natine Little endian storage types
using leint16_t = int16_t;
using leint32_t = int32_t;
using leuint16_t = uint16_t;
using leuint32_t = uint32_t;
#endif

#if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
// Native Big endian storage types
using beint16_t = int16_t;
using beint32_t = int32_t;
using beuint16_t = uint16_t;
using beuint32_t = uint32_t;

// Little endian storage types
using leint16_t = SwapEndian<int16_t>;
using leint32_t = SwapEndian<int32_t>;
using leuint16_t = SwapEndian<uint16_t>;
using leuint32_t = SwapEndian<uint32_t>;
#endif

//static_assert(sizeof(buint8_t) == 1);
static_assert(sizeof(beint16_t) == 2);
static_assert(sizeof(beint32_t) == 4);
static_assert(sizeof(beuint16_t) == 2);
static_assert(sizeof(beuint32_t) == 4);

//static_assert(sizeof(luint8_t) == 1);
static_assert(sizeof(leint16_t) == 2);
static_assert(sizeof(leint32_t) == 4);
static_assert(sizeof(leuint16_t) == 2);
static_assert(sizeof(leuint32_t) == 4);
