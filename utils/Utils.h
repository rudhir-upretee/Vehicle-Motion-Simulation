/*
 * Utils.h
 *
 *  Created on: May 26, 2013
 *      Author: rudhir
 */

#ifndef UTILS_H_
#define UTILS_H_

class Utils {
public:
	Utils();
	virtual ~Utils();

	static bool isLess(double a, double b);
	static bool isGreater(double a, double b);
	static bool isEqual(double a, double b);

private:
	static double const EPSILON = 0.001;
};

#endif /* UTILS_H_ */
