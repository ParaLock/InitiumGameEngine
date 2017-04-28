#pragma once
#include <math.h>

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
	return max(lower, min(n, upper));
}

static int getRandomNumber() {
	int random_integer = rand() % 100;

	return random_integer;
}
