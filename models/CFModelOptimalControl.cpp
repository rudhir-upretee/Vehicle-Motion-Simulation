/*
 * CFModelOptimalControl.cpp
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#include <cmath>
#include "CFModelOptimalControl.h"

CFModelOptimalControl::CFModelOptimalControl(double k1, double k2,
					double initHeadwayTime, double strStblHeadwayTime) {
	m_k1 = k1;
	m_k2 = k2;
	m_initHeadwayTime = initHeadwayTime;
	m_strStblHeadwayTime = strStblHeadwayTime;
}

CFModelOptimalControl::~CFModelOptimalControl() {

}

double CFModelOptimalControl::getAcclrResponse(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();
	double acclr = m_k1 * (interVehDist - (m_initHeadwayTime * velVeh)) +
					m_k2 * (velDiff);
	hdwayTimeUsed = m_initHeadwayTime;
	return acclr;
}

double CFModelOptimalControl::getAcclrResponseInNetwork(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();
#if 0
	double acclr = m_k1 * (interVehDist - (m_max_headwayTime * velVeh)) +
					m_k2 * (velDiff);
	hdwayTimeUsed = m_max_headwayTime;
#else
	double dynHeadwayTime = m_initHeadwayTime +
							(m_initHeadwayTime/(interVehDist/velVeh));
	hdwayTimeUsed = dynHeadwayTime;
	double acclr = m_k1 * (interVehDist - (dynHeadwayTime * velVeh)) +
					m_k2 * (velDiff);
#endif
	return acclr;
}

double CFModelOptimalControl::getInitialHeadwayTime() {
	return m_initHeadwayTime;
}

double CFModelOptimalControl::getStringStableHeadwayTime() {
	return m_strStblHeadwayTime;
}

