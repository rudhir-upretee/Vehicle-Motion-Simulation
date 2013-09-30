/*
 * CFModelIDM.h
 *
 *  Created on: May 28, 2013
 *      Author: rudhir
 */

#ifndef CFMODELIDM_H_
#define CFMODELIDM_H_

#include <cmath>
#include <Vehicle.h>
#include "CFModel.h"

class CFModelIDM: public CFModel {
public:
	CFModelIDM(double desVel, double initHeadwayTime, double strStblHeadwayTime,
				double minGap, double maxAcclr, double desDecelr);
	virtual ~CFModelIDM();

	double getAcclrResponse(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getAcclrResponseInNetwork(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getInitialHeadwayTime();
	double getStringStableHeadwayTime();

private:
	double m_desired_velocity;
	double m_initHeadwayTime;
	double m_strStblHeadwayTime;
	double m_min_gap;
	double m_max_acclr;
	double m_desired_decelr;
};

#endif /* CFMODELIDM_H_ */
