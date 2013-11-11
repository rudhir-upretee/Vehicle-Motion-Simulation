/*
 * CFAPI.h
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#ifndef CFAPI_H_
#define CFAPI_H_

#include <vector>
#include <string>
#include <map>
#include <Vehicle.h>
#include <CFModel.h>
#include <ArgParse.h>

class CFAPI {
public:
	CFAPI(CFModel* cfModel, double updateTime, double reactTime, double delta,
			double initVehGap, double initVel, double initAcclr,
			double initHdway, int adjHdwayTime);
	virtual ~CFAPI();

	void initVehicles(std::vector<Vehicle>& vehList, int maxVehicles,
							int connPat, int patCnt, double leaderCtrlStart,
							double leaderCtrlDuration, double leaderDecelr);
	void initVehicleNetwork(std::vector<Vehicle>& vehList, int maxVehicles,
							int connPat, int patCnt);
	void initLeaderControl(double leaderCtrlStart, double leaderCtrlDuration,
							double decelr);
	std::vector<Vehicle> updateState(int step, double time);
	void updateAcclr(int step, double time);

private:
	double ACCLR_LIMIT;
	double DECCLR_LIMIT;
//	static const int ON_FOLLOW_OFF = 1;
//	static const int OFF_FOLLOW_ON = 2;
//	static const int HDWAY_SAFETY = 1;
//	static const int HDWAY_RESUME = 2;

    double m_updateTime;
    double m_reactTime;
    double m_nwDelayDelta;
    double m_initVehGap;
    double m_initVel;
    double m_initAcclr;
    double m_initHdway;
    int m_adjHdwayTime;
    int m_factor;

    double m_leaderCtrlStart;
    double m_leaderCtrlDuration;
    double m_leaderCtrlDecelr;

    int m_networkHopCnt;

    CFModel* m_cfModel;

    typedef std::map<int, std::vector<Vehicle> > VehStateTable;
    VehStateTable m_vehStateTable;

	void updateFollowerAcclr(int step, double time, Vehicle& veh, Vehicle predVeh);
	//void updateFollowerAcclrInNetwork(int step, double time, Vehicle veh, Vehicle predVeh);
	void updateLeaderAcclr(int step, double time);

};

#endif /* CFAPI_H_ */
