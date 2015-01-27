/*	main.c
	Author: William Woodruff
	------------------------
	The entry point for busybeaver.
*/

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

	switch (beaver_init(&bb, argv[1]))
	{
		case 0:
			printf("%s\n", "Statefile load success.");
			break;
		case BB_ERR_FOPEN:
			printf("%s\n", "Error on fopen(). Bad permissions/filename?");
			return -1;
		case BB_ERR_FSEEK:
		case BB_ERR_FTELL:
			printf("%s\n", "Error on fseek()/ftell().");
			return -1;
		case BB_ERR_MALLOC:
			printf("%s\n", "Error on malloc().");
			return -1;
		case BB_ERR_FGETS:
			printf("%s\n", "Error on fgets().");
			return -1;
		case BB_ERR_BADFILE:
			printf("%s\n", "Statefile appears corrupt.");
			return -1;
		default:
			printf("%s\n", "Other error.");
			return -1;
	}

	run(bb);

	beaver_destroy(&bb);
	
	return 0;
}
