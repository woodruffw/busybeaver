/*	beaver.c
	Author: William Woodruff
	------------------------
	Functions for initializing a beaver struct and running it with a statefile.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "beaver.h"

int beaver_init(struct beaver *bb, const char *path)
{
	FILE *state_file = fopen(path, "r");
	long file_sz;
	char *l1, *l2;
	char *l1p, *l2p;
	int zcount0, zcount1;

	if (!state_file)
		return -1;

	if (fseek(state_file, 0L, SEEK_END))
		return -2;

	if (!(file_sz = ftell(state_file)))
		return -3;

	if (fseek(state_file, 0L, SEEK_SET))
		return -4;

	/* states_n[0] is the HALT state */
	bb->states_0[0] = "0";
	bb->states_1[0] = "0";

	l1 = malloc((file_sz / 2) + 1);
	l2 = malloc((file_sz / 2) + 1);

	if (!l1 || !l2)
		return -5;

	fgets(l1, 15, state_file);
	fgets(l2, 15, state_file);

	l1p = strtok(l1, ",");
	for (int i = 1; i < MAX_STATES + 1; i++)
	{
		bb->states_0[i] = l1p;
		l1p = strtok(NULL, ",\n");

		if (l1p == NULL)
			l1p = "0";
	}

	l2p = strtok(l2, ",");
	for (int i = 1; i < MAX_STATES + 1; i++)
	{
		bb->states_1[i] = l2p;
		l2p = strtok(NULL, ",\n");

		if (l2p == NULL)
			l2p = "0";
	}

	for (int i = 1; i <= MAX_STATES; i++)
	{
		if (!strcmp(bb->states_0[i], "0"))
			zcount0++;
		else if (strlen(bb->states_0[i]) != 3)
			return -6;
		if (!strcmp(bb->states_1[i], "0"))
			zcount1++;
		else if (strlen(bb->states_1[i]) != 3)
			return -6;
	}

	if (zcount0 != zcount1)
		return -6;

	bb->nstates = zcount0;
	bb->curr_state = 1;

	tm_init(&(bb->machine), 5000);

	fclose(state_file);

#ifdef DEBUG
	printf("No. states: %d\n", zcount0);
	printf("%s", "states_0: ");
	for (int i = 0; i <= bb->nstates; i++)
	{
		printf("%s ", bb->states_0[i]);
	}
	puts("");
	printf("%s", "states_1: ");
	for (int i = 0; i <= bb->nstates; i++)
	{
		printf("%s ", bb->states_1[i]);
	}
	puts("");
#endif

	return 0;
}

void beaver_destroy(struct beaver *bb)
{
	free(bb->states_0[1]);
	free(bb->states_1[1]);
}

int run(struct beaver bb)
{
	printf("%s%d states.\n", "Beginning busy beaver with ", bb.nstates);
	printf("%s\n", "States are: ");

	printf("0\t");

	for (int i = 1; i <= bb.nstates; i++)
	{
		printf("%d\t", i);
	}

	puts("");

	printf("HALT\t");

	for (int i = 1; i <= bb.nstates; i++)
	{
		printf("%s\t", bb.states_0[i]);
	}

	puts("");

	printf("HALT\t");

	for (int i = 1; i <= bb.nstates; i++)
	{
		printf("%s\t", bb.states_1[i]);
	}

	puts("");
	return 0;
}
