#include <stdio.h>
#include <string.h>
#include <argp.h>
#include "ArgParse.h"

const char *program_version = "CarFollow 1.0";

const char *program_bug_address = "<rupretee@mix.wvu.edu>";

char model_doc1[MAX_LINE_CHARS];
char model_doc2[MAX_LINE_CHARS];
char model_doc3[MAX_LINE_CHARS];
char model_doc4[MAX_LINE_CHARS];
char connPat_doc1[MAX_LINE_CHARS];
char connPat_doc2[MAX_LINE_CHARS];
char connPatCnt_doc1[MAX_LINE_CHARS];
char connPatCnt_doc2[MAX_LINE_CHARS];
char statCnt_doc1[MAX_LINE_CHARS];
char statCnt_doc2[MAX_LINE_CHARS];

void createOptDocs(void);

/*
 OPTIONS.  Field 1 in ARGP.
 Order of fields: {NAME, KEY, ARG, FLAGS, DOC}.
 */
static struct argp_option options[] = {
		{ 0, 0, 0, 0, "", 1},
		{ "model", 'm', "INT", 0, "Car following model" },
		{ "model", 'm', xstr(SM), 0, model_doc1 },
		{ "model", 'm', xstr(OCM), 0, model_doc2 },
		{ "model", 'm', xstr(FOOCM), 0, model_doc3 },
		{ "model", 'm', xstr(IDM), 0, model_doc4 },
		{ 0, 0, 0, 0, "", 2},
		{ "veh-cnt", 'n', "INT", 0, "Number of vehicles in simulation" },
		{ 0, 0, 0, 0, "", 3},
		{ "sim-time", 'i', "DOUBLE", 0, "Duration of simulation in seconds" },
		{ 0, 0, 0, 0, "", 4},
		{ "conn-pat", 'c', "INT", 0, "Vehicle network connectivity pattern" },
		{ "conn-pat", 'c', xstr(ON_FOLLOW_OFF), 0, connPat_doc1 },
		{ "conn-pat", 'c', xstr(OFF_FOLLOW_ON), 0, connPat_doc2 },
		{ 0, 0, 0, 0, "", 5},
		{ "pat-cnt", 'o', "INT", 0, "Number of vehicles for network connectivity pattern" },
		{ "pat-cnt", 'o', "NUM", 0, connPatCnt_doc1 },
		{ "pat-cnt", 'o', "NUM", 0, connPatCnt_doc2 },
		{ 0, 0, 0, 0, "", 6},
		{ "stat-cnt", 's', "INT", 0, "Vehicle interval count for calculating statistics" },
		{ "stat-cnt", 's', "1", 0, statCnt_doc1 },
		{ "stat-cnt", 's', "N", 0, statCnt_doc2 },
		{ 0, 0, 0, 0, "", 7},
		{ "react-time", 'r', "DOUBLE", 0, "Reaction time delay in seconds." },
		{ 0, 0, 0, 0, "", 8},
		{ "tau-time", 't', "DOUBLE", 0, "First order response time constant in seconds." },
		{ 0, 0, 0, 0, "", 9},
		{ "update-time", 'u', "DOUBLE", 0, "Simulation state update interval in seconds" },
		{ 0, 0, 0, 0, "", 10},
		{ "nwDelta-time", 'd', "DOUBLE", 0, "Network propagation delay in seconds" },
		{ 0, 0, 0, 0, "", 11},
		{ "init-hdway-time", 'w', "DOUBLE", 0, "Initial headway time in seconds" },
		{ 0, 0, 0, 0, "", 12},
		{ "stable-hdway-time", 'x', "DOUBLE", 0, "String stable headway time in seconds" },
		{ 0 } };

