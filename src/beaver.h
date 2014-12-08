/*	beaver.h
	Author: William Woodruff
	------------------------
	Function prototypes and the beaver struct for beaver.c.
*/

#ifndef BUSYBEAVER_BEAVER_H
#define BUSYBEAVER_BEAVER_H

#include "tm.h"

#define MAX_STATES 4 // don't change under penalty of death
#define HALT 0

struct beaver
{
	struct tm machine;
	int curr_state;
	int nstates;
	char *states_0[MAX_STATES + 1];
	char *states_1[MAX_STATES + 1];
};

int beaver_init(struct beaver *bb, const char *path);
void beaver_destroy(struct beaver *bb);
int run(struct beaver bb);

#endif /* BUSYBEAVER_BEAVER_H */
