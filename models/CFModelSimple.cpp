/*
 * CFModelSimple.cpp
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#include <cmath>
#include "CFModelSimple.h"

CFModelSimple::CFModelSimple(double lamda, double m, double l) {
	m_lamda = lamda;
	m_m = m;
	m_l = l;
}

CFModelSimple::~CFModelSimple() {

}

double CFModelSimple::getAcclrResponse(double time, Vehicle& veh, Vehicle pred,
										double& hdwayTimeUsed) {
	double velVeh = veh.getVel();
	double velPred = pred.getVel();
	double posXVeh = veh.getPosX();
	double posXPred = pred.getPosX();

	double acclr = (m_lamda * pow(velVeh, m_m) * (velPred - velVeh)) /
					(pow(posXPred - posXVeh, m_l));
	hdwayTimeUsed = 0.0;

	return acclr;
}

double CFModelSimple::getAcclrResponseInNetwork(double time, Vehicle& veh,
												Vehicle pred, double& hdwayTimeUsed) {
	hdwayTimeUsed = 0.0;
	return 0.0;
}

double CFModelSimple::getInitialHeadwayTime() {
	return 0.0;
}

double CFModelSimple::getStringStableHeadwayTime() {
	return 0.0;
}

