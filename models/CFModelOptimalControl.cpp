/*
 * CFModelOptimalControl.cpp
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#include <cmath>
#include <Config.h>
#include "CFModelOptimalControl.h"

CFModelOptimalControl::CFModelOptimalControl(double k1, double k2,
					double initHeadwayTime, double minStblHeadwayTime) {
	m_k1 = k1;
	m_k2 = k2;
	m_initHeadwayTime = initHeadwayTime;
	m_minStblHeadwayTime = minStblHeadwayTime;
}

CFModelOptimalControl::~CFModelOptimalControl() {

}

double CFModelOptimalControl::getAcclrResp(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();
	hdwayTimeUsed = m_initHeadwayTime;
	double acclr = m_k1 * (interVehDist - (hdwayTimeUsed * velVeh)) +
					m_k2 * (velDiff);
	return acclr;
}

double CFModelOptimalControl::getAcclrRespInNetSafe(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();

	double dynHeadwayTime = m_initHeadwayTime +
							(m_initHeadwayTime/(interVehDist/velVeh));
	hdwayTimeUsed = dynHeadwayTime;

	double acclr = m_k1 * (interVehDist - (hdwayTimeUsed * velVeh)) +
					m_k2 * (velDiff);
	return acclr;
}

double CFModelOptimalControl::getAcclrRespInNetResume(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();

	hdwayTimeUsed = m_minStblHeadwayTime;

	double acclr = m_k1 * (interVehDist - (hdwayTimeUsed * velVeh)) +
					m_k2 * (velDiff);
	return acclr;
}

double CFModelOptimalControl::getInitialHeadwayTime() {
	return m_initHeadwayTime;
}

double CFModelOptimalControl::getMinStableHeadwayTime() {
	return m_minStblHeadwayTime;
}

