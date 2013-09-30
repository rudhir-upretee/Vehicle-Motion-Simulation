/*
 * CFModelOptimalControl.h
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#ifndef CFMODELOPTIMALCONTROL_H_
#define CFMODELOPTIMALCONTROL_H_

#include <Vehicle.h>
#include "CFModel.h"

class CFModelOptimalControl: public CFModel {
public:
	CFModelOptimalControl(double k1, double k2,
					double initHeadwayTime, double strStblHeadwayTime);
	virtual ~CFModelOptimalControl();

	double getAcclrResponse(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getAcclrResponseInNetwork(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getInitialHeadwayTime();
	double getStringStableHeadwayTime();

private:

	double m_k1;
	double m_k2;
	double m_initHeadwayTime;
	double m_strStblHeadwayTime;
};

#endif /* CFMODELOPTIMALCONTROL_H_ */
