#ifndef BUSYBEAVER_BEAVER_H
#define BUSYBEAVER_BEAVER_H

#include "tm.h"

#define MAX_STATES 4

struct beaver
{
	struct tm machine;
	int curr_state;
	int nstates;
	char *states_0[MAX_STATES + 1];
	char *states_1[MAX_STATES + 1];
};

int beaver_init(struct beaver *bb, const char *path);
int run(struct beaver bb);

#endif /* BUSYBEAVER_BEAVER_H */