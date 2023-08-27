/*
 * FragmentEntry.h
 *
 *  Created on: Jan 5, 2022
 * @author Andrey Belomutskiy, (c) 2012-2022
 */

#pragma once

#include <cstddef>
#include <cstdint>

// Implement overloads of this function in your project for each live data
// struct you want to fetch
// for example:
// struct myData { };
//
// template<>
// const myData* getLiveDataStruct(size_t index) { return ...; }
template <typename TStruct>
const TStruct* getLiveData(size_t index);

template <typename TValue, int TIndex = 0>
struct decl_frag { };

struct FragmentEntry {
	template <typename TData, int TIndex>
	FragmentEntry(decl_frag<TData, TIndex>)
		: func((const uint8_t*(*)(size_t))getLiveData<TData>)
		, index(TIndex)
		, size(sizeof(TData))
	{
	}

	const uint8_t* get() const {
		return func(index);
	}

	const uint8_t *(*const func)(size_t);
	const size_t index;

	const size_t size;
};

struct FragmentList {
	const FragmentEntry* fragments;
	const size_t count;
};

// copy `size` of fragmented outputs in to destination, skipping the first `skip` bytes
size_t copyRange(uint8_t* destination, FragmentList src, size_t skip, size_t size);
// returns pointer to actual data and size of contiguous data
// if data is located in more than one fragmnet - returned value will be size available in first fragment
size_t getRangePtr(uint8_t **ptr, FragmentList src, size_t offset, size_t size);