/*
 PARSER. Field 2 in ARGP.
 Order of parameters: KEY, ARG, STATE.
 */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
	Arguments* arguments = state->input;

	switch (key) {
	case 'm':
		arguments->model = arg;
		break;
	case 'n':
		arguments->vehCnt = arg;
		break;
	case 'i':
		arguments->simTime = arg;
		break;
	case 'c':
		arguments->connPat = arg;
		break;
	case 'o':
		arguments->patCnt = arg;
		break;
	case 's':
		arguments->statCnt = arg;
		break;
	case 'r':
		arguments->reactTime = arg;
		break;
	case 't':
		arguments->tauTime = arg;
		break;
	case 'u':
		arguments->updateTime = arg;
		break;
	case 'd':
		arguments->nwDeltaTime = arg;
		break;
	case 'w':
		arguments->initHdwayTime = arg;
		break;
	case 'x':
		arguments->stableHdwayTime = arg;
		break;
	case ARGP_KEY_ARG:
		if (state->arg_num >= 1) {
			argp_usage(state);
		}
		arguments->args[state->arg_num] = arg;
		break;
	case ARGP_KEY_END:
		if (state->arg_num < 1) {
			argp_usage(state);
		}
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/*
 ARGS_DOC. Field 3 in ARGP.
 A description of the non-option command-line arguments
 that we accept.
 */
static char args_doc[] = "DUMMY_ARG";

/*
 DOC.  Field 4 in ARGP.
 Program documentation.
 */
static char doc[] =
	"A program to simulate car following behavior in a single lane traffic.";

/*
 The ARGP structure itself.
 */
static struct argp argp = {options, parse_opt, args_doc, doc};

/*
 The main function.
 Notice how now the only function call needed to process
 all command-line options and arguments nicely
 is argp_parse.
 */
void argParse(int argc, char **argv, Arguments* arguments) {

	/* Set argument defaults */
	arguments->model = "3";
	arguments->vehCnt = "100";
	arguments->simTime = "150";
	arguments->connPat = "2";
	arguments->patCnt = "100";
	arguments->statCnt = "1";
	arguments->reactTime = "0.3";
	arguments->tauTime = "0.2";
	arguments->updateTime = "0.1";
	arguments->nwDeltaTime = "0.1";
	arguments->initHdwayTime = "1.0";
	arguments->stableHdwayTime = "1.5";

	/* Where the magic happens */
	createOptDocs();
	argp_parse(&argp, argc, argv, 0, 0, arguments);

	/* Print argument values */
#if 0
	printf("model = %s\nveh-cnt = %s\nsim-time = %s\n"
			"conn-pat = %s\npat-cnt = %s\nstat-cnt = %s\n"
			"react-time = %s\ntau-time = %s\nupdate-time = %s\n"
			"nwDelta-time = %s\ninit-hdway-time = %s\nstable-hdway-time = %s\n",
			arguments->model,
			arguments->vehCnt,
			arguments->simTime,
			arguments->connPat,
			arguments->patCnt,
			arguments->statCnt,
			arguments->reactTime,
			arguments->tauTime,
			arguments->updateTime,
			arguments->nwDeltaTime,
			arguments->initHdwayTime,
			arguments->stableHdwayTime);
	printf("ARG1 = %s\n\n", arguments->args[0]);
#endif
}

void createOptDocs(void){

	strcpy(model_doc1, "Simple Model");
	strcpy(model_doc2, "Optimal Control Model");
	strcpy(model_doc3, "First Order Optimal Control Model");
	strcpy(model_doc4, "IDM");

	strcpy(connPat_doc1, "vehicles IN network followed by vehicles OUT of network");
	strcpy(connPat_doc2, "vehicles OUT of network followed by vehicles IN network");

	strcpy(connPatCnt_doc1, "-n 100 -c 1 -o NUM means first NUM vehicles IN and remaining n-NUM OUT");
	strcpy(connPatCnt_doc2, "-n 100 -c 2 -o NUM means first NUM vehicles OUT and remaining n-NUM IN");

	strcpy(statCnt_doc1, "-s 1  means take statistics of all the vehicles");
	strcpy(statCnt_doc2, "-s N  means take statistics of every Nth vehicle");

}

