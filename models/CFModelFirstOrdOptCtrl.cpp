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
		double updateTime, double initHeadwayTime, double minStblHeadwayTime,
		double minGap, double initAcclr) {

	m_alpha = alpha;
	m_k = k;
	m_xi = xi;
	m_tau = tau;
	m_updateTime = updateTime;
	m_initHeadwayTime = initHeadwayTime;
	m_minStblHeadwayTime = minStblHeadwayTime;
	m_minGap = minGap;
	m_initAcclr = initAcclr;
}

CFModelFirstOrdOptCtrl::~CFModelFirstOrdOptCtrl() {

}

double CFModelFirstOrdOptCtrl::getAcclrResp(double time,
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

double CFModelFirstOrdOptCtrl::getAcclrRespInNetSafe(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double acclrVeh = veh.getAcclr();
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();

	double dynHeadwayTime = m_initHeadwayTime +
							(interVehDist/velVeh)/m_initHeadwayTime;
	hdwayTimeUsed = dynHeadwayTime;

	double inputFunc = (m_alpha * (((interVehDist - m_minGap)/hdwayTimeUsed) - velVeh))
					+ (m_k * velDiff)
					- (m_xi * acclrVeh);

	// Acceleration in first order systems
	double acclr = (exp(-m_updateTime/m_tau) * (acclrVeh - inputFunc)) + inputFunc;
	return acclr;
}

double CFModelFirstOrdOptCtrl::getAcclrRespInNetResume(double time,
												Vehicle& veh, Vehicle pred,
												double& hdwayTimeUsed) {
	double acclrVeh = veh.getAcclr();
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() -  veh.getPosX();
	double velDiff = pred.getVel() - veh.getVel();

	//double dynHeadwayTime = std::max(m_minStblHeadwayTime,
	//		m_initHeadwayTime -(interVehDist/velVeh)/m_minStblHeadwayTime);
	//double dynHeadwayTime = std::max(m_minStblHeadwayTime,
			//exp(-((interVehDist/velVeh)/m_minStblHeadwayTime)/25.0));
	double dynHeadwayTime = std::max(m_minStblHeadwayTime,
			m_minStblHeadwayTime+0.8*((interVehDist/velVeh)/m_minStblHeadwayTime));
	hdwayTimeUsed = dynHeadwayTime;

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

double CFModelFirstOrdOptCtrl::getMinStableHeadwayTime() {
	return m_minStblHeadwayTime;
}

