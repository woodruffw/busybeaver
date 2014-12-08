/*	tm.h
	Author: William Woodruff
	------------------------
	Function prototypes and the tm struct.
*/

#ifndef BUSYBEAVER_TM_H
#define BUSYBEAVER_TM_H

struct tm
{
	/*
		This can be increased, but make sure to also increase the value
		used in beaver_init on the beaver struct's tm in the tm_init call.
	*/
	char tape[10000];
	int cell;
};

void tm_init(struct tm *machine, int init_cell);

#endif /* BUSYBEAVER_TM_H */
