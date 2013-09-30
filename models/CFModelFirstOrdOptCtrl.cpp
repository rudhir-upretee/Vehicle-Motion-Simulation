/*
 * CFModelOptCtrlFeedback.cpp
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#include <cmath>
#include "CFModelFirstOrdOptCtrl.h"

CFModelFirstOrdOptCtrl::CFModelFirstOrdOptCtrl(
		double alpha, double k, double xi, double tau,
		double updateTime, double initHeadwayTime, double strStblHeadwayTime,
		double minGap, double initAcclr) {

	m_alpha = alpha;
	m_k = k;
	m_xi = xi;
	m_tau = tau;
	m_updateTime = updateTime;
	m_initHeadwayTime = initHeadwayTime;
	m_strStblHeadwayTime = strStblHeadwayTime;
	m_minGap = minGap;
	m_initAcclr = initAcclr;
}

CFModelFirstOrdOptCtrl::~CFModelFirstOrdOptCtrl() {

}

double CFModelFirstOrdOptCtrl::getAcclrResponse(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double acclrVeh = veh.getAcclr();
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();

	hdwayTimeUsed = m_initHeadwayTime;
	double inputFunc = (m_alpha * (((interVehDist - m_minGap)/m_initHeadwayTime) - velVeh))
					+ (m_k * velDiff)
					- (m_xi * acclrVeh);

	// Acceleration in first order systems
#if 0
	double acclr = (exp(-time/m_tau) * (m_initAcclr - inputFunc)) + inputFunc;
#endif
	double acclr = (exp(-m_updateTime/m_tau) * (acclrVeh - inputFunc)) + inputFunc;
	return acclr;
}

double CFModelFirstOrdOptCtrl::getAcclrResponseInNetwork(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double acclrVeh = veh.getAcclr();
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();

#if 0
	double dynHeadwayTime = m_initHeadwayTime +
							(m_initHeadwayTime/(interVehDist/velVeh));
	hdwayTimeUsed = dynHeadwayTime;

	double inputFunc = (m_alpha * (((interVehDist - m_minGap)/dynHeadwayTime) - velVeh))
					+ (m_k * velDiff)
					- (m_xi * acclrVeh);
#else
	hdwayTimeUsed = m_strStblHeadwayTime;
	double inputFunc = (m_alpha * (((interVehDist - m_minGap)/m_strStblHeadwayTime) - velVeh))
					+ (m_k * velDiff)
					- (m_xi * acclrVeh);
#endif

	// Acceleration in first order systems
	double acclr = (exp(-m_updateTime/m_tau) * (acclrVeh - inputFunc)) + inputFunc;
	return acclr;
}

double CFModelFirstOrdOptCtrl::getInitialHeadwayTime() {
	return m_initHeadwayTime;
}

double CFModelFirstOrdOptCtrl::getStringStableHeadwayTime() {
	return m_strStblHeadwayTime;
}
