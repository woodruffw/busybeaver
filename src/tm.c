#include <string.h>
#include "tm.h"

void tm_init(struct tm *machine, int init_cell)
{
	machine->cell = init_cell;
	memset(machine->tape, 10000, 0);
}