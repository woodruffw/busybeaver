/*	tm.c
	Author: William Woodruff
	------------------------
	Contains the function for initializing a tm (Turing machine) struct.
*/

#include <string.h>
#include "tm.h"

/*	tm_init
	initializes the given tm with 'cell' at 'init_cell' and a tape of '0's.
*/
void tm_init(struct tm *machine, int init_cell)
{
	machine->cell = init_cell;
	memset(machine->tape, '0', 10000);
}
