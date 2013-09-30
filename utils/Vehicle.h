/*
 * Vehicle.h
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

class Vehicle {
public:
	Vehicle(int id, double posX, double vel, double acclr, double hdwayTime,
			bool hasSafetyDev, double safetyDevStartTime);
	virtual ~Vehicle();

	int getId();
	double getPosX();
	double getVel();
	double getAcclr();
	double getHdwayTime();
	void setId(int id);
	void setPosX(double posX);
	void setVel(double vel);
	void setAcclr(double acclr);
	void setHdwayTime(double time);
	void configSafetyDev(bool flag);
	bool hasSafetyDev();
	void setSafetyDevStartTime(double startTime);
	double getSafetyDevStartTime();

	private:
	int m_id;
	double m_posX;
	double m_vel;
	double m_acclr;
	double m_safetyDevStartTime;
	bool m_safetyDev;
	double m_hdwayTime;
};

#endif /* VEHICLE_H_ */
