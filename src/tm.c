/*	tm.c
	Author: William Woodruff
	------------------------
	Contains the function for initializing a tm (Turing machine) struct.
*/

#include <string.h>
#include "tm.h"

void tm_init(struct tm *machine, int init_cell)
{
	machine->cell = init_cell;
	memset(machine->tape, '0', 10000);
}
