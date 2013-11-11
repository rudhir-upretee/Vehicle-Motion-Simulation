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
	CFStats(int model,
			int vehCnt,
			double simTime,
			int connPat,
			int patCnt,
			int statCnt,
			double reactTime,
			double tauTime,
			double updateTime,
			double nwDeltaTime,
			double initHdwayTime,
			double adjHdwayTime,
			double perturbStartTime,
			double minGap);
	virtual ~CFStats();
	void openLogFiles();
	void closeLogFiles();
	void logDistTime(ostringstream& paramsLogStr);
	void logVelTime(ostringstream& paramsLogStr);
	void logRangeErrTime(ostringstream& paramsLogStr);
	void logParams(ostringstream& paramsLogStr);
	void logRangeError(double time, std::vector<Vehicle> vehList);
	void logCarVelocity(double time, std::vector<Vehicle> vehList);
	void initStatVectors();
	void plotStats();
	void plotMetrics();
	void setMinGap(double minGap);

private:
	int m_model;
	int m_vehCnt;
	double m_simTime;
	int m_connPat;
	int m_patCnt;
	int m_statCnt;
	double m_reactTime;
	double m_tauTime;
	double m_updateTime;
	double m_nwDeltaTime;
	double m_initHdwayTime;
	double m_adjHdwayTime;
	double m_perturbStartTime;
	double m_minGap;

	ofstream distTimeLog;
	ofstream velTimeLog;
	ofstream rangeErrTimeLog;
	ofstream paramsLog;

	std::vector<double> m_maxRangeErr;
	std::vector<double> m_minInterVehGap;
	std::vector<double> m_minTimeToCol;

};

#endif /* CFSTATS_H_ */
