#pragma once
#include <math.h>

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
	return max(lower, min(n, upper));
}