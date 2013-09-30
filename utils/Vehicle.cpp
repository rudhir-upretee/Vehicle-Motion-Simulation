/*
 * Vehicle.cpp
 *
 *  Created on: May 22, 2013
 *      Author: rudhir
 */

#include "Vehicle.h"

Vehicle::Vehicle(int id, double posX, double vel, double acclr, double hdwayTime,
				bool hasSafetyDev, double safetyDevStartTime) {
	m_id = id;
	m_posX = posX;
	m_vel = vel;
	m_acclr = acclr;
	m_hdwayTime = hdwayTime;
	m_safetyDev = hasSafetyDev;
	m_safetyDevStartTime = safetyDevStartTime;
}

Vehicle::~Vehicle() {
}

int Vehicle::getId() {
	return m_id;
}

double Vehicle::getPosX() {
	return m_posX;
}

double Vehicle::getVel() {
	return m_vel;
}

double Vehicle::getAcclr() {
	return m_acclr;
}

double Vehicle::getHdwayTime() {
	return m_hdwayTime;
}

void Vehicle::setId(int id) {
	m_id = id;
}

void Vehicle::setPosX(double posX) {
	m_posX = posX;
}

void Vehicle::setVel(double vel) {
	m_vel = vel;
}

void Vehicle::setAcclr(double acclr) {
	m_acclr = acclr;
}

void Vehicle::setHdwayTime(double time) {
	m_hdwayTime = time;
}

void Vehicle::configSafetyDev(bool flag) {
	m_safetyDev = flag;
}

bool Vehicle::hasSafetyDev() {
	return m_safetyDev;
}

void Vehicle::setSafetyDevStartTime(double startTime) {
	m_safetyDevStartTime = startTime;
}

double Vehicle::getSafetyDevStartTime() {
	return m_safetyDevStartTime;
}
