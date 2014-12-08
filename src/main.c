#include <stdio.h>
#include "beaver.h"

int main(int argc, char const *argv[])
{
	struct beaver bb;

	int stat = beaver_init(&bb, "beaver.states");

	switch (stat)
	{
		case -1:
			printf("%s\n", "Error on fopen()");
			break;
		case -2:
		case -3:
		case -4:
			printf("%s\n", "Error on fseek()/ftell()");
			break;
		case -5:
			printf("%s\n", "Error on malloc()");
			break;
		case -6:
			printf("%s\n", "Error in state file format.");
			break;
		default:
			printf("%s\n", "Success.");
	}
	
	return 0;
}