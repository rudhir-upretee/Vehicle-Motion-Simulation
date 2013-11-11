/*
 * CFModelIDM.cpp
 *
 *  Created on: May 28, 2013
 *      Author: rudhir
 */

#include "CFModelIDM.h"
#include <iostream>

CFModelIDM::CFModelIDM(double desVel, double initHeadwayTime, double minStblHeadwayTime,
		double minGap, double maxAcclr, double desDecelr) {

	m_desired_velocity = desVel;
	m_initHeadwayTime = initHeadwayTime;
	m_minStblHeadwayTime = minStblHeadwayTime;
	m_min_gap = minGap;
	m_max_acclr = maxAcclr;
	m_desired_decelr = desDecelr;
}

CFModelIDM::~CFModelIDM() {

}

double CFModelIDM::getAcclrResp(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	//double interVehDist = std::max(m_min_gap, pred.getPosX() - veh.getPosX());
	double interVehDist = pred.getPosX() - veh.getPosX();
	double velDiff =  veh.getVel() - pred.getVel();

	hdwayTimeUsed = m_initHeadwayTime;
	double effectiveDesMinGap = m_min_gap + std::max(0.0,
			(velVeh * hdwayTimeUsed) +
			((velVeh * velDiff)/(2 * sqrt(m_max_acclr * m_desired_decelr))));

	double acclrComponent = m_max_acclr *
								(1 - pow(velVeh/m_desired_velocity, 4.0));

	double brakingComponent = -1.0 * m_max_acclr *
								pow(effectiveDesMinGap/interVehDist, 2.0);

#if 0
	std::cout << "veh " << veh.getId()
			<< " vel " << velVeh
			<< " velDiff " << velDiff
			<< " vehDist " << interVehDist
			<< " effGap " << effectiveDesMinGap
			<< " acclrcomp " << acclrComponent
			<< " brakecomp " << brakingComponent
			<< std::endl;
#endif

	return (acclrComponent + brakingComponent);
}

double CFModelIDM::getAcclrRespInNetSafe(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() - veh.getPosX();
	double velDiff =  veh.getVel() - pred.getVel();

	hdwayTimeUsed = m_minStblHeadwayTime;
	double effectiveDesMinGap = m_min_gap + std::max(0.0,
			(velVeh * hdwayTimeUsed) +
			((velVeh * velDiff)/(2 * sqrt(m_max_acclr * m_desired_decelr))));

	double acclrComponent = m_max_acclr *
								(1 - pow(velVeh/m_desired_velocity, 4.0));

	double brakingComponent = -1.0 * m_max_acclr *
								pow(effectiveDesMinGap/interVehDist, 2.0);

#if 0
	std::cout << "veh " << veh.getId()
			<< " vel " << velVeh
			<< " velDiff " << velDiff
			<< " vehDist " << interVehDist
			<< " effGap " << effectiveDesMinGap
			<< " acclrcomp " << acclrComponent
			<< " brakecomp " << brakingComponent
			<< std::endl;
#endif

	return (acclrComponent + brakingComponent);
}

double CFModelIDM::getAcclrRespInNetResume(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double interVehDist = pred.getPosX() - veh.getPosX();
	double velDiff =  veh.getVel() - pred.getVel();

	hdwayTimeUsed = m_minStblHeadwayTime;
	double effectiveDesMinGap = m_min_gap + std::max(0.0,
			(velVeh * hdwayTimeUsed) +
			((velVeh * velDiff)/(2 * sqrt(m_max_acclr * m_desired_decelr))));

	double acclrComponent = m_max_acclr *
								(1 - pow(velVeh/m_desired_velocity, 4.0));

	double brakingComponent = -1.0 * m_max_acclr *
								pow(effectiveDesMinGap/interVehDist, 2.0);

#if 0
	std::cout << "veh " << veh.getId()
			<< " vel " << velVeh
			<< " velDiff " << velDiff
			<< " vehDist " << interVehDist
			<< " effGap " << effectiveDesMinGap
			<< " acclrcomp " << acclrComponent
			<< " brakecomp " << brakingComponent
			<< std::endl;
#endif

	return (acclrComponent + brakingComponent);
}

double CFModelIDM::getInitialHeadwayTime() {
	return m_initHeadwayTime;
}

double CFModelIDM::getMinStableHeadwayTime() {
	return 	m_minStblHeadwayTime;
}

