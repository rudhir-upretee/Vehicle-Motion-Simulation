/*
 * CFModelSimple.h
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#ifndef CFMODELSIMPLE_H_
#define CFMODELSIMPLE_H_

#include <Vehicle.h>
#include "CFModel.h"

class CFModelSimple: public CFModel {
public:
	CFModelSimple(double lamda, double m, double l);
	virtual ~CFModelSimple();

	double getAcclrResp(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getAcclrRespInNetSafe(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getAcclrRespInNetResume(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getInitialHeadwayTime();
	double getMinStableHeadwayTime();

private:

	double m_lamda;
	double m_m;
	double m_l;
};

#endif /* CFMODELSIMPLE_H_ */
