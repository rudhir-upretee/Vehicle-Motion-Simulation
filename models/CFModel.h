/*
 * CFModel.h
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#ifndef CFMODEL_H_
#define CFMODEL_H_

#include <Vehicle.h>

class CFModel {
public:
	CFModel();
	virtual ~CFModel();

	virtual double getAcclrResponse(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) = 0;
	virtual double getAcclrResponseInNetwork(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) = 0;
	virtual double getInitialHeadwayTime() = 0;
	virtual double getStringStableHeadwayTime() = 0;

protected:

private:

};

#endif /* CFMODEL_H_ */
