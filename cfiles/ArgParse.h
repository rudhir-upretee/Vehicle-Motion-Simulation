#ifndef ARGPARSE_H_
#define ARGPARSE_H_

#ifdef __cplusplus
extern "C" {
#endif


#define xstr(s) str(s)
#define str(s) #s
#define MAX_LINE_CHARS  100
#define SM              1 //SIMPLE_MODEL
#define	OCM             2 //OPT_CTRL_MODEL
#define	FOOCM           3 //FIRST_ORD_OPT_CTRL_MODEL
#define IDM             4 //IDM_MODEL
#define ON_FOLLOW_OFF   1
#define OFF_FOLLOW_ON   2
#define HDWAY_SAFE      1
#define HDWAY_RESUME    2

/* This structure is used by main to communicate with parse_opt. */
typedef struct Arguments {
	char* model;
	char* vehCnt;
	char* simTime;
	char* connPat;
	char* patCnt;
	char* statCnt;
	char* reactTime;
	char* tauTime;
	char* updateTime;
	char* nwDeltaTime;
	char* initHdwayTime;
	char* adjHdwayTime;
	char* perturbStartTime;
	char *args[1]; /* ARG1 */

}Arguments;

void argParse(int argc, char **argv, Arguments* arguments);



#ifdef __cplusplus
}
#endif

#endif //ARGPARSE_H_
