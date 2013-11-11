/*
 * CFModelFirstOrdOptCtrl.h
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#ifndef CFMODELFIRSTORDOPTCTRL_H_
#define CFMODELFIRSTORDOPTCTRL_H_

#include <Vehicle.h>
#include "CFModel.h"

class CFModelFirstOrdOptCtrl: public CFModel {
public:
	CFModelFirstOrdOptCtrl(double alpha, double k, double xi, double tau,
				double updateTime, double initHeadwayTime, double minStblHeadwayTime,
				double minGap, double initAcclr);
	virtual ~CFModelFirstOrdOptCtrl();

	double getAcclrResp(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getAcclrRespInNetSafe(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getAcclrRespInNetResume(double time, Vehicle& veh, Vehicle pred, double& hdwayTimeUsed);
	double getInitialHeadwayTime();
	double getMinStableHeadwayTime();

private:

	double m_alpha;
	double m_k;
	double m_xi;
	double m_tau;
	double m_updateTime;
	double m_initHeadwayTime;
	double m_minStblHeadwayTime;
	double m_minGap;
	double m_initAcclr;
};

#endif /* CFMODELFIRSTORDOPTCTRL_H_ */
