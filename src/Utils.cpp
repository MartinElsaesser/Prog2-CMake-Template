#pragma once
#include "Utils.h"
#include <stdlib.h>
#include <algorithm>

int randomNum(int lower, int upper) {
	// generates a random number within range [lower,upper]
	return (rand() % (upper - lower + 1)) + lower;
}

int limit(int minimum, int maximum, int number) {
	// makes sure number is within minimum and maximum
	// e.g. minimum=2 maximum=5 number=3    return 3
	// e.g. minimum=2 maximum=5 number=-3   return 2
	// e.g. minimum=2 maximum=5 number=8    return 5
	// if number is bigger than maximum, maximum is returned 
	// if number is smaller than minimum, minimum is returned
	// otherwise number is returned
	return std::min(std::max(number, minimum), maximum);
}
