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

ostringstream paramsLogStr;

// Globals
static double INITIAL_INTERVEH_DIST = 0.0;
static double INITIAL_VELOCITY = 0.0;
static double INITIAL_ACCELERATION = 0.0;
static double perturbDuration = 5.0;
static double perturbMagnitude = -2.0;

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

	double adjHdwayTime = atoi(arguments.adjHdwayTime);
	if((adjHdwayTime < HDWAY_SAFE) || (adjHdwayTime > HDWAY_RESUME))
		{
		cout << "ERROR: Invalid argument to adj-hdway-time" << endl;
		printUsage(argv[0]);
		return -1;
		}

	double perturbStartTime = atof(arguments.perturbStartTime);
	if(Utils::isLess(perturbStartTime, 0.0) || Utils::isEqual(perturbStartTime, 0.0))
		{
		cout << "ERROR: Invalid argument to perturb-start-time" << endl;
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
			<< "adjHdwayTime = " << adjHdwayTime << endl
			<< "perturbStartTime = " << perturbStartTime << endl;

	// Sanity check
	if(updateTime > reactTime)
		{
		cout << endl
				<< "ERROR: Update time should be less than react time"
				<< endl << endl;
		return -1;
		}

	// Initialize classes
	CFStats cfStats(model,
			vehCnt,
			simTime,
			connPat,
			patCnt,
			statCnt,
			reactTime,
			tauTime,
			updateTime,
			nwDeltaTime,
			initHdwayTime,
			adjHdwayTime,
			perturbStartTime,
			4.0);

	CFModel* cfModel;

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

		perturbDuration = 5.0;
		if(adjHdwayTime == HDWAY_SAFE)
			{
			perturbMagnitude = -2.0;
			}
		else
			{
			perturbMagnitude = 0.0;
			}

		cfModel = new CFModelSimple(lamda, m, l);

		paramsLogStr << " Lamda=" << lamda
				<< " m=" << m
				<< " l=" << l;
		cfStats.logParams(paramsLogStr);
		}
	else if(model == OCM)
		{
		double k1 = 0.1, k2 = 0.5;
		int minStableHdwayTime = 1.0;
		if(Utils::isLess(initHdwayTime, minStableHdwayTime))
			{
			cout << "ERROR: init-hdway-time is less than minStableHdwayTime" << endl;
			printUsage(argv[0]);
			return -1;
			}

		// Works with hdway=1.25 and stableHdway=2.0
		INITIAL_INTERVEH_DIST = 37.5;
		INITIAL_VELOCITY = 30.0;
		INITIAL_ACCELERATION = 0.0;

		perturbDuration = 5.0;
		if(adjHdwayTime == HDWAY_SAFE)
			{
			perturbMagnitude = -2.0;
			}
		else
			{
			perturbMagnitude = 0.0;
			}

		cfModel = new CFModelOptimalControl(k1, k2,
											initHdwayTime, minStableHdwayTime);

		paramsLogStr << " k1=" << k1
				<< " k2=" << k2
				<< " hdwayT=" << initHdwayTime
				<< " minStblHdwayT=" << minStableHdwayTime;
		cfStats.logParams(paramsLogStr);
		}
	else if(model == FOOCM)
		{
		double alpha = 2, k = 1, xi = 0.6;
		double minGap = 4.0;
		double minStableHdwayTime = 2.0;
		if(Utils::isLess(initHdwayTime, minStableHdwayTime))
			{
			cout << "ERROR: init-hdway-time is less than minStableHdwayTime" << endl;
			printUsage(argv[0]);
			return -1;
			}

		cfStats.setMinGap(minGap);

		// Works best tau = 0.2, updT = 0.1, reactT = 0.3, nwDlyT = 0.1
		INITIAL_VELOCITY = 30.0;
    	INITIAL_INTERVEH_DIST = INITIAL_VELOCITY * initHdwayTime + minGap;
		INITIAL_ACCELERATION = 0.0;

		perturbDuration = 5.0;
		if(adjHdwayTime == HDWAY_SAFE)
			{
			perturbMagnitude = -2.0;
			}
		else
			{
			perturbMagnitude = 0.0;
			}

		cfModel = new CFModelFirstOrdOptCtrl(alpha, k, xi, tauTime,
							updateTime, initHdwayTime, minStableHdwayTime,
							minGap, INITIAL_ACCELERATION);

		paramsLogStr << " TauT=" << tauTime
				<< " alpha=" << alpha
				<< " k=" << k
				<< " xi=" << xi
				<< " minGap=" << minGap
				<< " hdwayT=" << initHdwayTime
				<< " minStblHdwayT=" << minStableHdwayTime;
		cfStats.logParams(paramsLogStr);
		}
	else if(model == IDM)
		{
		double desVel = 30.0, minGap = 4.0, maxAcclr = 1.0, desDecelr = 3.0;
		double minStableHdwayTime = 2.0;
		if(Utils::isLess(initHdwayTime, minStableHdwayTime))
			{
			cout << "ERROR: init-hdway-time is less than minStableHdwayTime" << endl;
			printUsage(argv[0]);
			return -1;
			}

		cfStats.setMinGap(minGap);

		// Works with hdway=1.25 and stableHdway=2.0
		INITIAL_VELOCITY = 30.0;
		INITIAL_INTERVEH_DIST = INITIAL_VELOCITY * initHdwayTime + minGap;
		INITIAL_ACCELERATION = 0.0;

		perturbDuration = 5.0;
		if(adjHdwayTime == HDWAY_SAFE)
			{
			perturbMagnitude = -2.0;
			}
		else
			{
			perturbMagnitude = 0.0;
			}

		cfModel = new CFModelIDM(desVel, initHdwayTime, minStableHdwayTime,
								minGap, maxAcclr, desDecelr);

		paramsLogStr << " desVel=" << desVel
				<< " desTgap=" << initHdwayTime
				<< " minGap=" << minGap
				<< " maxAcl=" << maxAcclr
				<< " desDcl=" << desDecelr;
		cfStats.logParams(paramsLogStr);
		}

	std::vector<Vehicle> vehList;

	CFAPI cfApi(cfModel, updateTime, reactTime, nwDeltaTime,
				INITIAL_INTERVEH_DIST, INITIAL_VELOCITY, INITIAL_ACCELERATION,
				initHdwayTime, adjHdwayTime);

	cfApi.initVehicles(vehList, vehCnt, connPat, patCnt,
			perturbStartTime, perturbDuration, perturbMagnitude);

	// Main Loop
	double currTime = 0.0;
	for(int step = 0; Utils::isLess(((double)step * updateTime), simTime);
			step++, currTime += updateTime)
		{
		// Print statistics
		cout << "Time " << currTime << endl;
		cfStats.logRangeError(currTime, vehList);
		cfStats.logCarVelocity(currTime, vehList);

		// Acclr Response update
		cfApi.updateAcclr(step, currTime);

		// Next updated states
		vehList = cfApi.updateState(step, currTime);
		}

	// Generating plots
	cout << endl;
	cout << "Running script ..." << endl;
    cfStats.plotStats();
	cfStats.plotMetrics();

	return 0;
}

void printUsage(char* inString)
	{
	cout << endl
		<< "Usage: " << inString << " [OPTION...] DUMMY_ARG"
					<< endl
		<< "Try ` " << inString << " --help' or ` "
					<< inString << " --usage' for more information."
					<< endl << endl;
	}


