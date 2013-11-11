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

	//
	// This function calculates next acclr for vehicles not in network. It
	// does not change the head way time once it is set to some initial value.
	virtual double getAcclrResp(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) = 0;

	//
	// This function calculates next acclr for vehicles in network. It
	// increases the head way time dynamically and therefore increases the
	// inter vehicular gap. This is done for safety.
	// It guarantees string stability.
	virtual double getAcclrRespInNetSafe(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) = 0;

	//
	// This function calculates next acclr for vehicles in network. It
	// decreases the head way time to a minimum head way time supported
	// by the CF Model. This is typically called once the traffic is stable
	// and it is safe for vehicles to come closer. It guarantees string stability.
	virtual double getAcclrRespInNetResume(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed) = 0;

	virtual double getInitialHeadwayTime() = 0;
	virtual double getMinStableHeadwayTime() = 0;

protected:

private:

};

#endif /* CFMODEL_H_ */
