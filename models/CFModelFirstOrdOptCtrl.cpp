/*
 * CFModelOptCtrlFeedback.cpp
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */
#include <iostream>
#include <cmath>
#include <Utils.h>
#include <Config.h>
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

#if DYNAMIC_HEADWAY_ADJUST
	double dynHeadwayTime = m_initHeadwayTime +
							(interVehDist/velVeh)/m_initHeadwayTime;
	hdwayTimeUsed = dynHeadwayTime;
#else
	hdwayTimeUsed = m_strStblHeadwayTime;
#endif

	double inputFunc = (m_alpha * (((interVehDist - m_minGap)/hdwayTimeUsed) - velVeh))
					+ (m_k * velDiff)
					- (m_xi * acclrVeh);

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

