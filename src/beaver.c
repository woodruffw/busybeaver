/*	beaver.c
	Author: William Woodruff
	------------------------
	Functions for initializing a beaver struct and running it with a statefile.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "beaver.h"

/*	beaver_init
	Initializes the given beaver struct (pointer) with data from the given file.
	Returns an error code < 0 if an error occurred.
*/
int beaver_init(struct beaver *bb, const char *path)
{
	FILE *state_file;
	long file_sz;
	char *l1, *l2;
	char *l1p, *l2p;
	int zcount0 = 4, zcount1 = 4;

	state_file = fopen(path, "r");

	if (!state_file)
		return BB_ERR_FOPEN;

	if (fseek(state_file, 0L, SEEK_END))
		return BB_ERR_FSEEK;

	if (!(file_sz = ftell(state_file)))
		return BB_ERR_FTELL;

	if (fseek(state_file, 0L, SEEK_SET))
		return BB_ERR_FSEEK;

	// states_n[0] is the HALT state
	bb->states_0[0] = HALT;
	bb->states_1[0] = HALT;

	// 50 bytes is more than enough for each line
	l1 = malloc(50);
	l2 = malloc(50);

	if (!l1 || !l2)
		return BB_ERR_MALLOC;

	if (!fgets(l1, 50, state_file))
		return BB_ERR_FGETS;

	if (!fgets(l2, 50, state_file))
		return BB_ERR_FGETS;

	// remove the trailing newline from the first line
	if (l1[strlen(l1) - 1] == '\n')
		l1[strlen(l1) - 1] = '\0';

#ifdef DEBUG
	printf("l1: %s\n", l1);
	printf("l2: %s\n", l2);
#endif

	l1p = strtok(l1, " ");
	for (int i = 1; i <= MAX_STATES; i++)
	{
		bb->states_0[i] = l1p;
		l1p = strtok(NULL, " ");

		if (l1p == NULL)
			l1p = "0";
	}

	l2p = strtok(l2, " ");
	for (int i = 1; i <= MAX_STATES; i++)
	{
		bb->states_1[i] = l2p;
		l2p = strtok(NULL, " ");

		if (l2p == NULL)
			l2p = "0";
	}

	for (int i = 1; i <= MAX_STATES; i++)
	{
		if (!strcmp(bb->states_0[i], "0"))
			zcount0--;
		else if (strlen(bb->states_0[i]) != 3 || CTOI(bb->states_0[i][2]) > 4)
			return BB_ERR_BADFILE;
		if (!strcmp(bb->states_1[i], "0"))
			zcount1--;
		else if (strlen(bb->states_1[i]) != 3 || CTOI(bb->states_1[i][2]) > 4)
			return BB_ERR_BADFILE;
	}

	if (zcount0 != zcount1)
		return BB_ERR_BADFILE;

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

/*	beaver_destroy
	deallocates any memory allocated by beaver_init in the given beaver struct
*/
void beaver_destroy(struct beaver *bb)
{
	free(bb->states_0[1]);
	free(bb->states_1[1]);
}

/*	run
	the main busybeaver function.
	prints out the state table, then runs until a HALT symbol is read.
*/
int run(struct beaver bb)
{
	int iter = 0, count = 0;
	char curr_symbol = 0;
	char *curr_state_str;

	// print some friendly output before starting
	printf("%s%d states.\n", "Beginning busy beaver with ", bb.nstates);
	printf("%s\n", "The state table is: ");

	printf("\t0\t");
	for (int i = 1; i <= bb.nstates; i++)
	{
		printf("%d\t", i);
	}
	puts("");

	printf("0\tHALT\t");
	for (int i = 1; i <= bb.nstates; i++)
	{
		printf("%s\t", bb.states_0[i]);
	}
	puts("");

	printf("1\tHALT\t");
	for (int i = 1; i <= bb.nstates; i++)
	{
		printf("%s\t", bb.states_1[i]);
	}
	puts("\n---------------------------------");

	while (bb.curr_state != HALT)
	{
		curr_symbol = bb.machine.tape[bb.machine.cell];

		printf("Iteration: %d, Symbol: %c, State: %d\n", iter + 1, curr_symbol, bb.curr_state);
		// printf("Symbol read: %c\n", curr_symbol);
		// printf("Current state: %d\n", bb.curr_state);

		if (curr_symbol == '1')
		{
			curr_state_str = bb.states_1[bb.curr_state];
		}
		else // 0 or anything else is considered a blank tape symbol
		{
			curr_state_str = bb.states_0[bb.curr_state];
		}

		if (curr_state_str[0] == '1')
			bb.machine.tape[bb.machine.cell] = '1';
		else
			bb.machine.tape[bb.machine.cell] = '0';

		if (curr_state_str[1] == 'r')
			bb.machine.cell++;
		else if (curr_state_str[1] == 'l')
			bb.machine.cell--;

		bb.curr_state = CTOI(curr_state_str[2]);

		printf("Next state: %d\n", bb.curr_state);
		puts("---------------------------------");

		iter++;
	}

	for (int i = 0; i < 10000; i++)
		if (bb.machine.tape[i] == '1')
			count++;

	printf("Machine halted with %d iterations.\n", iter);
	printf("End result: %d cells toggled.\n", count);

	return 0;
}
