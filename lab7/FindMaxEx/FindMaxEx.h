#pragma once

#include <functional>
#include <iterator>
#include <utility>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	const T* max = &arr[0];
	for (const T& item : arr)
	{
		if (less(*max, item))
		{
			max = &item;
		}
	}
	maxValue = *max;
	
	return true;
}
