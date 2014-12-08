#include <stdio.h>
#include "beaver.h"

int main(int argc, char const *argv[])
{
	struct beaver bb;

	if (argc != 2)
	{
		printf("%s %s %s\n", "Usage:", argv[0], "<statefile>");
		return 1;
	}

	int stat = beaver_init(&bb, argv[1]);

	switch (stat)
	{
		case 0:
			printf("%s\n", "Statefile load success.");
			break;
		case -1:
			printf("%s\n", "Error on fopen().");
			return -1;
		case -2:
		case -3:
		case -4:
			printf("%s\n", "Error on fseek()/ftell().");
			return -1;
		case -5:
			printf("%s\n", "Error on malloc().");
			return -1;
		case -6:
			printf("%s\n", "Error on fgets().");
			return -1;
		case -7:
			printf("%s\n", "Error in statefile format.");
			return -1;
		default:
			printf("%s\n", "Other error.");
			return -1;
	}

	// not actually implemented yet
	run(bb);

	beaver_destroy(&bb);
	
	return 0;
}
