/*
 * CFStats.cpp
 *
 *  Created on: Oct 2, 2013
 *      Author: rudhir
 */

#include "CFStats.h"

CFStats::CFStats()
	{
	openLogFiles();
	}

CFStats::~CFStats()
	{
	closeLogFiles();
	}

void CFStats::openLogFiles()
	{
	if(!paramsLog.is_open())
		{
		paramsLog.open("params.log");
		}
	if(!distTimeLog.is_open())
		{
		distTimeLog.open("distTime.log");
		}
	if(!rangeErrTimeLog.is_open())
		{
		rangeErrTimeLog.open("rangeErrTime.log");
		}
	if(!velTimeLog.is_open())
		{
		velTimeLog.open("velTime.log");
		}
	}

void CFStats::closeLogFiles()
	{
	if(paramsLog.is_open())
		{
		paramsLog.close();
		}
	if(distTimeLog.is_open())
		{
		distTimeLog.close();
		}
	if(rangeErrTimeLog.is_open())
		{
		rangeErrTimeLog.close();
		}
	if(velTimeLog.is_open())
		{
		velTimeLog.close();
		}
	}

void CFStats::logDistTime(ostringstream& logStr)
	{
	distTimeLog << logStr.str();
	}

void CFStats::logVelTime(ostringstream& logStr)
	{
	velTimeLog << logStr.str();
	}

void CFStats::logRangeErrTime(ostringstream& logStr)
	{
	rangeErrTimeLog << logStr.str();
	}

void CFStats::logParams(ostringstream& logStr)
	{
	paramsLog << logStr.str();
	}

void CFStats::logRangeError(double time, std::vector<Vehicle> vehList, int interval)
	{
	for(unsigned int i = 0; i+1 < vehList.size(); i+=interval)
		{
		//
		// Log Inter car gap
		distTimeLog << time << ":"
				    << vehList.at(i).getPosX() - vehList.at(i+1).getPosX()
				    << std::endl;

		//
		// Log range error
		double actualGap =
				vehList.at(i).getPosX() - vehList.at(i+1).getPosX();
		double desiredGap =
				vehList.at(i+1).getHdwayTime() * vehList.at(i+1).getVel();

		double rangeErr = actualGap - desiredGap;
		rangeErrTimeLog << time << ":"
						<< rangeErr
						<< std::endl;
		}
	}

void CFStats::logCarVelocity(double time, std::vector<Vehicle> vehList, int interval)
	{
	for(unsigned int i = 0; i < vehList.size(); i+=interval)
		{
		velTimeLog << time << ":"
				   << vehList.at(i).getVel() << ":"
				   << vehList.at(i).getPosX()  << ":"
				   << vehList.at(i).getAcclr()
				   << std::endl;
		}
	}


