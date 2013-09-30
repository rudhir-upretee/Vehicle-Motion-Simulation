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

	double getAcclrResponse(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getAcclrResponseInNetwork(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getInitialHeadwayTime();
	double getStringStableHeadwayTime();

private:

	double m_lamda;
	double m_m;
	double m_l;
};

#endif /* CFMODELSIMPLE_H_ */
