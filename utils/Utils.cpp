/*
 * Utils.cpp
 *
 *  Created on: May 26, 2013
 *      Author: rudhir
 */

#include "Utils.h"
#include <cmath>

Utils::Utils() {
}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}


bool Utils::isLess(double a, double b) {
	if(isEqual(a, b))
		return false;

	return (a < b);
}

bool Utils::isGreater(double a, double b) {
	if(isEqual(a, b))
		return false;

	return (a > b);
}

bool Utils::isEqual(double a, double b) {
	return (fabs(a-b) < EPSILON);
}
