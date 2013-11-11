/*
 * CFAPI.cpp
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#include <iostream>
#include <cmath>
#include <Vehicle.h>
#include <Utils.h>
#include "CFAPI.h"

CFAPI::CFAPI(CFModel* cfModel, double updateTime, double reactTime, double delta,
			double initVehGap, double initVel, double initAcclr,
			double initHdway, int adjHdwayTime):
			m_leaderCtrlStart(4.0),
			m_leaderCtrlDuration (5.0),
			m_leaderCtrlDecelr(-4.0) {

	m_cfModel = cfModel;
	m_updateTime = updateTime;
	m_reactTime = reactTime;
	m_nwDelayDelta = delta;
	m_initVehGap = initVehGap;
    m_initVel = initVel;
	m_initAcclr = initAcclr;
	m_initHdway = initHdway;
	m_adjHdwayTime = adjHdwayTime;

	ACCLR_LIMIT = 4.0;
	DECCLR_LIMIT = -9.0;

	m_networkHopCnt = 1;

	m_factor = floor(m_reactTime/m_updateTime);
	std::cout << "m_factor " << m_factor  << std::endl;
}

CFAPI::~CFAPI() {

}

void CFAPI::initVehicles(std::vector<Vehicle>& vehList, int maxVehicles,
						int connPat, int patCnt, double leaderCtrlStart,
						double leaderCtrlDuration, double leaderDecelr)
{

	initLeaderControl(leaderCtrlStart, leaderCtrlDuration, leaderDecelr);

	// Initialize vehicles
	// Enable safety device according to the command line arguments.
	// For partial network, half the vehicles in front are in network
	// where as the other half are not in network.
	initVehicleNetwork(vehList, maxVehicles, connPat, patCnt);

	// Just copy the list. Init just fills the acclr for all the vehicles
	// till next reactTime. State of the followers will be fixed by
	// updateState() routine.
	for(int i = 0; i < m_factor; i++)
		{
		m_vehStateTable[i] = vehList;
		std::cout << "init step " << i << std::endl;
		}

}

void CFAPI::initVehicleNetwork(std::vector<Vehicle>& vehList, int maxVehicles,
								int connPat, int patCnt)
	{
	bool flag1 = false;
	bool flag2 = false;
	if(connPat == ON_FOLLOW_OFF)
		{
		flag1 = true;
		flag2 = false;
		}
	else
		{
		flag1 = false;
		flag2 = true;
		}

	int vehId = 0;
	while(vehId < maxVehicles)
		{
		//
		// Enable/Disable safety device
		for(int i = 0; i < patCnt; i++, vehId++)
			{
			if(vehId >= maxVehicles)
				{
				break;
				}
			Vehicle veh(vehId,
					(double)((maxVehicles-1) - vehId) * m_initVehGap,
					m_initVel,
					m_initAcclr,
					m_initHdway,
					flag1,
					-1.0);
			vehList.push_back(veh);
			}

		//
		// Enable/Disable safety device
		for(int i = 0; i < (maxVehicles - patCnt); i++, vehId++)
			{
			if(vehId >= maxVehicles)
				{
				break;
				}
			Vehicle veh(vehId,
					(double)((maxVehicles-1) - vehId) * m_initVehGap,
					m_initVel,
					m_initAcclr,
					m_initHdway,
					flag2,
					-1.0);
			vehList.push_back(veh);
			}
		}

    // Configure the safety device start time
	int reactTimeCnt = 0;
	int hopCnt = 0;
	for(int i = 0; i <= maxVehicles-1; i++)
		{
		if (vehList.at(i).hasSafetyDev())
			{
			// Set start time
			vehList.at(i).setSafetyDevStartTime(m_leaderCtrlStart +
												hopCnt * m_nwDelayDelta +
												reactTimeCnt * m_reactTime);
			}

		// Update counters for followers. Do not update for last vehicle.
		if (i < maxVehicles-1)
			{
			if(vehList.at(i).hasSafetyDev() && vehList.at(i+1).hasSafetyDev())
				{
				hopCnt++;
				}
			else if ((vehList.at(i).hasSafetyDev() && !vehList.at(i+1).hasSafetyDev()) ||
					(!vehList.at(i).hasSafetyDev() && vehList.at(i+1).hasSafetyDev()) ||
					(!vehList.at(i).hasSafetyDev() && !vehList.at(i+1).hasSafetyDev()))
				{
				reactTimeCnt++;
				}
			}

		std::cout << "Veh: " << vehList.at(i).getId() << " trigger: "
				<< vehList.at(i).getSafetyDevStartTime() << std::endl;
		}
	}

void CFAPI::initLeaderControl(double leaderCtrlStart, double leaderCtrlDuration,
								double decelr) {

	m_leaderCtrlStart = leaderCtrlStart;
	m_leaderCtrlDuration = leaderCtrlDuration;
	m_leaderCtrlDecelr = decelr;
}

///////////////////////////////////////////////////////////////////
// Get position and velocity for next simulation interval i.e.
// (time + updateTime).
//
// This loop calculates the position and speed for next updateTime
// based on the current acceleration. Current accelerations for all
// the vehicles are available for time < (time + reactTime).
///////////////////////////////////////////////////////////////////
std::vector<Vehicle> CFAPI::updateState(int step, double time) {

	std::cout << "updateState step " << step << std::endl;
	std::vector<Vehicle> vehList = m_vehStateTable[step];
	std::vector<Vehicle> nextStateVehList = m_vehStateTable[step + 1];

	for(unsigned int i = 0; i < vehList.size(); i++)
		{
		double s_init = vehList.at(i).getPosX();
		double u = vehList.at(i).getVel();
		double a = vehList.at(i).getAcclr();
		double t = m_updateTime;

		double nextPosX = s_init + (u * t) + (0.5 * a * pow(t, 2.0));
		double nextVel  = std::max(0.0, u + a * t);
		//double nextVel  = u + a * t;

		nextStateVehList.at(i).setPosX(nextPosX);
		nextStateVehList.at(i).setVel(nextVel);
		}
	m_vehStateTable[step + 1] = nextStateVehList;
	return nextStateVehList;
}

///////////////////////////////////////////////////////////////////
// Get acceleration for next reactTime i.e (time + reactTime)
//
// This loop calculates the acceleration responses of all the
// vehicles for time = time + reactTime.
///////////////////////////////////////////////////////////////////
void CFAPI::updateAcclr(int step, double time) {

	std::cout << "updateAcclr next step: " << step + m_factor << std::endl;

	// Lead vehicle controlled externally
	std::vector<Vehicle> vehList = m_vehStateTable[step];
	updateLeaderAcclr(step, time);

	// Followers controlled by car follow model. Follower list start from 1.
	for(unsigned int i = 1; i < vehList.size(); i++)
		{
		updateFollowerAcclr(step, time, vehList.at(i), vehList.at(i-1));
		}
}

void CFAPI::updateLeaderAcclr(int step, double time) {

	// Leaders controlled externally.
	// Create a new vehicle state with same state as current vehicle.
	// Acclr for current state is updated here. Position and velocity
	// will be calculated in future when time = currTime + reactionTime;
	Vehicle leaderNewState(m_vehStateTable[step].at(0).getId(),
							m_vehStateTable[step].at(0).getPosX(),
							m_vehStateTable[step].at(0).getVel(),
							m_vehStateTable[step].at(0).getAcclr(),
							m_vehStateTable[step].at(0).getHdwayTime(),
							m_vehStateTable[step].at(0).hasSafetyDev(),
							m_vehStateTable[step].at(0).getSafetyDevStartTime());

	if((time >= m_leaderCtrlStart) &&
			(time <= m_leaderCtrlStart + m_leaderCtrlDuration))
		{
		m_vehStateTable[step].at(0).setAcclr(m_leaderCtrlDecelr);
		}
	else
		{
		m_vehStateTable[step].at(0).setAcclr(0.0);
		}

	m_vehStateTable[step + m_factor].push_back(leaderNewState);
}

void CFAPI::updateFollowerAcclr(int step, double time, Vehicle& veh, Vehicle predVeh) {

	// Followers controlled by car follow model.
	// Create a new vehicle state with same state as current vehicle.
	// Acclr for new state is calculated here. Position and velocity
	// will be calculated in future when time = currTime + reactionTime;
	Vehicle followerNewState(veh.getId(),
							veh.getPosX(),
							veh.getVel(),
							veh.getAcclr(),
							veh.getHdwayTime(),
							veh.hasSafetyDev(),
							veh.getSafetyDevStartTime());

	double newAcclr = 0.0;
	double newHdwayTime = 0.0;

	if((veh.hasSafetyDev()) &&
		(time >= veh.getSafetyDevStartTime()))
		{
		if(m_adjHdwayTime == HDWAY_SAFE)
		    {
			newAcclr = m_cfModel->getAcclrRespInNetSafe(time, veh, predVeh, newHdwayTime);
		    }
		else
			{
			newAcclr = m_cfModel->getAcclrRespInNetResume(time, veh, predVeh, newHdwayTime);
			}

		std::cout << "Recv safety message: Veh: " << veh.getId()
					<< " at time " << time << std::endl;
		}
	else
		{
		newAcclr = m_cfModel->getAcclrResp(time, veh, predVeh, newHdwayTime);
		}

	// Adjust for unrealistic acclr and decclr values
	if(newAcclr > ACCLR_LIMIT)
		{
		newAcclr = ACCLR_LIMIT;
		}
	if(newAcclr < DECCLR_LIMIT)
		{
		newAcclr = DECCLR_LIMIT;
		}
	std::cout << "Next Acclr: Veh " << veh.getId()
						<< " acclr " << newAcclr << std::endl;

	followerNewState.setAcclr(newAcclr);
	followerNewState.setHdwayTime(newHdwayTime);
	m_vehStateTable[step + m_factor].push_back(followerNewState);
}

