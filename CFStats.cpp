/*
 * CFStats.cpp
 *
 *  Created on: Oct 2, 2013
 *      Author: rudhir
 */

#include <cstring>
#include <cstdlib>
#include <cmath>
#include "Utils.h"
#include "CFStats.h"

CFStats::CFStats(int model,
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
		double minGap)
	{
	m_model = model;
	m_vehCnt = vehCnt;
	m_simTime = simTime;
	m_connPat = connPat;
	m_patCnt = patCnt;
	m_statCnt = statCnt;
	m_reactTime = reactTime;
	m_tauTime = tauTime;
	m_updateTime = updateTime;
	m_nwDeltaTime = nwDeltaTime;
	m_initHdwayTime = initHdwayTime;
	m_adjHdwayTime = adjHdwayTime;
	m_perturbStartTime = perturbStartTime;
	m_minGap = minGap;

	openLogFiles();
	initStatVectors();
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
	// Adding 'endl' will flush the line to the file
	distTimeLog << logStr.str() << std::endl;
	}

void CFStats::logVelTime(ostringstream& logStr)
	{
	// Adding 'endl' will flush the line to the file
	velTimeLog << logStr.str() << std::endl;
	}

void CFStats::logRangeErrTime(ostringstream& logStr)
	{
	// Adding 'endl' will flush the line to the file
	rangeErrTimeLog << logStr.str() << std::endl;
	}

void CFStats::logParams(ostringstream& logStr)
	{
	// Adding 'endl' will flush the line to the file
	paramsLog << logStr.str() << std::endl;
	}

void CFStats::logRangeError(double time, std::vector<Vehicle> vehList)
	{
	for(unsigned int vehId = 0, i = 0;
				vehId+1 < vehList.size();
				vehId+=m_statCnt, i++)
		{
		//
		// Log Inter car gap
		double actualGap =
				vehList.at(vehId).getPosX() - vehList.at(vehId+1).getPosX();
		distTimeLog << time << ":"
				    << actualGap
				    << std::endl;

		//
		// Find range error
		double desiredGap =
			vehList.at(vehId+1).getHdwayTime() * vehList.at(vehId+1).getVel();

		//
		// Find rate error
		double rateErr = vehList.at(vehId+1).getVel() - vehList.at(vehId).getVel();

		double rangeErr = actualGap - desiredGap;
		rangeErrTimeLog << time << ":"
						<< rangeErr << ":"
						<< rateErr
						<< std::endl;

		if(Utils::isGreater(time, m_perturbStartTime))
			{
			// Find running min of inver veh gap
			if(Utils::isLess(actualGap,  m_minInterVehGap.at(i)))
				{
				m_minInterVehGap.at(i) = actualGap;
				}

			// Find running max of absolute range error
			if(Utils::isLess(rangeErr,  m_minGap) ||
				Utils::isEqual(rangeErr,  m_minGap))
				{
				double deviation = m_minGap - rangeErr;
				if(Utils::isGreater(deviation,  m_maxRangeErr.at(i)))
					{
					m_maxRangeErr.at(i) = deviation;
					}
				}

			// Find running min of time to collide
			double timeToCol = actualGap/(vehList.at(vehId+1).getVel());
			if(Utils::isLess(timeToCol,  m_minTimeToCol.at(i)))
				{
				m_minTimeToCol.at(i) = timeToCol;
				}
			}
		}
	}

void CFStats::logCarVelocity(double time, std::vector<Vehicle> vehList)
	{
	for(unsigned int vehId = 0; vehId < vehList.size(); vehId+=m_statCnt)
		{
		velTimeLog << time << ":"
				   << vehList.at(vehId).getVel() << ":"
				   << vehList.at(vehId).getPosX()  << ":"
				   << vehList.at(vehId).getAcclr() << ":"
				   << vehList.at(vehId).getHdwayTime()
				   << std::endl;
		}
	}

void CFStats::initStatVectors()
	{
	int cnt = m_vehCnt/m_statCnt;
	if(m_statCnt == 1)
		cnt = cnt - 1;

	for(int i = 0; i < cnt; i++)
		{
		m_maxRangeErr.push_back(-100000);
		m_minInterVehGap.push_back(100000);
		m_minTimeToCol.push_back(100000);
		}
	}

void CFStats::plotStats()
	{
	ostringstream plotCmdStr;
	plotCmdStr << "/home/rudhir/Research/CarFollow/src/plotscript/Plot.sh "
			<< m_vehCnt << " "
			<< m_statCnt << " "
			<< m_reactTime << " "
			<< m_updateTime << " "
			<< m_tauTime;
	string str(plotCmdStr.str());
	system(str.c_str());
	}

void CFStats::plotMetrics()
	{
	// Dump the min and max metrics to file
	ofstream maxRngErrLog;
	ofstream minInterVehGapLog;
	ofstream minTimeToColLog;

	// Open files
	if(!maxRngErrLog.is_open())
		{
		maxRngErrLog.open("maxRngErr.log");
		}
	if(!minInterVehGapLog.is_open())
		{
		minInterVehGapLog.open("minInterVehGap.log");
		}
	if(!minTimeToColLog.is_open())
		{
		minTimeToColLog.open("minTimeToCol.log");
		}

	// Write to files
	int cnt = m_vehCnt/m_statCnt;
	if(m_statCnt == 1)
		cnt = cnt - 1;

	for(int i = 0; i < cnt; i++)
		{
		maxRngErrLog << i << " " << m_maxRangeErr.at(i) << std::endl;
		minInterVehGapLog << i << " " << m_minInterVehGap.at(i) << std::endl;
		minTimeToColLog << i << " " << m_minTimeToCol.at(i) << std::endl;
		}

	// Close files
	if(maxRngErrLog.is_open())
		{
		maxRngErrLog.close();
		}
	if(minInterVehGapLog.is_open())
		{
		minInterVehGapLog.close();
		}
	if(minInterVehGapLog.is_open())
		{
		minTimeToColLog.close();
		}

	ostringstream plotCmdStr;
	plotCmdStr << "/home/rudhir/Research/CarFollow/src/plotscript/PlotMetrics.sh "
			<< m_vehCnt << " "
			<< m_statCnt << " "
			<< m_reactTime << " "
			<< m_updateTime << " "
			<< m_tauTime;
	string str(plotCmdStr.str());
	system(str.c_str());
	}

void CFStats::setMinGap(double minGap)
	{
	m_minGap = minGap;
	}
