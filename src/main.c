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
			printf("%s\n", "Success.");
			break;
		case -1:
			printf("%s\n", "Error on fopen().");
			break;
		case -2:
		case -3:
		case -4:
			printf("%s\n", "Error on fseek()/ftell().");
			break;
		case -5:
			printf("%s\n", "Error on malloc().");
			break;
		case -6:
			printf("%s\n", "Error in state file format.");
			break;
		default:
			printf("%s\n", "Other error.");
	}
	
	return 0;
}