#pragma once
#include <math.h>

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
	return max(lower, min(n, upper));
}

static int getRandomNumber() {
	srand((unsigned)time(0));
	int random_integer = rand();

	return random_integer;
}
