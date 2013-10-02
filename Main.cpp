//============================================================================
// Name        : Main.cpp
// Author      : Rudhir
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "CFModel.h"
#include "CFModelSimple.h"
#include "CFModelOptimalControl.h"
#include "CFModelFirstOrdOptCtrl.h"
#include "CFModelIDM.h"
#include "CFAPI.h"
#include "CFStats.h"
#include "Utils.h"
#include "ArgParse.h"

using namespace std;

#if 0
ofstream logDistTime;
ofstream logVelTime;
ofstream logRangeErrTime;
ofstream logParams;
#endif
ostringstream paramsLogStr;


// Globals
static double INITIAL_INTERVEH_DIST = 0.0;
static double INITIAL_VELOCITY = 0.0;
static double INITIAL_ACCELERATION = 0.0;
static double LEADER_CTRL_START = 0.0;
static double LEADER_CTRL_DURATION = 0.0;
static double LEADER_CRTL_DECELR = 0.0;

#if 0
void openLogFiles();
void closeLogFiles();
void logRangeError(double time, std::vector<Vehicle> vehList, int interval);
void logCarVelocity(double time, std::vector<Vehicle> vehList, int interval);
#endif
void printUsage(char* inString);


int main(int argc, char* argv[]) {

	Arguments arguments;
	argParse(argc, argv, &arguments);

	int model = atoi(arguments.model);
	if((model < SM) || (model > IDM))
		{
		cout << "ERROR: Invalid argument to model" << endl;
		printUsage(argv[0]);
		return -1;
		}

	int vehCnt = atoi(arguments.vehCnt);
	if(vehCnt < 1)
		{
		cout << "ERROR: Invalid argument to veh-cnt" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double simTime = atof(arguments.simTime);
    if(Utils::isLess(simTime, 0.0) || Utils::isEqual(simTime, 0.0))
    	{
    	cout << "ERROR: Invalid argument to sim-time" << endl;
    	printUsage(argv[0]);
		return -1;
    	}

	int connPat = atoi(arguments.connPat);
	if((connPat < ON_FOLLOW_OFF) || (connPat > OFF_FOLLOW_ON))
		{
		cout << "ERROR: Invalid argument to conn-pat" << endl;
		printUsage(argv[0]);
		return -1;
		}

	int patCnt = atoi(arguments.patCnt);
	if(patCnt < 0)
		{
		cout << "ERROR: Invalid argument to pat-cnt" << endl;
		printUsage(argv[0]);
		return -1;
		}

	int statCnt = atoi(arguments.statCnt);
	if(statCnt < 1)
		{
		cout << "ERROR: Invalid argument to stat-cnt" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double reactTime = atof(arguments.reactTime);
	if(Utils::isLess(reactTime, 0.0) || Utils::isEqual(reactTime, 0.0))
		{
		cout << "ERROR: Invalid argument to react-time" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double tauTime = atof(arguments.tauTime);
	if(Utils::isLess(tauTime, 0.0) || Utils::isEqual(tauTime, 0.0))
		{
		cout << "ERROR: Invalid argument to tau-time" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double updateTime = atof(arguments.updateTime);
	if(Utils::isLess(updateTime, 0.0) || Utils::isEqual(updateTime, 0.0))
		{
		cout << "ERROR: Invalid argument to update-time" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double nwDeltaTime = atof(arguments.nwDeltaTime);
	if(Utils::isLess(nwDeltaTime, 0.0) || Utils::isEqual(nwDeltaTime, 0.0))
		{
		cout << "ERROR: Invalid argument to nwDelta-time" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double initHdwayTime = atof(arguments.initHdwayTime);
	if(Utils::isLess(initHdwayTime, 0.0) || Utils::isEqual(initHdwayTime, 0.0))
		{
		cout << "ERROR: Invalid argument to init-hdway-time" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double stableHdwayTime = atof(arguments.stableHdwayTime);
	if(Utils::isLess(stableHdwayTime, 0.0) || Utils::isEqual(stableHdwayTime, 0.0)
		|| (Utils::isLess(stableHdwayTime, initHdwayTime)))
		{
		cout << "ERROR: Invalid argument to stable-hdway-time" << endl;
		printUsage(argv[0]);
		return -1;
		}

	cout << "model = " << model << endl
			<< "vehCnt = " << vehCnt << endl
			<< "simTime = " << simTime << endl
			<< "connPat = " << connPat << endl
			<< "patCnt = " << patCnt << endl
			<< "statCnt = " << statCnt << endl
			<< "reactTime = " << reactTime << endl
			<< "tauTime = " << tauTime << endl
			<< "updateTime = " << updateTime << endl
			<< "nwDeltaTime = " << nwDeltaTime << endl
			<< "initHdwayTime = " << initHdwayTime << endl
			<< "stableHdwayTime = " << stableHdwayTime << endl;

	// Sanity check
	if(updateTime > reactTime)
		{
		cout << endl
				<< "ERROR: Update time should be less than react time"
				<< endl << endl;
		return -1;
		}

	// Important classes
	CFModel* cfModel;
	CFStats cfStats;
#if 0
	openLogFiles();
	logParams << "N=" << vehCnt
			<< " T=" << simTime
			<< " UpdT=" << updateTime
			<< " RctT=" << reactTime
			<< " DelT=" << nwDeltaTime;
#endif
	paramsLogStr << "N=" << vehCnt
			<< " T=" << simTime
			<< " UpdT=" << updateTime
			<< " RctT=" << reactTime
			<< " DelT=" << nwDeltaTime;

	if(model == SM)
		{
		double lamda = 0.3, m = 1.0, l = 1.0;

		INITIAL_INTERVEH_DIST = 37.0;
		INITIAL_VELOCITY = 30.0;
		INITIAL_ACCELERATION = 0.0;

		LEADER_CTRL_START = 4.0;
		LEADER_CTRL_DURATION = 5.0;
		LEADER_CRTL_DECELR = -2.0;

		cfModel = new CFModelSimple(lamda, m, l);

#if 0
		logParams << " Lamda=" << lamda
				<< " m=" << m
				<< " l=" << l << endl;
#endif
		paramsLogStr << " Lamda=" << lamda
				<< " m=" << m
				<< " l=" << l << endl;
		}
	else if(model == OCM)
		{
		double k1 = 0.1, k2 = 0.5;

		// Works with hdway=1.25 and stableHdway=2.0
		INITIAL_INTERVEH_DIST = 37.5;
		INITIAL_VELOCITY = 30.0;
		INITIAL_ACCELERATION = 0.0;

		LEADER_CTRL_START = 4.0;
		LEADER_CTRL_DURATION = 5.0;
		LEADER_CRTL_DECELR = -4.0;

		cfModel = new CFModelOptimalControl(k1, k2,
											initHdwayTime, stableHdwayTime);
#if 0
		logParams << " k1=" << k1
				<< " k2=" << k2
				<< " hdwayT=" << initHdwayTime
				<< " stblHdwayT=" << stableHdwayTime << endl;
#endif
		paramsLogStr << " k1=" << k1
				<< " k2=" << k2
				<< " hdwayT=" << initHdwayTime
				<< " stblHdwayT=" << stableHdwayTime << endl;
		}
	else if(model == FOOCM)
		{
		double alpha = 2, k = 1, xi = 0.6;
		double minGap = 4.0;

		// Works best tau = 0.2, updT = 0.1, reactT = 0.3, nwDlyT = 0.1
		INITIAL_VELOCITY = 30.0;
		INITIAL_INTERVEH_DIST = INITIAL_VELOCITY * initHdwayTime;
		INITIAL_ACCELERATION = 0.0;

		LEADER_CTRL_START = 10.0;
		LEADER_CTRL_DURATION = 5.0;
		LEADER_CRTL_DECELR = -2.0;

		cfModel = new CFModelFirstOrdOptCtrl(alpha, k, xi, tauTime,
							updateTime, initHdwayTime, stableHdwayTime,
							minGap, INITIAL_ACCELERATION);

#if 0
		logParams << " TauT=" << tauTime
				<< " alpha=" << alpha
				<< " k=" << k
				<< " xi=" << xi
				<< " minGap=" << minGap
				<< " hdwayT=" << initHdwayTime
				<< " sHdwayT=" << stableHdwayTime << endl;
#endif
		paramsLogStr << " TauT=" << tauTime
				<< " alpha=" << alpha
				<< " k=" << k
				<< " xi=" << xi
				<< " minGap=" << minGap
				<< " hdwayT=" << initHdwayTime
				<< " sHdwayT=" << stableHdwayTime << endl;
		}
	else if(model == IDM)
		{
		double desVel = 30.0, minGap = 2.0, maxAcclr = 1.0, desDecelr = 3.0;

		// Works with hdway=1.25 and stableHdway=2.0
		INITIAL_INTERVEH_DIST = 34.0;
		INITIAL_VELOCITY = 30.0;
		INITIAL_ACCELERATION = 0.0;

		LEADER_CTRL_START = 4.0;
		LEADER_CTRL_DURATION = 5.0;
		LEADER_CRTL_DECELR = -4.0;

		cfModel = new CFModelIDM(desVel, initHdwayTime, stableHdwayTime,
								minGap, maxAcclr, desDecelr);

#if 0
		logParams << " desVel=" << desVel
				<< " desTgap=" << initHdwayTime
				<< " minGap=" << minGap
				<< " maxAcl=" << maxAcclr
				<< " desDcl=" << desDecelr << endl;
#endif
		paramsLogStr << " desVel=" << desVel
				<< " desTgap=" << initHdwayTime
				<< " minGap=" << minGap
				<< " maxAcl=" << maxAcclr
				<< " desDcl=" << desDecelr << endl;
		}
	cfStats.logParams(paramsLogStr);

	std::vector<Vehicle> vehList;

	CFAPI cfApi(cfModel, updateTime, reactTime, nwDeltaTime,
				INITIAL_INTERVEH_DIST, INITIAL_VELOCITY, INITIAL_ACCELERATION,
				initHdwayTime);

	cfApi.initVehicles(vehList, vehCnt, connPat, patCnt,
				LEADER_CTRL_START, LEADER_CTRL_DURATION, LEADER_CRTL_DECELR);

	// Main Loop
	double currTime = 0.0;
	for(int step = 0; Utils::isLess(((double)step * updateTime), simTime);
			step++, currTime += updateTime)
		{
		// Print statistics
		cout << "Time " << currTime << endl;
		cfStats.logRangeError(currTime, vehList, statCnt);
		cfStats.logCarVelocity(currTime, vehList, statCnt);

		// Acclr Response update
		cfApi.updateAcclr(step, currTime);

		// Next updated states
		vehList = cfApi.updateState(step, currTime);
		}

	// Generating plots
	cout << endl;
	cout << "Running script ..." << endl;
	cout.flush();
	char cmd[500];
	sprintf(cmd,
			"/home/rudhir/Research/CarFollow/src/plotscript/Plot.sh %d %d %f %f %f",
			vehCnt, statCnt, reactTime, updateTime, tauTime);
	system(cmd);

#if 0
	closeLogFiles();
#endif
	return 0;
}

#if 0
void openLogFiles()
	{
	if(!logParams.is_open())
		{
		logParams.open("params.log");
		}
	if(!logDistTime.is_open())
		{
		logDistTime.open("distTime.log");
		}
	if(!logRangeErrTime.is_open())
		{
		logRangeErrTime.open("rangeErrTime.log");
		}
	if(!logVelTime.is_open())
		{
		logVelTime.open("velTime.log");
		}

	}

void closeLogFiles()
	{
	if(logParams.is_open())
		{
		logParams.close();
		}
	if(logDistTime.is_open())
		{
		logDistTime.close();
		}
	if(logRangeErrTime.is_open())
		{
		logRangeErrTime.close();
		}
	if(logVelTime.is_open())
		{
		logVelTime.close();
		}

	}

void logRangeError(double time, std::vector<Vehicle> vehList, int interval)
	{
	for(unsigned int i = 0; i+1 < vehList.size(); i+=interval)
		{
		//
		// Log Inter car gap
		logDistTime << time << ":"
				    << vehList.at(i).getPosX() - vehList.at(i+1).getPosX()
				    << std::endl;

		//
		// Log range error
		double actualGap =
				vehList.at(i).getPosX() - vehList.at(i+1).getPosX();
		double desiredGap =
				vehList.at(i+1).getHdwayTime() * vehList.at(i+1).getVel();

		double rangeErr = actualGap - desiredGap;
		logRangeErrTime << time << ":"
						<< rangeErr
						<< std::endl;
		}
	}

void logCarVelocity(double time, std::vector<Vehicle> vehList, int interval)
	{
	for(unsigned int i = 0; i < vehList.size(); i+=interval)
		{
		logVelTime << time << ":"
				   << vehList.at(i).getVel() << ":"
				   << vehList.at(i).getPosX()  << ":"
				   << vehList.at(i).getAcclr()
				   << std::endl;
		}
	}
#endif

void printUsage(char* inString)
	{
	cout << endl
		<< "Usage: " << inString << " [OPTION...] DUMMY_ARG"
					<< endl
		<< "Try ` " << inString << " --help' or ` "
					<< inString << " --usage' for more information."
					<< endl << endl;
	}


