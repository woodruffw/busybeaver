/*	misc.c
	Author: William Woodruff
	------------------------
	Miscellaneous functions.
*/

#if defined(__linux__) || defined(__unix__)
	#define _BSD_SOURCE
	#include <unistd.h>
#elif defined(_WIN32)
	#include <Windows.h>
#else
	#warning "This system lacks a good way to sleep. Continuing, but delays will not work."
#endif

/*	ssleep
	
*/
void ssleep(double seconds)
{
	if (seconds >= 1.0)
	{
#if defined(__linux__) || defined(__unix__)
		sleep(1);
#elif defined(_WIN32)
		Sleep(1000);
#endif
	}
	else
	{
#if defined(__linux__) || defined(__unix__)
		usleep(seconds * 100000);
#elif defined(_WIN32)
		Sleep((DWORD) seconds * 1000)
#endif
	}
}
