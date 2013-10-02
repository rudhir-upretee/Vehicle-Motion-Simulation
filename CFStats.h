/*
 * CFStats.h
 *
 *  Created on: Oct 2, 2013
 *      Author: rudhir
 */

#ifndef CFSTATS_H_
#define CFSTATS_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <Vehicle.h>

using namespace std;

class CFStats {
public:
	CFStats();
	virtual ~CFStats();
	void openLogFiles();
	void closeLogFiles();
	void logDistTime(ostringstream& paramsLogStr);
	void logVelTime(ostringstream& paramsLogStr);
	void logRangeErrTime(ostringstream& paramsLogStr);
	void logParams(ostringstream& paramsLogStr);
	void logRangeError(double time, std::vector<Vehicle> vehList, int interval);
	void logCarVelocity(double time, std::vector<Vehicle> vehList, int interval);

private:
	ofstream distTimeLog;
	ofstream velTimeLog;
	ofstream rangeErrTimeLog;
	ofstream paramsLog;
};

#endif /* CFSTATS_H_ */
